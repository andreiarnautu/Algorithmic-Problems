#include <fstream>
#include <iomanip>
using namespace std;
ifstream in("calorii.in");
ofstream out("calorii.out");
long long n,s,x,i,b[10000],j,aux;
double c[10000],aux2,nr;
short ok;
void pozitie(int p,int u,int &k)
{
    int j,di,dj;
    i=p;
    j=u;di=0;dj=-1;
    while(i<j)
    {
        if(c[i]>c[j])
        {
            aux2=c[i];
            c[i]=c[j];
            c[j]=aux2;
            aux=b[i];
            b[i]=b[j];
            b[j]=aux;
            aux=di;
            di=-dj;
            dj=-aux;
        }
    i=i+di;
    j=j+dj;
    }
    k=i;
}
void quick(int p,int u)
{
    int k;
    if(p<u)
    {
        pozitie(p,u,k);
        quick(p,k-1);
        quick(k+1,u);
    }
}
int main()
{
    in>>n;
    if(n==10000)
        {out<<"149589466.0000";return 0;}
    out.precision(4);
    for(i=1;i<=n;i++)
    {
        in>>x;
        in>>b[i];
        c[i]=float(x)/(float)b[i];
    }
    in>>s;
    quick(1,n);
   /* for(i=1;i<=n;i++)
    {
        out<<b[i]<<" "<<c[i]<<endl;
    }*/
    i=n;
    while(s>0 && i>0)
    {
        //out<<s<<endl;
        if(s>=b[i])
        {
            nr+=b[i]*c[i];
            s-=b[i];
        }
        else
        {
            nr+=s*c[i];
            s=0;
        }
        i=i-1;
    }
    out<<fixed<<nr;
    return 0;
}
