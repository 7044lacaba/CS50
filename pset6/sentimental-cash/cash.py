# TODO
from cs50 import get_float

change = 0
coin = 0

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

while True:
    if change > 0.24:
        change = change - 0.25
        coin += 1
    elif change > 0.09:
        change = change - 0.10
        coin += 1
    elif change > 0.04:
        change = change - 0.05
        coin += 1
    elif change < 0.04:
        change = change * 100
        coin = coin + change
        break

print(round(coin))
