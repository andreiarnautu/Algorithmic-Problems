#include <fstream>
using namespace std;
ifstream in("degrade.in");
ofstream out("degrade.out");

char s1[11],s2[100001];

void citire(int &k) // Citesc cele 2 siruri de caractere, in primul ordinea gradelor si apoi sirul propriu zis. Stiu ca se putea citi si cu in.get nu stiu de ce nu am facut asa de la inceput.
{
    char p,i;
    k=0;
    for(i=0;i<10;i++)
        {
            in>>s1[i];
        }
    in>>s2[0];
    while(s2[k]!=NULL)
    {
        in>>s2[k+1];
        ++k;
    }
}

int grad(char s) // Aceasta functie returneaza gradul unui anumit caracter.
{
    for(int i=0;i<10;i++)
        if(s==s1[i])
            return i;
}

void afisare(int k) //Ultima functie este cea de finalizare si afisare.
{
    int ok,i=0,nrmax=0,nr=0,nrc=0;
    while(i<=k) // cred ca aici nu acopar cele 2 cazuri, desi am stat vreo jumatate de ora pe ea, nu gasesc unde greseste.
    {
       nrc=1;
       ok=0;
       while(grad(s2[i])<=grad(s2[i+1]) && i<=k-1)
       {
            ++i;
            ++nrc;
            ok=1;
       }
       if(nrc>nrmax)
       {
           nrmax=nrc;
           nr=1;
           out<<i<<" ";
       }
       else if(nrc==nrmax)
            {
                ++nr;
                out<<i<<" ";
            }
        if(ok==0)
            ++i;
    }
    out<<nrmax<<" "<<nr;
}

int main() //in main doar activez functiile void.
{
    int k,i=0;
    citire(k);
    afisare(k);
    return 0;
}
