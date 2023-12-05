#include <format>
#include <iostream>

#include "global.h"

int* globalFunc (int v)
{
    using namespace std;
    int* p {nullptr};
    *p = v;
    cout << std::format("allocated new value {}\n", *p);
    return p;
}
