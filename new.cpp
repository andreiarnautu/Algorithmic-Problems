# include<cstdio>
using namespace std;
FILE *f=freopen("livada1.in","r",stdin);
FILE *g=freopen("livada1.out","w",stdout);
int v[700000];
int main()
{
    int n,m,p,numar=0,i,j,q,r=0,pr,ct,maxim=0,k,l;
    scanf("%d%d%d",&n,&m,&p);
    for( i = 1; i <= n; i++)
       {
           numar=0;
           scanf("%d",&pr);
           v[1] = pr; ct = 1;q = 1;k = 2;l = 1;
           for( j = 2; j <= m; j++)
            {
                scanf("%d",&v[j]);
                if(ct == 0)
                {
                    pr = v[j];
                    ct = 1;
                }
                if(v[j] == pr) ct++;
                if(v[j] != pr) ct--;
                if(v[q] != v[k])
                {
                    if(l > maxim) maxim = l;
                    l = 1;
                    q = k;k++;
                }
                if(v[q] == v[k]) {k++;l++;}
            }
          if( ct != 0) {
            for(j = 1; j <= m; j++)
            {
                if(pr == v[j]) numar++;
            }
       if(numar >= (n / 2) + 1) r++;
                     }
        }
       printf("%d\n%d",r,maxim);
        return 0;
}
