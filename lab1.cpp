#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <limits>
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
    cout << endl;
    system("cls");
}

void Print(bool state, int valInt = 0, unsigned char valUC = 0) {
    cout << "Internal representation: ";
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
            cout << "You entered an empty string! Try again...\n";
            ClearStr();
            Flag = true;
        }
        else if (len < NumberBit)
        {
            cout << "The sequence of bits shorter then " << NumberBit << "! Try again...\n";
            ClearStr();
            Flag = true;
        }
        else if (len > NumberBit)
        {
            cout << "The sequence of bits longer then " << NumberBit << "! Try again...\n";
            ClearStr();
            Flag = true;
        }
        else
        {
            for (int i = 0; i < NumberBit && !Flag; ++i)
            {
                if (Check[i] != '0' && Check[i] != '1')
                {
                    cout << "The sequence of bits must consist only of 0 and 1! Try again...\n";
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
            cout << "You entered an empty string! Try again...\n";
            ClearStr();
        }
        else if (Check[1] != '\n' && Check[1 + state] != '\n' || atoi(Check) < NumberBit - 1 || atoi(Check) > MaxPos)
        {
            cout << "The highest bit is a number from " << NumberBit - 1 << " to " << MaxPos << "! Try again...\n";
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
            cout << "You entered an empty string! Try again...\n";
            ClearStr();
        }
        else if (Check[1] != '\n' && Check[1 + state] != '\n' || atoi(Check) > MaxBits || atoi(Check) < 1)
        {
            cout << "The number of bits is a number from 1 to " << MaxBits << "! Try again...\n";
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
        if (isnan(tmp.actual))
            cout << "New converted value is not a number (NaN)" << endl;
        else if (isinf(tmp.actual))
            cout << "New converted value is infinity" << endl;
        else
            cout << "New converted value: " << tmp.actual << endl;
        Print(state, valInt);
    }
    else {
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                valUC |= (1 << (HighBit - i));
            else
                valUC &= ~(1 << (HighBit - i));
        }
        cout << "New converted character: " << valUC << endl;
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
        zeroFlag = false,
        clsFlag = false,
        expAppearanceFlag = false;
    int
        sizeBeforeDot = 0,
        sizeAfterDot = 0,
        exp = 0,
        expSize = 0;
    char
        sign = '+',
        expSign = '+',
        last_c = 0,
        c = 0;
    float
        val = 0,
        degreeBeforeDot = 0.1f;
    do {
        errorFlag = false;
        dotFlag = false;
        expFlag = false;
        expAppearanceFlag = false;
        lineFlag = false;
        zeroFlag = false;
        clsFlag = false;
        sizeBeforeDot = 0;
        sizeAfterDot = 0;
        expSize = 0;
        sign = '+';
        expSign = '+';
        c = 0;
        last_c = 0;
        exp = 0;
        val = 0;
        degreeBeforeDot = 0.1f;
        cout << "MAX value is " << numeric_limits<float>::max();
        cout << ", MIN value is " << numeric_limits<float>::lowest() << ".\n";
        cout << "The MIN value modulo nonzero is " << numeric_limits<float>::denorm_min() << ".\n";
        cout << "Enter a float value: ";
        do {
            c = getchar();
            if (!clsFlag) {
                system("cls");
                clsFlag = true;
            }
            if (!errorFlag) {
                if ((c >= '0' && c <= '9') ||
                    c == 'e' || c == 'E' ||
                    c == '+' || c == '-' || c == '.') {
                    if (c == '+' || c == '-') {
                        if (last_c == 'e' || last_c == 'E') {
                            expSign = c;
                        }
                        else if (last_c == 0) {
                            sign = c;
                        }
                        else {
                            cout << "That input is invalid. Try again...\n";
                            errorFlag = true;
                        }
                    }

                    if (c == '.') {
                        if (!dotFlag) {
                            dotFlag = true;
                        }
                        else {
                            errorFlag = true;
                            cout << "That input is invalid. Try again...\n";
                        }
                    }
                    if (c == 'e' || c == 'E') {
                        if (!expFlag && last_c != 0 &&
                            (!dotFlag || sizeAfterDot > 0)) {
                            expFlag = true;
                        }
                        else {
                            errorFlag = true;
                            cout << "That input is invalid. Try again...\n";
                        }
                    }
                    if (c >= '0' && c <= '9') {
                        if (expFlag) {
                            exp = exp * 10 + (c - '0');
                            if (exp + sizeBeforeDot > 39 && expSign == '+') {
                                cout << "MAX value is " << numeric_limits<float>::max();
                                cout << ", MIN value is " << numeric_limits<float>::lowest() << ". Try again...\n";
                                errorFlag = true;
                            }
                            else if (exp - sizeBeforeDot >= 45 && expSign == '-') {
                                cout << "The MIN value modulo nonzero is " << numeric_limits<float>::denorm_min() << ".\n";
                                errorFlag = true;
                            }
                        }
                        else if (dotFlag) {
                            if (sizeAfterDot <= 9) {
                                val += (degreeBeforeDot * (float)(c - '0'));
                                degreeBeforeDot *= 0.1f;
                                ++sizeAfterDot;
                                if (isnan(val) || isinf(val)) {
                                    cout << "MAX value is " << numeric_limits<float>::max();
                                    cout << ". MIN value is " << numeric_limits<float>::lowest() << ". Try again...\n";
                                    errorFlag = true;
                                }
                            }
                        }
                        else if (!dotFlag) {
                            if (c != '0')
                                zeroFlag = true;
                            if (zeroFlag)
                                ++sizeBeforeDot;
                            if (sizeBeforeDot <= 39) {
                                val = val * 10.f + (float)(c - '0');
                                if (isnan(val) || isinf(val)) {
                                    cout << "MAX value is " << numeric_limits<float>::max();
                                    cout << ". MIN value is " << numeric_limits<float>::lowest() << ". Try again...\n";
                                    errorFlag = true;
                                }
                            }
                            else
                                errorFlag = true;
                        }
                    }
                    lineFlag = true;
                    last_c = c;
                }
                else if (c != '\n') {
                    cout << "That input is invalid. Try again...\n";
                    errorFlag = true;
                }
                else if (!lineFlag) {
                    cout << "You input nothing. Try again...\n";
                    errorFlag = true;
                }
            }

        } while (c != '\n');


        if (sign == '-') {
            val = -val;
        }

        if ((last_c == 'e' || last_c == 'E' ||
            last_c == '+' || last_c == '-') && !errorFlag) {
            cout << "That input is invalid. Try again...\n";
            errorFlag = true;
        }

        if (!errorFlag && expFlag) {
            for (int i = 0; i < exp; ++i) {
                (expSign == '+') ? val *= 10.f : val *= 0.1f;
            }
            if (isinf(val)) {
                cout << "MAX value is " << numeric_limits<float>::max();
                cout << ", MIN value is " << numeric_limits<float>::lowest() << ". Try again...\n";
                errorFlag = true;
            }
        }

        if (errorFlag) {
            ClearStr();
        }

    } while (errorFlag);
    return val;
}

bool getChoice(bool state) {

    char choice[3];
    bool flag;
    do {

        flag = false;
        if (state) {
            cout << "What type of value do you need?\n";
            cout << "Enter 0, if you need unsigned char, or 1, if you need float: ";
        }
        else {
            cout << "Do you want repeat?\nEnter 1, if you want it, or 0, if not: ";
        }

        fgets(choice, 3, stdin);
        fflush(stdin);
        system("cls");

        if (choice[0] == '\n') {
            flag = true;
            cout << "You entered an empty string! Try again...\n";
            ClearStr();
        }
        else if (choice[1] != '\n' || (choice[0] != '0' && choice[0] != '1')) {
            flag = true;
            cout << "That input is invalid! Try again...\n";
            ClearStr();
        }

    } while (flag);

    return (bool)(choice[0] - '0');
}

int main() {
    unsigned char valUChar; // unsigned char value
    special_float valFloat; // float and int union value
    float val;
    bool
        choice,
        state;
    do {
        state = getChoice(1);    // user make choice

        if (state) {
            valFloat.actual = getFloatValue();
            cout << "Your value: " << valFloat.actual << endl;
            Print(state, valFloat.auxiliary);
            ChangeBit(state, valFloat.auxiliary);
        }
        else {
            valUChar = UnsCharCheck();
            cout << "Your character: " << valUChar << endl;
            Print(state, 0, valUChar);
            ChangeBit(state, 0, valUChar);
        }

        choice = getChoice(0);

    } while (choice);

    return 0;
}
