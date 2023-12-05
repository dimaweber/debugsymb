#include <format>
#include <iostream>

#include "class.h"
#include "global.h"

A::A( )
{
    using namespace std;
    cout << "object created\n";
}

A::~A( )
{
    using namespace std;
    cout << "object destroyed\n";
}

void A::run( )
{
    using namespace std;
    cout << "run execution\n";
    while ( true ) {
        step( );
    }
    cout << "run execution done\n";
}

void A::step( )
{
    using namespace std;
    stepsCount++;
    cout << format("executing step {}\n", stepsCount);
    globalFunc(stepsCount);
}
