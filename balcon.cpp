#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("balcon.in");
ofstream out("balcon.out");

int v[2501],m[50][50];
void citire(int n)
{
    int i;
    for(i=0;i<n*n;i++)
        in>>v[i];
    sort(v,v+i);
}
void spirala(int n)
{
    int k=0,ci=0,cf=n-1,li=0,lf=n-1,i;
    while(k<n*n)
    {
        for(i=ci;i<=cf;i++)
        {
            m[li][i]=v[k];
            ++k;
        }
        for(i=li+1;i<=lf;i++)
        {
            m[i][cf]=v[k];
            k++;
        }
        for(i=cf-1;i>=ci;i--)
        {
            m[lf][i]=v[k];
            ++k;
        }
        for(i=lf-1;i>li;i--)
        {
            m[i][ci]=v[k];
            ++k;
        }
        ++li;
        ++ci;
        --lf;
        --cf;
    }
}

void afisare(int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            out<<m[i][j]<<" ";
        out<<endl;
    }
}
int main()
{
    int n;
    in>>n;
    citire(n);
    spirala(n);
    afisare(n);
    return 0;
}
