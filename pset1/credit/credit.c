#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get Number
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 1);

    //Calculate Checksum

    //Even Digits
    int two, four, six, eight;
    long ten, twelve, fourteen, sixteen;

    two = ((card % 100) - (card % 10)) / 10;
    four = ((card % 10000) - (card % 1000)) / 1000;
    six = ((card % 1000000) - (card % 100000)) / 100000;
    eight = ((card % 100000000) - (card % 10000000)) / 10000000;
    ten = ((card % 10000000000) - (card % 1000000000)) / 1000000000;
    twelve = ((card % 1000000000000) - (card % 100000000000)) / 100000000000;
    fourteen = ((card % 100000000000000) - (card % 10000000000000)) / 10000000000000;
    sixteen = ((card % 10000000000000000) - (card % 1000000000000000)) / 1000000000000000;

    //x2
    int atwo, afour, asix, aeight, aten, atwelve, afourteen, asixteen;
    int btwo, bfour, bsix, beight, bten, btwelve, bfourteen, bsixteen;
    int half;

    atwo = two * 2;
    afour = four * 2;
    asix = six * 2;
    aeight = eight * 2;
    aten = ten * 2;
    atwelve = twelve * 2;
    afourteen = fourteen * 2;
    asixteen = sixteen * 2;

    //Add all digits
    btwo = (((atwo % 100) - (atwo % 10)) / 10) + (atwo % 10);
    bfour = (((afour % 100) - (afour % 10)) / 10) + (afour % 10);
    bsix = (((asix % 100) - (asix % 10)) / 10) + (asix % 10);
    beight = (((aeight % 100) - (aeight % 10)) / 10) + (aeight % 10);
    bten = (((aten % 100) - (aten % 10)) / 10) + (aten % 10);
    btwelve = (((atwelve % 100) - (atwelve % 10)) / 10) + (atwelve % 10);
    bfourteen = (((afourteen % 100) - (afourteen % 10)) / 10) + (afourteen % 10);
    bsixteen = (((asixteen % 100) - (asixteen % 10)) / 10) + (asixteen % 10);

    half = btwo + bfour + bsix + beight + bten + btwelve + bfourteen + bsixteen;

    //Rest of digits
    int one, three, five, seven;
    long nine, eleven, thirteen, fifteen;
    int whole;

    one = (card % 10);
    three = ((card % 1000) - (card % 100)) / 100;
    five = ((card % 100000) - (card % 10000)) / 10000;
    seven = ((card % 10000000) - (card % 1000000)) / 1000000;
    nine = ((card % 1000000000) - (card % 100000000)) / 100000000;
    eleven = ((card % 100000000000) - (card % 10000000000)) / 10000000000;
    thirteen = ((card % 10000000000000) - (card % 1000000000000)) / 1000000000000;
    fifteen = ((card % 1000000000000000) - (card % 100000000000000)) / 100000000000000;

    //American Express
    int amex;
    amex = ((card % 1000000000000000) - (card % 10000000000000)) / 10000000000000;
    //MasterCard
    int master;
    master = ((card % 10000000000000000) - (card % 100000000000000)) / 100000000000000;
    //Visa
    int sixvisa, threevisa;
    sixvisa = ((card % 10000000000000000) - (card % 1000000000000000)) / 1000000000000000;
    threevisa = ((card % 10000000000000) - (card % 1000000000000)) / 1000000000000;


    //check for zero
    if (whole % 10 == 0)
    {
        //sixteen
        if (card < 6000000000000000 && card > 1000000000000000)
        {
            if (master == 51 || master == 52 || master == 53 || master == 54 || master == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (sixvisa == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //fifteen
        else if (card < 600000000000000 && card > 100000000000000)
        {
            if (amex == 34 || amex == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //thirteen
        else if (card < 10000000000000)
        {
            if (threevisa == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
