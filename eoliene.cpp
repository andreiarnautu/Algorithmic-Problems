#include <fstream>
using namespace std;
ifstream in("eoliene.in");
ofstream out("eoliene.out");
long aux,j,i,n,d[1000],l[1000],v1[1000],v2[1000],nr,x;
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
        in>>d[i];
    for(i=1;i<=n;i++)
    {
        in>>l[i];
        v1[i]=d[i]-l[i];
        v2[i]=d[i]+l[i];
    }
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            if(v2[i]>v2[j])
            {
                aux=v2[i];
                v2[i]=v2[j];
                v2[j]=aux;
                aux=v1[i];
                v1[i]=v1[j];
                v1[j]=aux;
            }
    x=v2[1];
    nr=0;
    for(i=2;i<=n;i++)
    {
        if(v1[i]<=x)
            ++nr;
        else
            x=v2[i];
    }
    out<<nr;
    return 0;
}
