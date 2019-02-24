#include <fstream>
using namespace std;
ifstream in("carte.in");
ofstream out("carte.out");
int n,k,f,x,v[1000],r=0,nrp=1,y;
int main()  // Problema foloseste metoda Greedy, in sensul ca se hotaraste pt fiecare linie daca incape pe pagina curenta sau nu.
{
    int i;
    in>>n>>k>>f;
    for(i=1;i<=n;i++)
        v[i]=1;
    for(i=1;i<=f;i++)
    {
        in>>x>>y;
        v[x]+=y;
    }
    for(i=1;i<=n;i++)
    {
        if(r+v[i]<=k)
            r+=v[i];
        else
        {
            ++nrp;
            r=v[i];
        }
    }
    out<<nrp;
    return 0;
}
