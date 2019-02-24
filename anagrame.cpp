#include <cstring>
#include <fstream>
using namespace std;
ifstream in("anagrame.in");
ofstream out("anagrame.out");
int f[30],nr,k,v[500],x,m[500],p=1;
char s[1001];
void prim()
{
    int i,j,ok=1;
    for(i=2;i<=strlen(s);i++)
    {
        for(j=2;j*j<=i;j++)
            if(i%j==0)
            {
                ok=0;
                break;
            }
        if(ok)
        {
            v[k]=i;
            ++k;
        }
    }
}
int main()
{
    int i,j;
    in.get(s,sizeof(s));
    for(i=0;i<strlen(s);i++)
    {
        ++f[s[i]-97];
        if(f[s[i]-97]==1)
            ++nr;
    }
    prim();
    for(i=2;i<=strlen(s);i++)
    {
        p=1;
        x=i;
        out<<"*"<<endl;
        while(x)
        {
            while(x%v[p]==0 && x>0)
            {
                ++m[p];
                x/=v[p];
            }
            ++p;
        }
    }
    for(i=1;i<30;i++)
    {
        for(j=2;j<=f[i];j++)
        {
            x=j;
            p=1;
            while(x)
            {
                while(x%v[p]==0)
                {
                    --m[p];
                    x/=v[p];
                }
                ++p;
            }
        }
    }
    out<<k;
    for(i=1;i<k;i++)
        if(m[i]>0)
            out<<v[i]<<" "<<m[i]<<'\n';
    return 0;
}
