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
    for ( int i = 0; i < 10; i++ ) {
        step( );
    }
    cout << "run execution done\n";
}

void A::step( )
{
    using namespace std;
    stepsCount++;
    cout << "executing step " << stepsCount << "\n";
    globalFunc(stepsCount);
}
