#include <iostream>
#include "plocica.h"

using namespace std;

int main()
{
    plocica P(1,2,3,1);
    P.ispisi();
    cout<<endl;
    P.rotiraj();
    P.ispisi();
    return 0;
}