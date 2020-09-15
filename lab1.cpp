#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
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
}

void CheckSignBit(int NumberBit, char* Check)
{
    bool Flag;

    do
    {
        Flag = false;
        cout << "Enter the bit sequence: ";
        fgets(Check, NumberBit + 2, stdin);
        fflush(stdin);
        system("cls");
        if (Check[0] == '\n')
        {
            cout << "You entered an empty string! Try again..." << endl;
            ClearStr();
            Flag = true;
        }
        else if (Check[NumberBit] != '\n')
        {
            cout << "The sequence of bits longer then " << NumberBit << "! Try again..." << endl;
            ClearStr();
            Flag = true;
        }
        else
        {
            Check[NumberBit] = '\0';
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
        cout << "Enter the highest bit: ";
        fgets(Check, MAX, stdin);
        fflush(stdin);
        system("cls");
        if (Check[0] == '\n')
        {
            cout << "You entered an empty string! Try again..." << endl;
            ClearStr();
        }
        else if (Check[1] != '\n' && Check[1 + state] != '\n' || atoi(Check) < NumberBit - 1)
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
        cout << "Enter the number of bits: ";
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
    int NumberBit, HighBit;

    NumberBit = CheckNumberBit(state);
    HighBit = CheckHighBit(state, NumberBit);
    CheckSignBit(NumberBit, SignBit);

    if (state) {
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                valInt |= (1 << (HighBit - i));
            else
                valInt &= ~(1 << (HighBit - i));
        }
        Print(state, valInt);
    }
    else {
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                valUC |= (1 << (HighBit - i));
            else
                valUC &= ~(1 << (HighBit - i));
        }
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

/*float getFloatValue() {

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
        c = 0,
        exp[4] = {};

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
        c = 0;
        for (int i = 0; exp[i]; ++i)
            exp[i] = 0;

        val = 0;

        cout << "Enter float: ";

        do {
            c = getchar();

            if (!errorFlag) {
                if ((c >= '0' && c <= '9') ||
                    c == 'e' || c == 'E' ||
                    c == '+' || c == '-' || c == '.') {

                    if (c == '+' || c == '-') {
                        if (expAppearanceFlag)
                            sign = c;
                        else
                            errorFlag = true;
                    }

                    if (expAppearanceFlag)
                        expAppearanceFlag = false;

                    if (c == '.') {
                        if (!dotFlag)
                            dotFlag = true;
                        else
                            errorFlag = true;
                    }

                    if (c == 'e' || c == 'E') {
                        if (!expFlag) {
                            expFlag = true;
                            expAppearanceFlag = true;
                        }
                        else
                            errorFlag = true;
                    }

                    if (c >= '0' && c <= '9') {
                        if (expFlag) {
                            if (exp[0] != '0' || expSize != 2 || c != '0') {
                                exp[expSize++] = c;
                                if (atoi(exp) + sizeBeforeDot > 39 || expSize > 2)
                                    errorFlag = true;
                            }
                        }
                        else if (dotFlag) {
                            if (sizeAfterDot <= 7) {
                                val += (degreeBeforeDot[sizeAfterDot] * (float)(c - '0'));
                                ++sizeAfterDot;
                            }
                        }
                        else if (!dotFlag) {
                            ++sizeBeforeDot;
                            if (sizeBeforeDot <= 39)
                                val = val * 10.f + (float)(c - '0');
                            else
                                errorFlag = true;
                        }
                    }

                    lineFlag = true;

                }
                else if (c != '\n' || !lineFlag)
                    errorFlag = true;
            }

        } while (c != '\n');
        
        if (!errorFlag) {
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
        }
        val = val;
        if (errorFlag)
            cout << "That input is invalid. Please try again." << endl;

    } while (errorFlag);

    return val;
}*/

/*float getFloatValue() {
    float val;
    while (true) {
        cout << "Enter a  value: ";
        cin >> val;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n'); // удаляем лишние значения

            return a;
        }
    }
}*/

float getFloatValue() {
    char str[51];
    bool flag;
    float val = 0;
    int len = 0;
    do {
        val = 0;
        len = 0;
        flag = false;
        fgets(str, 51, stdin);
        fflush(stdin);
        for (int i = 0; str[i] != '\n'; ++i, ++len);
        str[len] = 0;
        fflush(stdin);
        if (len == 0) {
            cout << "You entered an empty string! Try again...";
            ClearStr();
        }
        else if (len > 50) {
            cout << "Entered string longer then need! Try again...";
            ClearStr();
        }
        else if (str[0] == '0' && (str[1] != '\n' && str[1] != '.')) {
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
                        cout << "That input is invalid. Try again...";
                        ClearStr();
                    }
                }
                if (!flag) {
                    val = (float)atof(str);
                    if (val == 0 || isinf(val)) {
                        cout << "MIN value is 1.175494351e-38, MAX value is 3.402823466e+38";
                        ClearStr();
                        flag = true;
                    }
                }
            }
        }
    } while (flag);

    return val;
}

int main() {
    unsigned char valUChar;
    special_float valFloat;
    special_float val;
    bool state;
    cout << "What type of value do you need?" << endl;
    cout << "Enter 0, if unsigned char, or 1, if float: ";
    cin >> state;
    if (state) {
        cin >> val.actual;
        cout << val.actual << endl;
        val.actual = val.actual;
        while (getchar() != '\n');
        valFloat.actual = getFloatValue();
        valFloat.actual = valFloat.actual;
        Print(state, val.auxiliary);
        Print(state, valFloat.auxiliary);
        ClearStr();
        ChangeBit(state, valFloat.auxiliary);
    }
    else {
        valUChar = UnsCharCheck();
        Print(state, 0, valUChar);
        ClearStr();
        ChangeBit(state, 0, valUChar);
    }

    return 0;
}
