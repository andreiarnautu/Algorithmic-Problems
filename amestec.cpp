//#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
//FILE *fin=freopen("amestec.in","r",stdin);
//FILE *fout=freopen("amestec.out","w",stdout);
ifstream in("amestec.in");
ofstream out("amestec.out");

int n,k;
bool a[101][101];
char s[15],c;
void nord(int d, int q)
{
    int i,j,u=1001;
    for(j=1;j<=n;j++)
    {
        u=1001;
        for(i=2;i<=n;i++)
        {
            if((a[i][j]==q && a[i-1][j]!=q) && (u!=i-1 && u!=i))
            {
                swap(a[i][j],a[i-1][j]);
                u=i;
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            out<<a[i][j]<<" ";
        out<<'\n';
    }
}
void sud(int d, int q)
{
    int i,j,u=1001;
    for(j=1;j<=n;j++)
    {
        u=1001;
        for(i=n-1;i>0;i--)
            if((a[i][j]==q && a[i+1][j]!=q) && (u!=i && u!=i+1))
            {
                swap(a[i][j],a[i+1][j]);
                u=i;
            }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            out<<a[i][j]<<" ";
        out<<'\n';
    }
}
void est(int d, int q)
{
    int i,j,u,l;
    for(l=1;l<=d;l++)
        for(i=1;i<=n;i++)
        {
            u=1001;
            for(j=n-1;j>0;j--)
            if((a[i][j]==q && a[i][j+1]!=q) && (u!=j && u!=j+1))
            {
                swap(a[i][j],a[i][j+1]);
                u=j;
            }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            out<<a[i][j]<<" ";
        out<<'\n';
    }
}
int main()
{
    int i,j,q,d;
    in>>n>>k;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            {
                in>>c;
                a[i][j]=c-48;
            }
    in.get();
    for(i=1;i<=k;i++)
    {
        in.get(s,sizeof(s));
        in.get();
        d=atoi(s);
        q=s[strlen(s)-1]-48;
        if(s[strlen(s)-2]=='N')
            nord(d,q);
        else if(s[strlen(s)-2]=='S')
            sud(d,q);
        else if(s[strlen(s)-2]=='E')
            est(d,q);
    }
    return 0;
}
