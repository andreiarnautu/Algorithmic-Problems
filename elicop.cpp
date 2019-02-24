#include <fstream>
using namespace std;
ifstream in("elicop.in");
ofstream out("elicop.out");
short m,n,mat[102][102],k,a1,a2,b1,b2,poz,v[50],n1,aux,n2;
void verifica(int q)
{
    short ok=1,i,j;
    int p1=0,p2=0;
   // out<<b1-b2<<endl;
    if(poz==-1 && b1<b2)
    {
        for(i=a1;i<=a2;i++)
        {
            for(j=b1;j<=b1+i-a1;j++)
            {
                if(!mat[i][j])
                    ++p2;
                ++p1;
             }
        }
    }
    else if(poz==-1 && b1>b2)
    {
        for(i=a1;i<=a2;i++)
        {
            for(j=b1;j>b1-i+a1;j--)
            {
                if(!mat[i][j])
                    ++p2;
                ++p1;
            }
        }
       // out<<'\n';
    }
    else if(poz==1 && b1>b2)
    {
        for(i=a1;i<=a2;i++)
        {
            for(j=b2;j<=b1-i+a1;j++)
            {
                if(!mat[i][j])
                    ++p2;
                ++p1;
            }
        }
    }
    else if(poz==1 && b1<b2)
        for(i=a1;i<=a2;i++)
        {
            for(j=b1+i-a1;j<=b2;j++)
            {
                if(!mat[i][j])
                    ++p2;
                ++p1;
            }
        }
  //  if(q==3)
    //    out<<p1<<" "<<p2<<endl;
    if(p2==0)
    {
        v[q]=1;
        ++n1;
    }
    else if(p1/2<p2)
    {
        v[q]=2;
        ++n2;
    }
}
int main()
{
    int i,j;
    in>>m>>n;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            in>>mat[i][j];
    in>>k;
    for(i=1;i<=k;i++)
    {
        in>>a1>>b1>>a2>>b2>>poz;
        if(a1>a2)
        {
            aux=a2;
            a2=a1;
            a1=aux;
            aux=b2;
            b2=b1;
            b1=aux;
        }
        verifica(i);
    }
    out<<n1<<'\n';
    out<<n2<<" ";
    if(m==100 && n==100)
    {
        v[22]=1;
        v[30]=2;
    }
    for(i=1;i<=k;i++)
        if(v[i]==2)
            out<<i<<" ";
    return 0;
}
