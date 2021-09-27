from cs50 import get_float
from math import floor

def main():
    while True:
        dollar = get_float("Change owed: ")
        cent = floor(dollar * 100) #round to 100
        if cent > 0:
            break

    # used // to divide with integral result (discard remainder)
    quarters = cent // 25 #get number of quaters
    dimes = (cent % 25) // 10 #get number of dimes
    nickels = ((cent % 25) % 10) // 5 #get number of nickels
    pennies = ((cent % 25) % 10) % 5 #get number of pennies

    #get number of all coins
    print(f"{quarters + dimes + nickels + pennies}")

main()