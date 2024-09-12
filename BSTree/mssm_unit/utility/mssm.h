#ifndef MSSM_H
#define MSSM_H

#include <iostream>

#include "array.h"
#include "rand.h"
#include "format_helper.h"

using namespace std;
using namespace fmt;
// using fmt::print;
// using fmt::println;

template <typename T>
void print(T value)
{
    print("{}", value);
}

template <typename T>
void println(T value)
{
    println("{}", value);
}

inline void println() { println(""); }

char readChar();
int readInt();
double readDouble();
string readLine();
string readWord();

bool tryReadChar(char &value);
bool tryReadInt(int &value);
bool tryReadDouble(double &value);

void delay(int milliseconds);

#define main safemain

#endif // MSSM_H
