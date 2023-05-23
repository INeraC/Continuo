#include <iostream>
#include <SFML/Graphics.hpp>
#include "plocica.h"
#include <vector>

#define CRVENA 1
#define PLAVA 2
#define ZUTA 3
#define ZELENA 4

using namespace std;

plocica::plocica(int lijevi_kut, int lijevi_segment, int desni_kut, int desni_segment)
{
    int i, j;
    // lijevi_kut
    polje[0][0] = polje[3][3] = lijevi_kut;

    // desni_kut
    polje[0][3] = polje[3][0] = desni_kut;

    // lijevi_segment
    polje[0][1] = polje[1][0] = polje[1][1] = polje[2][2] = polje[2][3] = polje[3][2] = lijevi_segment;

    // desni_segment
    polje[1][2] = polje[2][1] = polje[0][2] = polje[2][0] = polje[1][3] = polje[3][1] = desni_segment;
}

void plocica::rotiraj()
{
    int i, j, temp;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            temp = polje[i][j];
            polje[i][j] = polje[i][3 - j];
            polje[i][3 - j] = temp;
        }
    }
}

void plocica::ispisi()
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            cout << polje[i][j] << " ";
        }
        cout << endl;
    }
}

bool plocica::iste(plocica p){
    int i,j;
    bool iste = true;
    bool rotirane = true;

    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            if (polje[i][j] != p.polje[i][j])
                iste = false;
        }
    }
    p.rotiraj();
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            if (polje[i][j] != p.polje[i][j])
                rotirane = false;
        }
    }

    if (rotirane || iste)
        return true;
    
    return false;

}

vector<plocica> generiraj()
{
    vector<plocica> ret;
    int i, j, k;

    //generiranje plocica s dvije boje

    for (i=1; i<5; i++ ){
        for (j=1; j<5; j++){
            if (i>=j)
                continue;
            
            ret.push_back(plocica(i,j,j,i));
            
        }
    }

    for (i=1; i<5; i++ ){
        for (j=1; j<5; j++){

            //slucaj kada su sva cetiri vrha obojana istom bojom
            for (k=1; k<5; k++){
                if (j>=k || j==i || k==i)
                    continue;
                plocica p (i,j,i,k);
                ret.push_back(p);
            }

            //slucaj kada su vrhovi obojani razlicitim bojama
            for (k=1; k<5; k++){
                if (i==j || i==k || j==k)
                    continue;
                
                ret.push_back(plocica(i,k,j,i));
            }
        }
    }

    for(i = 0; i < ret.size();i++){
        for( j = 0; j < ret.size(); j++){
            if( i== j)
                continue;

            if(ret[i].iste(ret[j])){
                cout<<"Error"<<endl;
            }
        }
    }
    return ret;

}


// int main(){
//     vector<plocica> pl;
//     pl = generiraj();
//     return 0;
// }