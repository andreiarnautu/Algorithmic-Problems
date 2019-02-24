#include <fstream>
using namespace std;
ifstream in("numere6.in");
ofstream out("numere6.out");
int v1[100],v2[100];

void baza2(int &m,int &n)
{
    int k1=0,k2=0,i=0,j,p=1,nr1=0,nr2=0,l;
    while(m)
    {
        v1[k1]=m%2;
        m=m/2;
        ++k1;
    }
    while(n)
    {
        v2[k2]=n%2;
        n=n/2;
        ++k2;
    }
    m=k1;
    n=k2;
    j=k1-1;
    while(m && n && v1[j]==v2[i])
    {
        v1[j]=2;
        v2[i]=2;
        --j;
        ++i;
        --m;
        --n;
    }
    for(l=0;l<k1;l++)
    {
        if(v1[l]==1 || v1[l]==0)
            p*=2;
        if(v1[l]==1)
            nr1+=p/2;
    }
    p=1;
    for(l=0;l<k2;l++)
    {
        if(v2[l]==0 || v2[l]==1)
            p*=2;
        if(v2[l]==1)
            nr2+=p/2;
    }
    out<<nr1+nr2;
}


int main()
{
    int m,n;
    in>>m>>n;
    baza2(m,n);
    return 0;
}
