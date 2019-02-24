#include <fstream>
#include <cstring>
using namespace std;
ifstream in("circular.in");
ofstream out("circular.out");

char s1[20000],s2[20000];

int main()
{
    int n,i,j,ok;
    in>>n;
    in.get();
    in.get(s1,sizeof(s1));
    in.get();
    in.get(s2,sizeof(s2));
    for(i=0;i<n;i++)
    {
        ok=0;
        for(j=0;j<n;j++)
            if(s1[(j+i)%n]!=s2[j]) //aici tu verificai daca sirul 1 e o permutare a sirului 2 (in enunt se cere invers) //si implicit nu mai gasesti 'p min'
            {
                ok=1;
                break;
            }
        if(ok==0)
            break;
    }
    if(ok==0)
        out<<i; //aici afisezi i nu (n-i)%n
    else
        out<<"-1";
    return 0;
}
