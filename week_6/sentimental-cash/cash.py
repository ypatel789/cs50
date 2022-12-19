money = 0
while money <= 0:
    money = input("Change Owed: ")
    while money.isalpha() == True:
        money = input("Change Owed: ")
    money = float(money)


coins = 0

change = money * 100

while change >= 25:
    change = change - 25
    coins += 1

while change >= 10:
    change = change - 10
    coins += 1

while change >= 5:
    change = change - 5
    coins += 1

while change >= 1:
    change = change - 1
    coins += 1

print(coins)