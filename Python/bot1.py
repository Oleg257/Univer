import telebot
from telebot import types
import requests
import sqlite3
from math import radians, sin, cos, sqrt, atan2
from config import DGIS_API_KEY, TELEGRAM_BOT_TOKEN
import random
import time

bot = telebot.TeleBot(TELEGRAM_BOT_TOKEN)
conn = sqlite3.connect('gas_stations .db', check_same_thread=False)
cursor = conn.cursor()
user_data = {}

def create_tables():
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        user_id INTEGER PRIMARY KEY,
        username TEXT,
        first_name TEXT,
        last_name TEXT,
        registration_date TEXT
    )''')
    
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS search_history (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER,
        latitude REAL,
        longitude REAL,
        radius INTEGER,
        search_date TEXT,
        FOREIGN KEY (user_id) REFERENCES users (user_id)
    )''')
    
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS favorites (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER,
        station_id TEXT,
        station_name TEXT,
        station_address TEXT,
        station_lat REAL,
        station_lon REAL,
        added_date TEXT,
        FOREIGN KEY (user_id) REFERENCES users (user_id),
        UNIQUE(user_id, station_id)
    )''')
    conn.commit()

create_tables()

def calculate_distance(lat1, lon1, lat2, lon2):
    R = 6371000
    lat1, lon1, lat2, lon2 = map(radians, [lat1, lon1, lat2, lon2])
    dlat = lat2 - lat1
    dlon = lon2 - lon1
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    return R * c

def find_gas_stations_2gis(lat, lon, radius=1000):
    try:
        all_stations = []
        offset = 0
        batch_size = 10
        attempts = 0
        max_attempts = 3
        
        while len(all_stations) < 20 and attempts < max_attempts:
            params = {
                'q': "АЗС",
                'type': 'branch',
                'point': f"{lon},{lat}",
                'radius': radius,
                'fields': 'items.point,items.name,items.address_name,items.id',
                'key': DGIS_API_KEY,
                'page_size': batch_size,
                'page': (offset // batch_size) + 1,
                'r': random.random()
            }
            
            try:
                response = requests.get("https://catalog.api.2gis.com/3.0/items", 
                                      params=params,
                                      timeout=10)
                response.raise_for_status()
                data = response.json()
                
                if 'result' not in data:
                    error_msg = data.get('error', {}).get('message', 'Unknown API error')
                    print(f"API Error: {error_msg}")
                    attempts += 1
                    time.sleep(1)
                    continue
                
                if 'items' not in data['result'] or not data['result']['items']:
                    break
                
                stations = data['result']['items']
                
                for station in stations:
                    point = station.get('point', {})
                    station_lon = point.get('lon')
                    station_lat = point.get('lat')
                    
                    if station_lon is None or station_lat is None:
                        continue
                        
                    station['distance'] = calculate_distance(lat, lon, station_lat, station_lon)
                    all_stations.append(station)
                
                offset += len(stations)
                if len(stations) < batch_size:
                    break
                    
            except requests.exceptions.RequestException as e:
                print(f"Request failed: {e}")
                attempts += 1
                time.sleep(1)
                continue
        
        if not all_stations:
            print(f"No stations found at {lat},{lon} with radius {radius}")
            return None
        
        all_stations.sort(key=lambda x: x['distance'])
        return all_stations[:20]
        
    except Exception as e:
        print(f"Error in find_gas_stations_2gis: {str(e)}")
        return None

def geocode_address(address):
    try:
        params = {
            'q': address,
            'fields': 'items.point',
            'key': DGIS_API_KEY,
            'r': random.random()
        }
        
        response = requests.get("https://catalog.api.2gis.com/3.0/items", 
                              params=params,
                              timeout=10)
        response.raise_for_status()
        data = response.json()
        
        if 'result' not in data or 'items' not in data['result'] or not data['result']['items']:
            print(f"No results for address: {address}")
            return None
        
        first_item = data['result']['items'][0]
        point = first_item.get('point', {})
        
        if 'lat' not in point or 'lon' not in point:
            print(f"No coordinates in point: {point}")
            return None
            
        return point['lat'], point['lon']
    
    except requests.exceptions.RequestException as e:
        print(f"Geocoding request failed: {e}")
        return None
    except Exception as e:
        print(f"Error in geocode_address: {e}")
        return None

def create_station_card(station, index, total, user_id, show_distance=True):
    name = station.get('name', 'Неизвестная АЗС')
    address = station.get('address_name', 'Адрес не указан')
    distance = station.get('distance', 0)
    station_id = station.get('id')
    station_url = f"https://2gis.ru/firm/{station_id}"
    
    cursor.execute('SELECT 1 FROM favorites WHERE user_id = ? AND station_id = ?', (user_id, station_id))
    is_favorite = cursor.fetchone() is not None
    
    card_text = f"⛽ <b>{name}</b>\n📍 Адрес: {address}\n"
    
    if show_distance:
        card_text += f"📏 Расстояние: {distance:.0f} м\n\n"
    
    card_text += f"🔢 {index + 1} из {total}"
    
    markup = types.InlineKeyboardMarkup()
    buttons = []
    
    if total > 1:
        buttons.append(types.InlineKeyboardButton("◀️", callback_data=f'prev_{index}'))
    
    buttons.append(types.InlineKeyboardButton("🗺 Карта", url=station_url))
    
    if total > 1:
        buttons.append(types.InlineKeyboardButton("▶️", callback_data=f'next_{index}'))
    
    markup.row(*buttons)
    
    fav_button = types.InlineKeyboardButton(
        "❤️ Удалить из избранного" if is_favorite else "🤍 Добавить в избранное",
        callback_data=f'fav_{station_id}_{index}'
    )
    markup.row(fav_button)
    
    return card_text, markup

@bot.message_handler(commands=['start'])
def send_welcome(message):
    user_id = message.from_user.id
    cursor.execute('''
    INSERT OR IGNORE INTO users (user_id, username, first_name, last_name, registration_date)
    VALUES (?, ?, ?, ?, datetime('now'))''',
    (user_id, message.from_user.username, message.from_user.first_name, message.from_user.last_name))
    conn.commit()
    
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    markup.row(types.KeyboardButton("📍 Найти по местоположению"))
    markup.row(types.KeyboardButton("🔍 Найти по адресу"))
    markup.row(types.KeyboardButton("❤️ Мои избранные АЗС"))
    
    bot.send_message(
        message.chat.id,
        "⛽ <b>Бот для поиска АЗС</b>\n\n"
        "Выберите способ поиска:",
        reply_markup=markup,
        parse_mode='HTML'
    )

@bot.message_handler(func=lambda message: message.text == "📍 Найти по местоположению")
def ask_for_location(message):
    markup = types.InlineKeyboardMarkup()
    markup.row(
        types.InlineKeyboardButton("1 км", callback_data='radius_1000'),
        types.InlineKeyboardButton("3 км", callback_data='radius_3000')
    )
    markup.row(
        types.InlineKeyboardButton("5 км", callback_data='radius_5000'),
        types.InlineKeyboardButton("10 км", callback_data='radius_10000')
    )
    
    bot.send_message(
        message.chat.id,
        "Выберите радиус поиска:",
        reply_markup=markup
    )

@bot.message_handler(func=lambda message: message.text == "🔍 Найти по адресу")
def ask_for_address(message):
    msg = bot.send_message(message.chat.id, "Введите адрес для поиска АЗС (например: Москва, Тверская 10):")
    bot.register_next_step_handler(msg, process_address_step1)

def process_address_step1(message):
    address = message.text.strip()
    if not address:
        bot.send_message(message.chat.id, "❌ Вы не ввели адрес. Попробуйте снова.")
        return
    
    user_data[message.from_user.id] = {'address': address}
    
    markup = types.InlineKeyboardMarkup()
    markup.row(
        types.InlineKeyboardButton("1 км", callback_data='address_radius_1000'),
        types.InlineKeyboardButton("3 км", callback_data='address_radius_3000')
    )
    markup.row(
        types.InlineKeyboardButton("5 км", callback_data='address_radius_5000'),
        types.InlineKeyboardButton("10 км", callback_data='address_radius_10000')
    )
    
    bot.send_message(
        message.chat.id,
        "Выберите радиус поиска:",
        reply_markup=markup
    )

@bot.callback_query_handler(func=lambda call: call.data.startswith('address_radius_'))
def handle_address_radius(call):
    user_id = call.from_user.id
    radius = int(call.data.split('_')[2])
    
    if user_id not in user_data or 'address' not in user_data[user_id]:
        bot.answer_callback_query(call.id, "❌ Адрес не найден. Попробуйте снова.")
        return
    
    address = user_data[user_id]['address']
    bot.answer_callback_query(call.id, f"Ищем АЗС в радиусе {radius//1000} км от {address}")
    
    bot.send_message(
        call.message.chat.id,
        f"🔍 Ищем координаты для адреса: {address}...",
        reply_markup=types.ReplyKeyboardRemove()
    )
    
    coords = geocode_address(address)
    if not coords:
        bot.send_message(
            call.message.chat.id,
            "❌ Не удалось найти координаты для этого адреса.\n"
            "Попробуйте уточнить адрес или ввести его в другом формате."
        )
        return
    
    lat, lon = coords
    
    cursor.execute('''
    INSERT INTO search_history (user_id, latitude, longitude, radius, search_date)
    VALUES (?, ?, ?, ?, datetime('now'))''', (user_id, lat, lon, radius))
    conn.commit()
    
    bot.send_message(
        call.message.chat.id,
        f"📍 Найденные координаты: {lat:.6f}, {lon:.6f}\n"
        f"🔎 Ищем АЗС в радиусе {radius//1000} км...",
        reply_markup=types.ReplyKeyboardRemove()
    )
    
    stations = find_gas_stations_2gis(lat, lon, radius)
    if not stations:
        bot.send_message(
            call.message.chat.id,
            f"❌ В радиусе {radius//1000} км не найдено ни одной АЗС.\n"
            "Попробуйте увеличить радиус поиска или выбрать другое место."
        )
        return
    
    user_data[user_id] = {
        'stations': stations,
        'current_index': 0,
        'from_favorites': False
    }
    
    show_station_card(call.message.chat.id, user_id, 0)

@bot.message_handler(func=lambda message: message.text == "❤️ Мои избранные АЗС")
def show_favorites(message):
    user_id = message.from_user.id
    cursor.execute('''
    SELECT station_id, station_name, station_address, station_lat, station_lon 
    FROM favorites 
    WHERE user_id = ?
    ORDER BY added_date DESC''', (user_id,))
    
    favorites = cursor.fetchall()
    if not favorites:
        bot.send_message(
            message.chat.id,
            "❌ У вас пока нет избранных АЗС.\n"
            "Вы можете добавить АЗС в избранное при просмотре результатов поиска.",
            reply_markup=types.ReplyKeyboardRemove()
        )
        return
    
    stations = []
    for fav in favorites:
        station = {
            'id': fav[0],
            'name': fav[1],
            'address_name': fav[2],
            'point': {'lat': fav[3], 'lon': fav[4]},
            'distance': 0
        }
        stations.append(station)
    
    user_data[user_id] = {
        'stations': stations,
        'current_index': 0,
        'from_favorites': True
    }
    
    show_station_card(message.chat.id, user_id, 0)

@bot.callback_query_handler(func=lambda call: call.data.startswith('radius_'))
def handle_radius(call):
    radius = int(call.data.split('_')[1])
    bot.answer_callback_query(call.id, f"Радиус: {radius//1000} км")
    
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    markup.add(types.KeyboardButton("📍 Отправить местоположение", request_location=True))
    
    bot.send_message(
        call.message.chat.id,
        f"🔍 Ищем АЗС в радиусе <b>{radius//1000} км</b>...\n"
        "Нажмите кнопку ниже, чтобы отправить свое местоположение:",
        reply_markup=markup,
        parse_mode='HTML'
    )
    
    bot.register_next_step_handler(
        call.message,
        lambda m: handle_location(m, radius)
    )

def handle_location(message, radius):
    if not message.location:
        bot.send_message(
            message.chat.id,
            "❌ Вы не отправили местоположение.\n"
            "Пожалуйста, нажмите кнопку '📍 Отправить местоположение'.",
            reply_markup=types.ReplyKeyboardRemove()
        )
        return
    
    user_id = message.from_user.id
    lat = message.location.latitude
    lon = message.location.longitude
    
    cursor.execute('''
    INSERT INTO search_history (user_id, latitude, longitude, radius, search_date)
    VALUES (?, ?, ?, ?, datetime('now'))''', (user_id, lat, lon, radius))
    conn.commit()
    
    bot.send_message(
        message.chat.id,
        f"📍 Ваши координаты: {lat:.6f}, {lon:.6f}\n"
        f"🔎 Ищем АЗС в радиусе {radius//1000} км...",
        reply_markup=types.ReplyKeyboardRemove()
    )
    
    stations = find_gas_stations_2gis(lat, lon, radius)
    if not stations:
        bot.send_message(
            message.chat.id,
            f"❌ В радиусе {radius//1000} км не найдено ни одной АЗС.\n"
            "Попробуйте увеличить радиус поиска или выбрать другое место."
        )
        return
    
    user_data[user_id] = {
        'stations': stations,
        'current_index': 0,
        'from_favorites': False
    }
    
    show_station_card(message.chat.id, user_id, 0)

def show_station_card(chat_id, user_id, index):
    if user_id not in user_data or 'stations' not in user_data[user_id]:
        bot.send_message(
            chat_id,
            "❌ Данные устарели. Пожалуйста, выполните новый поиск.",
            reply_markup=types.ReplyKeyboardRemove()
        )
        return
    
    stations = user_data[user_id]['stations']
    if index < 0:
        index = len(stations) - 1
    elif index >= len(stations):
        index = 0
    
    station = stations[index]
    show_distance = not user_data[user_id].get('from_favorites', False)
    card_text, markup = create_station_card(station, index, len(stations), user_id, show_distance)
    
    user_data[user_id]['current_index'] = index
    
    if 'last_message_id' in user_data[user_id]:
        try:
            bot.edit_message_text(
                chat_id=chat_id,
                message_id=user_data[user_id]['last_message_id'],
                text=card_text,
                reply_markup=markup,
                parse_mode='HTML'
            )
            return
        except:
            pass
    
    msg = bot.send_message(chat_id, card_text, reply_markup=markup, parse_mode='HTML')
    user_data[user_id]['last_message_id'] = msg.message_id

@bot.callback_query_handler(func=lambda call: call.data.startswith(('prev_', 'next_')))
def handle_navigation(call):
    user_id = call.from_user.id
    if user_id not in user_data or 'stations' not in user_data[user_id]:
        bot.answer_callback_query(call.id, "❌ Данные устарели. Выполните новый поиск.")
        return
    
    current_index = user_data[user_id]['current_index']
    new_index = current_index - 1 if call.data.startswith('prev_') else current_index + 1
    
    show_station_card(call.message.chat.id, user_id, new_index)
    bot.answer_callback_query(call.id)

@bot.callback_query_handler(func=lambda call: call.data.startswith('fav_'))
def handle_favorite(call):
    user_id = call.from_user.id
    parts = call.data.split('_')
    station_id = parts[1]
    index = int(parts[2])
    
    if user_id not in user_data or 'stations' not in user_data[user_id]:
        bot.answer_callback_query(call.id, "❌ Данные устарели.")
        return
    
    stations = user_data[user_id]['stations']
    if index < 0 or index >= len(stations):
        bot.answer_callback_query(call.id, "❌ Неверный индекс.")
        return
    
    station = stations[index]
    
    cursor.execute('SELECT 1 FROM favorites WHERE user_id = ? AND station_id = ?', (user_id, station_id))
    is_favorite = cursor.fetchone() is not None
    
    if is_favorite:
        cursor.execute('DELETE FROM favorites WHERE user_id = ? AND station_id = ?', (user_id, station_id))
        conn.commit()
        bot.answer_callback_query(call.id, "❌ Удалено из избранного")
    else:
        point = station.get('point', {})
        cursor.execute('''
        INSERT INTO favorites (user_id, station_id, station_name, station_address, station_lat, station_lon, added_date)
        VALUES (?, ?, ?, ?, ?, ?, datetime('now'))''',
        (user_id, station_id, station.get('name'), station.get('address_name'), 
         point.get('lat'), point.get('lon')))
        conn.commit()
        bot.answer_callback_query(call.id, "❤️ Добавлено в избранное")
    
    show_station_card(call.message.chat.id, user_id, index)

if __name__ == '__main__':
    print("Бот запущен...")
    bot.infinity_polling()