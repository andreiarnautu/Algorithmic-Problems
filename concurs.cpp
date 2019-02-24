#include <fstream>
using namespace std;
ifstream in("concurs.in");
ofstream out("concurs.out");
long long n,v1[505],v2[505],j[55],nj;
void schimba(int x, int y)
{
    long long aux;
    aux=v1[x];
    v1[x]=v1[y];
    v1[y]=aux;
    aux=v2[x];
    v2[x]=v2[y];
    v2[y]=aux;
}
void sortare()
{
    long long i;
    short ok;
    do
    {
        ok=0;
        for(i=1;i<n;i++)
            if(v2[i]>v2[i+1])
            {
                schimba(i,i+1);
                ok=1;
            }
    }while(ok);
}
int main()
{
    int i;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>v1[i]>>v2[i];
        ++j[v1[i]];
        if(j[v1[i]]==1)
            ++nj;
    }
    out<<nj<<'\n';
    for(i=1;i<=50;i++)
        if(j[i])
            out<<j[i]<<" ";
    out<<'\n';
    sortare();
    for(i=1;i<=n;i++)
    {
        if(v1[i]==v1[i+1])
        {
            if(i==1)
                schimba(i+1,i+2);
            else
                schimba(i,i-1);
        }
    }
    for(i=1;i<=n;i++)
        out<<v1[i]<<" "<<v2[i]<<'\n';
    return 0;
}
