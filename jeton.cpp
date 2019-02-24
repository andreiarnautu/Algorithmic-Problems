#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("jeton.in");
ofstream out("jeton.out");

int v1[28000],v2[28000];

void citire(int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
        in>>v1[i];
    for(j=0;j<n;j++)
        in>>v2[j];
}
void maxsimin(int &minim,int &maxim,int m, int n,int &i1,int &i2,int &j1, int &j2)
{
    int i,j,ok=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(v2[j]>v1[i])
                break;
            if(v1[i]==v2[j])
            {
                minim=v1[i];
                ok=1;
                i1=i;
                j1=j;
                break;
            }
        }
        if(ok==1)
            break;
    }
    ok=0;
    for(i=m-1;i>=0;i--)
    {
        for(j=n-1;j>=0;j--)
        {
            if(v2[j]<v1[i])
                break;
            if(v1[i]==v2[j])
            {
                maxim=v1[i];
                ok=1;
                i2=i;
                j2=j;
                break;
            }
        }
        if(ok==1)
            break;
    }
}
int main()
{
    int m,n,minim=50001,maxim=-1,i1,i2,j1,j2;
    in>>m>>n;
    citire(m,n);
    sort(v1,v1+m);
    sort(v2,v2+n);
    maxsimin(minim,maxim,m,n,i1,i2,j1,j2);
    out<<minim<<" "<<maxim<<" ";
    if(m-i2+i1-1==n-j2+j1-1)
        out<<"0";
    else if(m-i2+i1-1>n-j2+j1-1)
        out<<"1";
    else if(m-i2+i1-1<n-j2+j1-1)
        out<<"2";
    return 0;
}
