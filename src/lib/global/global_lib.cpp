#include <iostream>

#include "global.h"

int* globalFunc (int v)
{
    using namespace std;
    int* p {nullptr};
    *p = v;
    cout << "allocated new value" << *p << "\n";
    return p;
}
