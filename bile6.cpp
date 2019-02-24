#include <fstream>
using namespace std;
ifstream in("bile6.in");
ofstream out("bile6.out");
int m,n,p,lin[10000],col[10000],b[2001],aux,i;
void pozitie(int q,int u,int &k)
{
    int i,j,di,dj,aux;
    i=q;
    j=u;di=0;dj=-1;
    while(i<j)
    {
        if(lin[i]>lin[j])
        {
            aux=lin[i];
            lin[i]=lin[j];
            lin[j]=aux;
            aux=col[i];
            col[i]=col[j];
            col[j]=aux;
            aux=di;
            di=-dj;
            dj=-aux;
        }
    i=i+di;
    j=j+dj;
    }
    k=i;
}
void quick(int q,int u)
{
    int k;
    if(q<u)
    {
        pozitie(q,u,k);
        quick(q,k-1);
        quick(k+1,u);
    }
}
int main()
{
    short ok;
    in>>m>>n>>p;
    for(i=1;i<=p;i++)
        in>>lin[i]>>col[i];
    for(i=1;i<=n;i++)
        in>>b[i];
    quick(1,p);
    for(i=1;i<=p;i++)
    {
       // out<<col[i]<<" ";
        b[col[i]-1]+=(b[col[i]]+1)/2;
        b[col[i]+1]+=b[col[i]]/2;
        b[col[i]]=0;
       // out<<b[col[i]-1]<<" "<<b[col[i]]<<" "<<b[col[i]+1]<<endl;
    }
    for(i=1;i<=n;i++)
        out<<b[i]<<'\n';
    return 0;
}
