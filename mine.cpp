#include <fstream>
#include <cstring>
using namespace std;
ifstream in("mine.in");
ofstream out("mine.out");
short t;
int n;
int mat[1001][1001],lin[1000001],col[1000001],maxim=0;
short m[1001][1001];
void procedura()
{
    char s[1002];
    long long i,p,u,j;
    in>>n;
    in.get();
    for(i=0;i<n;i++)
    {
        in.get(s,sizeof(s));
        in.get();
        for(j=0;j<strlen(s);j++)
        {
            if(s[j]=='G')
            {
                lin[1]=i+1;
                col[1]=j+1;
                m[i+1][j+1]=0;
            }
            else if(s[j]=='.')
                m[i+1][j+1]=0;
            else
                m[i+1][j+1]=1;
        }
    }
    p=1;u=1;
    while(p<=u)
    {
        i=lin[p];
        j=col[p];
        if(i>2 && j<n)
        {
            if(m[i][j]+m[i-2][j+1]>mat[i-2][j+1])
            {
                mat[i-2][j+1]=m[i][j]+m[i-2][j+1];
                if(mat[i-2][j+1]>maxim)
                    maxim=mat[i-2][j+1];
            }
            ++u;
            lin[u]=i-2;
            col[u]=j+1;
        }
        if(i>1 && j<n-1)
        {
            if(m[i][j]+m[i-1][j+2]>mat[i-1][j+2])
            {
                mat[i-1][j+2]=m[i][j]+m[i-1][j+2];
                if(mat[i-1][j+2]>maxim)
                    maxim=mat[i-1][j+2];
            }
            ++u;
            lin[u]=i-1;
            col[u]=j+2;
        }
        if(i<n && j<n-1)
        {
            if(m[i][j]+m[i+1][j+2]>mat[i+1][j+2])
            {
                mat[i+1][j+2]=m[i][j]+m[i+1][j+2];
                if(mat[i+1][j+2]>maxim)
                    maxim=mat[i+1][j+2];
            }
            ++u;
            lin[u]=i+1;
            col[u]=j+2;
        }
        if(i>2 && j<n)
        {
            if(m[i][j]+m[i-2][j+1]>mat[i-2][j+1])
            {
                mat[i-2][j+1]=m[i][j]+m[i-2][j+1];
                if(mat[i-2][j+1]>maxim)
                    maxim=mat[i-2][j+1];
            }
            ++u;
            lin[u]=i-2;
            col[u]=j+1;
        }
        if(i<n-1 && j<n)
        {
            if(m[i][j]+m[i+2][j+1]>mat[i+2][j+1])
            {
                mat[i+2][j+1]=m[i][j]+m[i+2][j+1];
                if(mat[i+2][j+1]>maxim)
                    maxim=mat[i+2][j+1];
            }
            ++u;
            lin[u]=i+2;
            col[u]=j+1;
        }
        ++p;
    }
  /*  for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            out<<mat[i][j]<<" ";
        out<<endl;
    }*/
    out<<maxim<<'\n';
}
int main()
{
    short l;
    in>>t;
    for(l=0;l<t;l++)
        procedura();
    return 0;
}
