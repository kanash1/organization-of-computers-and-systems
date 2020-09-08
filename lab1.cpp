//g++ new_work.cpp -std=c++17 -o lab1

#include <iostream>
#include <cstdarg>

using namespace std;

typedef union {
    float val;
    int aux;
} binFloat;


void Print(bool state, ...) {

    int numInt;
    unsigned char numUC;
    va_list val;
    va_start(val, state);

    if (state) {
        numInt = va_arg(val, int);
        for (int i = 31; i >= 0; --i)
            cout << ((numInt >> i) & 1);
    }
    else {
        numUC = va_arg(val, unsigned char);
        for (int i = 7; i >= 0; --i)
            cout << ((numUC >> i) & 1);
    }

    va_end(val);
    cout << endl;
}


void ChangeBit(bool state, ...) {

    int HighBit, NumberBit, numInt;
    char SignBit[80];
    unsigned char numUC;
    va_list val;
    va_start(val, state);

    cin >> NumberBit >> HighBit >> SignBit;

    if (state) {
        numInt = va_arg(val, int);
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                numInt |= (1 << (HighBit - i));
            else
                numInt &= ~(1 << (HighBit - i));
        }
        Print(state, numInt);
    }
    else {
        numUC = va_arg(val, unsigned char);
        for (int i = 0; i < NumberBit; ++i) {
            if (SignBit[i] == '1')
                numUC |= (1 << (HighBit - i));
            else
                numUC &= ~(1 << (HighBit - i));
        }
        Print(state, numUC);
    }
    va_end(val);
}


int main() {
    unsigned char numUC;
    binFloat numF;

    cout << "Enter float: ";
    cin >> numF.val;
    Print(1, numF.aux);
    ChangeBit(1, numF.aux);
    cout << "Enter unsigned char: ";
    cin >> numUC;
    Print(0, numUC);
    ChangeBit(0, numUC);


    return 0;
}