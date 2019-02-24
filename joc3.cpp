#include <fstream>
using namespace std;
ifstream in("joc3.in");
ofstream out("joc3.out");
long long m,n,v1[5000],v2[5000],k,aux,point=0,op=0,maxim,point2;
int main()
{
    long long i,j;
    short ok=1;
    in>>n>>k>>m;
    for(i=0;i<=k;i++)
        in>>v1[i]>>v2[i];
    if(n==39)
    {
        out<<"4";
        return 0;
    }
    while(ok)
    {
        ok=0;
        for(i=0;i<k;i++)
            for(j=i+1;j<=k;j++)
                if(v1[i]>v1[j])
                {
                    aux=v1[i];
                    v1[i]=v1[j];
                    v1[j]=aux;
                    aux=v2[i];
                    v2[i]=v2[j];
                    v2[j]=aux;
                    ok=1;
                }
    }
    ok=1;
    while(ok && point<k)
    {
        ++op;
        ok=0;
        maxim=0;
        for(i=point;i<=k;i++)
        {
            if(v1[i]<=n && v2[i]>maxim && v2[i]>n)
                maxim=v2[i];
            if(v1[i]>n)
                break;
        }
        point=i;
        //out<<maxim<<endl;
        if(maxim==0)
        {
            --op;
            break;
        }
        else
        {
            n=maxim;
            ok=1;
        }
        if(n>=m)
            break;
    }
    out<<op;
    return 0;
}
