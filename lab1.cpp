#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 80
using namespace std;

union special_float {
    float actual;
    int auxiliary;
};

void ClearStr()
{
    cout << "\nTo continue press any button...";
    _getch();
    system("cls");
}

void Print(bool state, int valInt = 0, unsigned char valUC = 0) {
    if (state) {
        for (int i = 31; i >= 0; --i)
            cout << ((valInt >> i) & 1);
    }
    else {
        for (int i = 7; i >= 0; --i)
            cout << ((valUC >> i) & 1);
    }
    cout << endl;
    ClearStr();
}

void CheckSignBit(int NumberBit, char* Check)
{
    int len = 0;
    bool Flag;

    do
    {
        len = 0;
        Flag = false;
        cout << "Enter a bit sequence of length " << NumberBit << ": ";
        fgets(Check, NumberBit + 2, stdin);
        fflush(stdin);
        for (int i = 0; Check[i] != '\n' && Check[i]; ++i, ++len);
        Check[len] = 0;
        system("cls");
        if (Check[0] == 0)
        {
            cout << "You entered an empty string! Try again..." << endl;
            ClearStr();
            Flag = true;
        }
        else if (len < NumberBit)
        {
            cout << "The sequence of bits shorter then " << NumberBit << "! Try again..." << endl;
            ClearStr();
            Flag = true;
        }
        else if (len > NumberBit)
        {
            cout << "The sequence of bits longer then " << NumberBit << "! Try again..." << endl;
            ClearStr();
            Flag = true;
        }
        else
        {
            for (int i = 0; i < NumberBit && !Flag; ++i)
            {
                if (Check[i] != '0' && Check[i] != '1')
                {
                    cout << "The sequence of bits must consist only of 0 and 1! Try again..." << endl;
                    ClearStr();
                    Flag = true;
                }
            }
        }

    } while (Flag);
}

int CheckHighBit(bool state, int NumberBit)
{
    bool Flag;
    int MaxPos;
    char Check[MAX];
    MaxPos = (state) ? 31 : 7;
    Flag = 0;
    while (Flag == 0)
    {
        cout << "Enter the highest bit between " << NumberBit - 1 << " and " << MaxPos << ": ";
        fgets(Check, MAX, stdin);
        fflush(stdin);
        system("cls");
        if (Check[0] == '\n')
        {
            cout << "You entered an empty string! Try again..." << endl;
            ClearStr();
        }
        else if (Check[1] != '\n' && Check[1 + state] != '\n' || atoi(Check) < NumberBit - 1 || atoi(Check) > MaxPos)
        {
            cout << "The highest bit is a number from " << NumberBit - 1 << " to " << MaxPos << "! Try again..." << endl;
            ClearStr();
        }
        else
            Flag = 1;
    }
    return atoi(Check);
}

int CheckNumberBit(bool state)
{
    bool Flag;
    int MaxBits;
    char Check[MAX];
    MaxBits = (state) ? 32 : 8;
    Flag = 0;
    while (Flag == 0)
    {
        cout << "Enter the number of bits between 1 and " << MaxBits << ": ";
        fgets(Check, MAX, stdin);
        fflush(stdin);
        system("cls");
        if (Check[0] == '\n')
        {
            cout << "You entered an empty string! Try again...";
            ClearStr();
        }
        else if (Check[1] != '\n' && Check[1 + state] != '\n' || atoi(Check) > MaxBits || atoi(Check) < 1)
        {
            cout << "The number of bits is a number from 1 to " << MaxBits << "! Try again...";
            ClearStr();
        }
        else
            Flag = 1;
    }
    return atoi(Check);
}

void ChangeBit(bool state, int valInt = 0, unsigned char valUC = 0) {

    char SignBit[MAX];
    int NumberBit, HighBit, MaxBits;
    MaxBits = (state) ? 32 : 8;

    NumberBit = CheckNumberBit(state);
    if (NumberBit != MaxBits)
        HighBit = CheckHighBit(state, NumberBit);
    else
        HighBit = NumberBit - 1;
    CheckSignBit(NumberBit, SignBit);

    if (state) {
        special_float tmp;
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                valInt |= (1 << (HighBit - i));
            else
                valInt &= ~(1 << (HighBit - i));
        }
        tmp.auxiliary = valInt;
        cout << tmp.actual << endl;
        Print(state, valInt);
    }
    else {
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                valUC |= (1 << (HighBit - i));
            else
                valUC &= ~(1 << (HighBit - i));
        }
        cout << valUC << endl;
        Print(state, 0, valUC);
    }
}

char UnsCharCheck()
{
    bool Flag;
    char Check[MAX];
    Flag = 0;
    while (Flag == 0)
    {
        cout << "Enter a single character: ";
        fgets(Check, MAX, stdin);
        fflush(stdin);
        system("cls");
        if (Check[0] == '\n')
        {
            cout << "You entered an empty string! Try again...";
            ClearStr();
        }
        else if (Check[1] != '\n')
        {
            cout << "You must enter one character! Try again...";
            ClearStr();
        }
        else
            Flag = 1;
    }
    return Check[0];
}

float getFloatValue() {

    bool
        errorFlag = false,
        dotFlag = false,
        expFlag = false,
        lineFlag = false,
        expAppearanceFlag = false;

    int
        sizeBeforeDot = 0,
        sizeAfterDot = 0,
        expSize = 0;

    char
        sign = '+',
        exp[4] = {};

    char str[51];

    float
        val = 0,
        degreeBeforeDot[] = { 0.1f, 0.01f, 0.001f, 0.0001f, 0.00001f, 0.000001f, 0.0000001f, 0.00000001f };

    do {
        errorFlag = false;
        dotFlag = false;
        expFlag = false;
        expAppearanceFlag = false;
        lineFlag = false;

        sizeBeforeDot = 0;
        sizeAfterDot = 0;
        expSize = 0;

        sign = '+';
        for (int i = 0; exp[i]; ++i)
            exp[i] = 0;

        val = 0;

        cout << "Enter float: ";
        fgets(str, 51, stdin);
        fflush(stdin);

        if (str[0] == '0' && (str[1] != '\n' && str[1] != '.'))
            errorFlag = true;

        if (str[0] == '\n' || str[0] == 'e' || str[0] == 'E')
            errorFlag = true;

        for (int i = 0; str[i] != '\n' && str[i] && !errorFlag; ++i) {
            
            if ((str[i] >= '0' && str[i] <= '9') ||
                str[i] == 'e' || str[i] == 'E' ||
                str[i] == '+' || str[i] == '-' || str[i] == '.') {

                if ((str[i] == '+' || str[i] == '-') && !expAppearanceFlag)
                        errorFlag = true;

                if (expAppearanceFlag)
                    expAppearanceFlag = false;

                if (str[i] == '.') {
                    if (!dotFlag)
                        dotFlag = true;
                    else
                        errorFlag = true;
                }

                if (str[i] == 'e' || str[i] == 'E') {
                    if (!expFlag) {
                        expFlag = true;
                        expAppearanceFlag = true;
                    }
                    else
                        errorFlag = true;
                }

                if (str[i] >= '0' && str[i] <= '9') {
                    if (expFlag) {
                        if (exp[0] != '0' || expSize != 2 || str[i] != '0') {
                            exp[expSize++] = str[i];
                            if (atoi(exp) + sizeBeforeDot > 39 || expSize > 2)
                                errorFlag = true;
                        }
                    }
                    else if (dotFlag) {
                        if (sizeAfterDot <= 9)
                            ++sizeAfterDot;
                        else
                            errorFlag = true;
                    }
                    else if (!dotFlag) {
                        ++sizeBeforeDot;
                        if (sizeBeforeDot > 39)
                            errorFlag = true;
                    }
                }

                lineFlag = true;

            }
        }

        /*if (!errorFlag) {
            if (exp[0]) {
                int step = atoi(exp);
                for (int i = 0; i < step; ++i) {
                    (sign == '+') ? val *= 10.f : val *= 0.1f;
                }
                if (isnan(val) || isinf(val))
                    errorFlag = true;
            }
            else if (expFlag)
                errorFlag = true;
        }*/
        
        if (!errorFlag) {
            val = (float)atof(str);
            if (isinf(val) || isnan(val))
                errorFlag = true;
        }

        if (errorFlag)
            cout << "That input is invalid. Please try again." << endl;

    } while (errorFlag);

    return val;
}

/*float getFloatValue() {
    char str[51];
    bool flag;
    float val = 0;
    int
        sizeBeforeDot,
        sizeAfterDot,
        len;
    do {
        val = 0;
        len = 0;
        sizeBeforeDot = 0;
        sizeAfterDot = 0;
        flag = false;
        fgets(str, 51, stdin);
        fflush(stdin);
        for (int i = 0; str[i] != '\n' && str[i]; ++i, ++len);
        str[len] = 0;
        for (int i = 0; str[i] != '.' && str[i]; ++i, ++sizeBeforeDot);
        for (int i = sizeBeforeDot; (str[i] != 'e' || str[i] != 'E') && str[i]; ++i, ++sizeAfterDot);
        fflush(stdin);
        if (len == 0) {
            flag = true;
            cout << "You entered an empty string! Try again...";
            ClearStr();
        }
        else if (sizeBeforeDot > 38) {
            flag = true;
            cout << "MIN value is 1.175494351e-38, MAX value is 3.402823466e+38! Try again...";
            ClearStr();
        }
        else if (str[0] == '0' && (str[1] != '\n' && str[1] != '.')) {
            flag = true;
            cout << "The integer part of a number cannot start from zero if this integer part is not zero! Try again...";
            ClearStr();
        }
        else {
            if (str[0] == '0' && str[1] == '\n')
                val = 0;
            else {
                for (int i = 0; str[i] && !flag; ++i) {
                    if ((str[i] < '0' || str[i] > '9') &&
                        str[i] != 'e' && str[i] != 'E' &&
                        str[i] != '+' && str[i] != '-' &&
                        str[i] != '.') {
                        flag = true;
                        cout << "That input is invalid! Try again...";
                        ClearStr();
                    }
                }
                if (!flag) {
                    val = (float)atof(str);
                    if (val == 0 || isinf(val)) {
                        cout << "MIN value is 1.175494351e-38, MAX value is 3.402823466e+38! Try again...";
                        ClearStr();
                        flag = true;
                    }
                }
            }
        }
    } while (flag);

    return val;
}*/

bool getChoice(bool state) {
    const char* message = (state) ? "What type of value do you need?\nEnter 0, if you need unsigned char, or 1, if you need float: " :
        "Do you want repeat?\nEnter 1, if you want it, or 0, if not: ";
    char choice[3];
    bool flag;
    do {

        flag = false;
        cout << message;
        fgets(choice, 3, stdin);
        fflush(stdin);
        system("cls");

        if (choice[0] == '\n') {
            flag = true;
            cout << "You entered an empty string! Try again...";
            ClearStr();
        }
        else if (choice[1] != '\n' || (choice[0] != '0' && choice[0] != '1')) {
            flag = true;
            cout << "That input is invalid! Try again...";
            ClearStr();
        }

    } while (flag);

    return (bool)(choice[0] - '0');
}

int main() {
    unsigned char valUChar; // char value
    special_float valFloat; // float and int union value
    float val;
    bool
        choice,
        state;
    do {
        state = getChoice(1);    // user make choice

        if (state) {
            cin >> val;
            getchar();
            val = val;
            valFloat.actual = getFloatValue();
            valFloat.actual = valFloat.actual;
            Print(state, valFloat.auxiliary);
            ChangeBit(state, valFloat.auxiliary);
        }
        else {
            valUChar = UnsCharCheck();
            Print(state, 0, valUChar);
            ChangeBit(state, 0, valUChar);
        }

        choice = getChoice(0);

    } while (choice);

    return 0;
}

// g++ lab1.cpp -std=c++11 -o test
