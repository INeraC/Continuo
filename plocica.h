#include <iostream>

using namespace std;

class plocica
{
    int polje[4][4];

public:
    plocica(int lijevi_kut, int lijevi_segment, int desni_kut, int desni_segment);
    void rotiraj();
    void ispisi();
};