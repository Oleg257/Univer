from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager
import telebot
from telebot import types
import sqlite3
import time
from datetime import datetime, timedelta
import pytz  

bot = telebot.TeleBot("")

conn = sqlite3.connect("flight_history.db", check_same_thread=False, timeout=10)
cursor = conn.cursor()
cursor.execute("PRAGMA journal_mode=WAL")

cursor.execute("""
CREATE TABLE IF NOT EXISTS search_history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    chat_id INTEGER,
    flight_number TEXT,
    flight_type TEXT,
    search_date TEXT,
    flight_date TEXT,
    search_time TIMESTAMP
)
""")
conn.commit()

user_data = {}

def normalize_input(text):
    if not text:
        return text
    return text.strip().title()

def create_date_keyboard():
    markup = types.InlineKeyboardMarkup(row_width=3)
    now = datetime.now()
    yesterday = now - timedelta(days=1)
    tomorrow = now + timedelta(days=1)
    
    buttons = [
        types.InlineKeyboardButton("Вчера", callback_data="date_yesterday"),
        types.InlineKeyboardButton("Сегодня", callback_data="date_today"),
        types.InlineKeyboardButton("Завтра", callback_data="date_tomorrow"),
    ]
    
    markup.add(*buttons)
    return markup

def create_main_keyboard():
    markup = types.InlineKeyboardMarkup(row_width=2)
    markup.add(
        types.InlineKeyboardButton("По номеру рейса", callback_data="search_flight"),
        types.InlineKeyboardButton("По городу", callback_data="search_city"),
        types.InlineKeyboardButton("📜 История поиска", callback_data="history")
    )
    return markup

def get_flight_date(date_type):
    """Возвращает дату в зависимости от выбранного типа (вчера/сегодня/завтра)"""
    now = datetime.now()
    if date_type == "yesterday":
        return (now - timedelta(days=1)).strftime("%d.%m.%Y")
    elif date_type == "tomorrow":
        return (now + timedelta(days=1)).strftime("%d.%m.%Y")
    else:  
        return now.strftime("%d.%m.%Y")

def get_current_datetime():
    """Возвращает текущие дату и время в Новосибирске"""
    return datetime.now()

def parse_flight_date(date_str, selected_date):
    """Парсит дату рейса из строки на сайте"""
    try:
        if not date_str or date_str == "N/A":
            return selected_date
        
        parts = date_str.split()
        if len(parts) >= 2:
            date_part = parts[1]
            try:
                parsed_date = datetime.strptime(date_part, "%d.%m.%Y")
                return parsed_date.strftime("%d.%m.%Y")
            except:
                return selected_date
        
        return selected_date
    except:
        return selected_date

def get_flight_info(flight_number, date_type):
    normalized_flight_number = normalize_input(flight_number)
    selected_date = get_flight_date(date_type)
    
    options = webdriver.ChromeOptions()
    options.add_argument("--headless")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

    try:
        url = f"https://tolmachevo.ru/passengers/information/timetable/?flightDate={selected_date}"
        driver.get(url)
        wait = WebDriverWait(driver, 5)
        switch_to_day(driver, date_type)
        time.sleep(2)

        wait.until(EC.presence_of_element_located((By.CLASS_NAME, "flight-item")))

        def find_flight():
            flight_items = driver.find_elements(By.CLASS_NAME, "flight-item")
            for flight_item in flight_items:
                try:
                    flight_header = flight_item.find_element(By.CLASS_NAME, "fi-header")
                    flight_no_element = flight_header.find_element(By.CLASS_NAME, "tth-flight")
                    flight_no = flight_no_element.text.strip()
                    
                    if normalize_input(flight_no) == normalized_flight_number:
                        destination = flight_header.find_element(By.CLASS_NAME, "tth-destination").text.strip()
                        status = flight_header.find_element(By.CLASS_NAME, "tth-status").text.strip()
                        terminal = flight_header.find_element(By.CLASS_NAME, "tth-terminal").text.strip() if flight_header.find_elements(By.CLASS_NAME, "tth-terminal") else "N/A"

                        schedule_time = ""
                        estimated_time = ""
                        try:
                            schedule_time = flight_header.find_element(By.CLASS_NAME, "tth-time").text.strip()
                            flight_date = parse_flight_date(schedule_time, selected_date)
                        except:
                            schedule_time = "N/A"
                            flight_date = selected_date
                        try:
                            estimated_time = flight_header.find_element(By.CLASS_NAME, "tth-time-count").text.strip()
                        except:
                            estimated_time = "N/A"

                        flight_type = "Вылет" if "tts-departure" in driver.find_element(By.CLASS_NAME, "tts-departure").get_attribute("class") else "Прилет"

                        return {
                            'flight': flight_no,
                            'route': destination,
                            'scheduled_time': schedule_time,
                            'estimated_time': estimated_time,
                            'terminal': terminal,
                            'status': status,
                            'type': flight_type,
                            'date': flight_date,
                            'search_date': selected_date
                        }
                except Exception as e:
                    print(f"Ошибка при обработке рейса: {e}")
            return None

        departure_tab = driver.find_element(By.CLASS_NAME, "tts-departure")
        departure_tab.click()
        time.sleep(2)
        flight_data = find_flight()
        
        if not flight_data:
            arrival_tab = driver.find_element(By.CLASS_NAME, "tts-arrival")
            arrival_tab.click()
            time.sleep(2)
            flight_data = find_flight()
            if flight_data:
                flight_data['type'] = "Прилет"

        driver.quit()
        return flight_data

    except Exception as e:
        print(f"Произошла ошибка: {e}")
        driver.quit()
        return None

def get_flights_by_city(city, date_type, driver=None):
    normalized_city = normalize_input(city)
    selected_date = get_flight_date(date_type)

    options = webdriver.ChromeOptions()
    options.add_argument("--headless")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

    try:
        driver.get("https://tolmachevo.ru/passengers/information/timetable/ ")
        time.sleep(5)

        switch_to_day(driver, date_type)
        time.sleep(2)

        flights = []
        
        departure_tab = driver.find_element(By.CLASS_NAME, "tts-departure")
        if "active" not in departure_tab.get_attribute("class"):
            departure_tab.click()
        time.sleep(2)

        flight_items = driver.find_elements(By.CLASS_NAME, "flight-item")
        for flight_item in flight_items:
            try:
                flight_header = flight_item.find_element(By.CLASS_NAME, "fi-header")
                destination = flight_header.find_element(By.CLASS_NAME, "tth-destination").text.strip()

                if normalized_city in normalize_input(destination):
                    flight_data = process_flight_item(flight_item, flight_header, selected_date, "Вылет")
                    if flight_data:
                        flights.append(flight_data)
            except Exception as e:
                print(f"Ошибка при обработке рейса: {e}")

        arrival_tab = driver.find_element(By.CLASS_NAME, "tts-arrival")
        if "active" not in arrival_tab.get_attribute("class"):
            arrival_tab.click()
        time.sleep(2)

        flight_items = driver.find_elements(By.CLASS_NAME, "flight-item")
        for flight_item in flight_items:
            try:
                flight_header = flight_item.find_element(By.CLASS_NAME, "fi-header")
                destination = flight_header.find_element(By.CLASS_NAME, "tth-destination").text.strip()

                if normalized_city in normalize_input(destination):
                    flight_data = process_flight_item(flight_item, flight_header, selected_date, "Прилет")
                    if flight_data:
                        flights.append(flight_data)
            except Exception as e:
                print(f"Ошибка при обработке рейса: {e}")

        driver.quit()
        return flights

    except Exception as e:
        print(f"Произошла ошибка: {e}")
        driver.quit()
        return []
    
def switch_to_day(driver, day):
    """Переключает сайт на заданный день (yesterday, today, tomorrow)"""
    try:
        WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.CLASS_NAME, "tt-days-switcher"))
        )

        day_buttons = driver.find_elements(By.XPATH, "//span[@data-tt-day='yesterday' or @data-tt-day='today' or @data-tt-day='tomorrow']")       

        for button in day_buttons:
            if button.get_attribute("data-tt-day") == day:
                if "active" not in button.get_attribute("class"):
                    button.click()
                break
    except Exception as e:
        print(f"Ошибка при переключении дня: {e}")

def process_flight_item(flight_item, flight_header, selected_date, flight_type):
    try:
        flight_no = flight_header.find_element(By.CLASS_NAME, "tth-flight").text.strip()
        destination = flight_header.find_element(By.CLASS_NAME, "tth-destination").text.strip()
        status = flight_header.find_element(By.CLASS_NAME, "tth-status").text.strip()
        terminal = flight_header.find_element(By.CLASS_NAME, "tth-terminal").text.strip() if flight_header.find_elements(By.CLASS_NAME, "tth-terminal") else "N/A"
        schedule_time = ""
        estimated_time = ""

        try:
            schedule_time = flight_header.find_element(By.CLASS_NAME, "tth-time").text.strip()
            flight_date = parse_flight_date(schedule_time, selected_date)
        except:
            schedule_time = "N/A"
            flight_date = selected_date

        try:
            estimated_time = flight_header.find_element(By.CLASS_NAME, "tth-time-count").text.strip()
        except:
            estimated_time = "N/A"

        return {
            'flight': flight_no,
            'route': destination,
            'scheduled_time': schedule_time,
            'estimated_time': estimated_time,
            'terminal': terminal,
            'status': status,
            'date': flight_date,
            'search_date': selected_date,
            'type': flight_type  
        }
    except Exception as e:
        print(f"Ошибка при обработке рейса: {e}")
        return None

def format_flight_info(flights, limit=15):  
    formatted = []
    for flight in flights[:limit]:  
        formatted.append(
            f"✈️ Рейс: {flight['flight']}\n"
            f"📅 Дата рейса: {flight['date']}\n"
            f"🛫 Тип: {flight.get('type', 'Не указано')}\n"
            f"📍 Маршрут: {flight['route']}\n"
            f"🕒 По расписанию: {flight['scheduled_time']}\n"
            f"🔄 Расчетное время: {flight['estimated_time']}\n"
            f"🚪 Терминал: {flight['terminal']}\n"
            f"📊 Статус: {flight['status']}\n"
            "────────────────────\n"
        )
    return "\n".join(formatted)

def save_search_history(chat_id, query, flight_type=None, flight_date=None, search_date=None):
    max_retries = 3
    current_time = get_current_datetime().strftime("%Y-%m-%d %H:%M:%S")
    
    for attempt in range(max_retries):
        try:
            with conn:
                cursor.execute("""
                INSERT INTO search_history (chat_id, flight_number, flight_type, search_date, flight_date, search_time)
                VALUES (?, ?, ?, ?, ?, ?)
                """, (chat_id, query, flight_type, search_date, flight_date, current_time))
            break
        except sqlite3.OperationalError as e:
            if attempt == max_retries - 1:
                print(f"Не удалось сохранить историю после {max_retries} попыток: {e}")
            time.sleep(0.1)

def show_search_history(chat_id):
    cursor.execute("""
    SELECT flight_number, flight_type, search_date, flight_date, search_time 
    FROM search_history
    WHERE chat_id = ? 
    ORDER BY search_time DESC 
    LIMIT 10
    """, (chat_id,))
    history = cursor.fetchall()

    if not history:
        bot.send_message(chat_id, "История поиска пуста.")
        return

    formatted_history = []
    for i, (flight_number, flight_type, search_date, flight_date, search_time) in enumerate(history, 1):
        entry = f"{i}. {flight_number}"
        if flight_type:
            entry += f" ({flight_type})"
        entry += f" - Искали на {search_date}"
        if flight_date and flight_date != search_date:
            entry += f" (рейс на {flight_date})"
        entry += f" - {search_time.split()[1][:5]}"
        formatted_history.append(entry)

    response = "📜 История ваших поисков:\n\n" + "\n".join(formatted_history)
    bot.send_message(chat_id, response)

@bot.message_handler(commands=['start'])
def start(message):
    user_id = message.chat.id
    bot.send_message(user_id, 
                    "✈️ Привет! Я бот для проверки рейсов аэропорта Толмачево.\n"
                    "Выберите способ поиска:", 
                    reply_markup=create_main_keyboard())

@bot.callback_query_handler(func=lambda call: call.data == 'search_flight')
def search_flight(call):
    chat_id = call.message.chat.id
    user_data[chat_id] = {'step': 'enter_flight_number', 'search_type': 'flight'}
    bot.send_message(chat_id, "Выберите дату для поиска:", reply_markup=create_date_keyboard())

@bot.callback_query_handler(func=lambda call: call.data == 'search_city')
def search_city(call):
    chat_id = call.message.chat.id
    user_data[chat_id] = {'step': 'enter_city', 'search_type': 'city'}
    bot.send_message(chat_id, "Выберите дату для поиска:", reply_markup=create_date_keyboard())

@bot.callback_query_handler(func=lambda call: call.data.startswith('date_'))
def handle_date_selection(call):
    chat_id = call.message.chat.id
    date_type = call.data.split('_')[1]  # yesterday/today/tomorrow
    
    if 'search_type' not in user_data.get(chat_id, {}):
        bot.send_message(chat_id, "Пожалуйста, начните поиск заново.")
        return
    
    user_data[chat_id]['date_type'] = date_type
    
    if user_data[chat_id]['search_type'] == 'flight':
        bot.send_message(chat_id, "Введите номер рейса (например, S7 1234):")
    else:
        bot.send_message(chat_id, "Введите название города:")

@bot.callback_query_handler(func=lambda call: call.data == 'history')
def show_history(call):
    show_search_history(call.message.chat.id)

@bot.message_handler(func=lambda message: user_data.get(message.chat.id, {}).get('step') == 'enter_flight_number')
def handle_flight_number(message):
    user_id = message.chat.id
    flight_number = message.text.strip()
    
    if not flight_number:
        bot.send_message(user_id, "Пожалуйста, введите номер рейса.")
        return
    
    date_type = user_data.get(user_id, {}).get('date_type')
    
    bot.send_message(user_id, "🔍 Ищем рейс...")
    
    flight_info = get_flight_info(flight_number, date_type)
    
    if flight_info:
        response = format_flight_info([flight_info])
        bot.send_message(user_id, f"Информация о рейсе:\n\n{response}")
        save_search_history(
            user_id, 
            flight_number, 
            flight_info['type'],
            flight_info['date'],
            flight_info['search_date']
        )
    else:
        bot.send_message(user_id, "Рейс не найден.")
    
    user_data[user_id] = {}
    bot.send_message(user_id, "✈️ Выберите по чему будет следующий поиск рейсов:", reply_markup=create_main_keyboard())

@bot.message_handler(func=lambda message: user_data.get(message.chat.id, {}).get('step') == 'enter_city')
def handle_city(message):
    user_id = message.chat.id
    city = message.text.strip()
    if not city:
        bot.send_message(user_id, "Пожалуйста, введите название города.")
        return
    date_type = user_data.get(user_id, {}).get('date_type')
    bot.send_message(user_id, f"🔍 Ищем рейсы в город {city}...")
    flights = get_flights_by_city(city, date_type)
    if flights:
        response = format_flight_info(flights, limit=15)  
        bot.send_message(user_id, f"Найдены рейсы:\n{response}")
        if flights:
            save_search_history(
                user_id, 
                city, 
                None,  
                flights[0]['date'],
                flights[0]['search_date']
            )
    else:
        bot.send_message(user_id, "Рейсы не найдены.")
    user_data[user_id] = {}
    bot.send_message(user_id, "✈️ Выберите по чему будет следующий поиск рейсов:", reply_markup=create_main_keyboard())

if __name__ == "__main__":
    print("Бот запущен...")
    try:
        bot.polling(none_stop=True)
    finally:
        conn.close()