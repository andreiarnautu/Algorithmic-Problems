#include <fstream>
using namespace std;
ifstream in("cartonas.in");
ofstream out("cartonas.out");
int n;
long long x,v1[100],v2[100],v3[100],c1,c2,c3[100],suma[100];
int unu(int s)
{
    int k=0;
    while(s)
    {
        if(s%2==1)
            ++k;
        s=s/2;
    }
    return k;
}
void sursa()
{
    int i,s=0,j,p=2,ok=0,aux,maxim,nn;
    nn=n;
    for(i=1;i<=n;i++)
        s+=v1[i];
    suma[1]=unu(s);
    for(i=1;i<=n;i++)
        if(x==v1[i])
        {
            c2=1;
            ok=1;
            break;
        }
    s=0;
    for(i=n-1;i>=1;i--)
    {
        for(j=1;j<=i;j++)
            v1[j]+=v1[j+1];
        for(j=1;j<=i;j++)
            s+=v1[j];
        suma[p]=unu(s);
        for(j=1;j<=i;j++)
            if(v1[j]==x && ok==0)
            {
                c2=p;
                ok=1;
                break;
            }
        ++p;
        s=0;
    }
    out<<v1[1]<<endl<<c2<<endl;
    maxim=0;
    while(nn)
    {
        maxim=-1;
        for(i=1;i<=n;i++)
            if(suma[i]>maxim)
                maxim=suma[i];
        for(i=1;i<=n;i++)
            if(suma[i]==maxim)
            {
                out<<i<<" ";
                suma[i]=-1;
                break;
            }
        --nn;
    }
}
int main()
{
    int i;
    in>>n>>x;
    for(i=1;i<=n;i++)
        in>>v1[i];
    sursa();
    return 0;
}
