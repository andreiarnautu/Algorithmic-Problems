#include <cstdio>
using namespace std;

int v[150],s[150];

int main()
{
    freopen("muguri.in","r",stdin);
    freopen("muguri.out","w",stdout);
    int n,i,nr,j,nrmax=0,x;
    bool ok;
    char c;
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        ok=true;
        scanf("%d ",&nr);
        x=nr/2;
        for (j=1;j<=nr;j++)
        {
            scanf("%c",&c);
            v[j]=c-'0';
            if (j>x)
                if (v[j]!=v[nr+1-j])
                    ok=false;
        }
        if (ok)
        {
            if (nr>nrmax) nrmax=nr;
            for (j=nr;j>=1;j--)
            {
                s[nr+1-j]=s[nr+1-j]+v[j];
                if (s[nr+1-j]>9)
                {
                    s[nr+2-j]=s[nr+2-j]+(s[nr+1-j]/10);
                    s[nr+1-j]=s[nr+1-j]%10;
                    if (s[nr+2-j]>9)
                    {
                        s[nr+3-j]=s[nr+3-j]+(s[nr+2-j]/10);
                        s[nr+2-j]=s[nr+2-j]%10;
                    }
                }
            }
        }
    }
    if (s[nrmax+1]!=0) nrmax++;
    for (i=nrmax;i>=1;i--)
        printf("%d",s[i]);
    return 0;
}
