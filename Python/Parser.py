import csv

class CryptoCurrency:
    def __init__(self, name, symbol, price, market_cap):
        self.name = name
        self.symbol = symbol
        self.price = price
        self.market_cap = market_cap

def load_currencies_from_csv(filename):
    currencies = []
    with open(filename, 'r', newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',', quotechar='"')
        next(reader)  
        for row in reader:
            name, symbol, price, market_cap = row
            price = float(price.replace(',', '.'))
            market_cap = float(market_cap.replace(',', '.'))
            currency = CryptoCurrency(name, symbol, price, market_cap)
            currencies.append(currency)
    return currencies

def find_currencies(currencies, partial_name):
    found_currencies = []
    for currency in currencies:
        if partial_name.lower() in currency.name.lower():
            found_currencies.append(currency)
    return found_currencies

def print_all_currencies(currencies):
    for currency in currencies:
        print(f"Название: {currency.name}")
        print(f"Символ: {currency.symbol}")
        price_str = f"{currency.price:.20f}".rstrip('0').rstrip('.')
        print(f"Цена: {price_str} USD")
        print(f"Рыночная капитализация: {currency.market_cap} USD")
        print()

filename = 'currencies24.csv'
currencies = load_currencies_from_csv(filename)
    
print("Список всех криптовалют:")
print_all_currencies(currencies)
print()
    
while True:
    search_name = input("Введите часть или полное название криптовалюты (или 'exit' для выхода): ")
    if search_name.lower() == 'exit':
        break
        
    found_currencies = find_currencies(currencies, search_name)
    if found_currencies:
        print("Найденные криптовалюты:")
        for currency in found_currencies:
            print(f"Название: {currency.name}")
            print(f"Символ: {currency.symbol}")
            price_str = f"{currency.price:.20f}".rstrip('0').rstrip('.')
            print(f"Цена: {price_str} USD")
            print(f"Рыночная капитализация: {currency.market_cap} USD")
            print()
    else:
        print("Криптовалюты с таким названием не найдены.")              
