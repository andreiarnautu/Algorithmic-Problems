#include <fstream>
using namespace std;
ifstream in("canguri.in");
ofstream out("canguri.out");
int i,n,x,y,maxim;
long long nr=1,aux1,aux2,aux3,p;
int main()
{
    in>>n;
    for(i=0;i<n;i++)
    {
        in>>x;
        if(x>maxim)
            maxim=x;
        aux1=x;
        aux2=nr;
        p=nr*x;
        aux3=aux1%aux2;
        while(aux3!=0)
        {
            aux1=aux2;
            aux2=aux3;
            aux3=aux1%aux2;
        }
        nr=p/aux2;
    }
    if(maxim*3>nr)
    {
        if(nr*2>=maxim*3)
            nr*=2;
        else
            nr*=3;
    }
    out<<nr;
    return 0;
}
