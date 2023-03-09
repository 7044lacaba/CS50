# TODO
import cs50


def main():

    # Get card number
    while True:
        card = (cs50.get_int("Number: "))
        if card > 1:
            break

    # checksum

    two = ((card % 100) - (card % 10)) / 10
    four = ((card % 10000) - (card % 1000)) / 1000
    six = ((card % 1000000) - (card % 100000)) / 100000
    eight = ((card % 100000000) - (card % 10000000)) / 10000000
    ten = ((card % 10000000000) - (card % 1000000000)) / 1000000000
    twelve = ((card % 1000000000000) - (card % 100000000000)) / 100000000000
    fourteen = ((card % 100000000000000) - (card % 10000000000000)) / 10000000000000
    sixteen = ((card % 10000000000000000) - (card % 1000000000000000)) / 1000000000000000

    atwo = two * 2
    afour = four * 2
    asix = six * 2
    aeight = eight * 2
    aten = ten * 2
    atwelve = twelve * 2
    afourteen = fourteen * 2
    asixteen = sixteen * 2

    btwo = (((atwo % 100) - (atwo % 10)) / 10) + (atwo % 10)
    bfour = (((afour % 100) - (afour % 10)) / 10) + (afour % 10)
    bsix = (((asix % 100) - (asix % 10)) / 10) + (asix % 10)
    beight = (((aeight % 100) - (aeight % 10)) / 10) + (aeight % 10)
    bten = (((aten % 100) - (aten % 10)) / 10) + (aten % 10)
    btwelve = (((atwelve % 100) - (atwelve % 10)) / 10) + (atwelve % 10)
    bfourteen = (((afourteen % 100) - (afourteen % 10)) / 10) + (afourteen % 10)
    bsixteen = (((asixteen % 100) - (asixteen % 10)) / 10) + (asixteen % 10)

    half = btwo + bfour + bsix + beight + bten + btwelve + bfourteen + bsixteen

    one = (card % 10)
    three = ((card % 1000) - (card % 100)) / 100
    five = ((card % 100000) - (card % 10000)) / 10000
    seven = ((card % 10000000) - (card % 1000000)) / 1000000
    nine = ((card % 1000000000) - (card % 100000000)) / 100000000
    eleven = ((card % 100000000000) - (card % 10000000000)) / 10000000000
    thirteen = ((card % 10000000000000) - (card % 1000000000000)) / 1000000000000
    fifteen = ((card % 1000000000000000) - (card % 100000000000000)) / 100000000000000

    whole = half + one + three + five + seven + nine + eleven + thirteen + fifteen

    amex = ((card % 1000000000000000) - (card % 10000000000000)) / 10000000000000

    master = ((card % 10000000000000000) - (card % 100000000000000)) / 100000000000000

    sixvisa = ((card % 10000000000000000) - (card % 1000000000000000)) / 1000000000000000
    threevisa = ((card % 10000000000000) - (card % 1000000000000)) / 1000000000000

    if whole % 10 == 0:
        if card < 6000000000000000 and card > 1000000000000000:
            if master == 51 or master == 52 or master == 53 or master == 54 or master == 55:
                print("MASTERCARD")
            elif sixvisa == 4:
                print("VISA")
            else:
                print("INVALID")
        elif card < 600000000000000 and card > 100000000000000:
            if amex == 34 or amex == 37:
                print("AMEX")
            else:
                print("INVALID")
        elif card < 10000000000000:
            if threevisa == 4:
                print("VISA")
            else:
                print("INVALID")
    else:
        print("INVALID")


main()