#include <cstdio>
#include <algorithm>
#define ub(t) t&(-t)
#define Inf 10000000
#define nmax 100005
using namespace std;
FILE *f=fopen("cerc5.in","r");
FILE *g=fopen("cerc5.out","w");

int n,k,v[110000],pr[110000],aib[110000],maxim[110000],ma;
int8_t viz[1100000];


void update(int x,int val)
{int i;
for (i=x;i<nmax;i+=ub(i)) if (val>aib[i])
            aib[i]=val;


}
int maxulet(int x)
{int m=1,i;
for (i=x;i>=1;i-=ub(i)) if (aib[i]+1>m)
                     {m=aib[i]+1;}
return m;}

void Solve1()
{int i;
fscanf(f,"%d%d",&n,&k);
for (i=1;i<=n;i++) fscanf(f,"%d",&v[i]);
for (i=1;i<=n;i++)
        {maxim[i]=maxulet(v[i]);
         update(v[i]+1,maxim[i]);}
for (i=1;i<=n;i++) if (maxim[i]>ma) ma=maxim[i];
fprintf(g,"%d\n",ma);
}

void Generate(int x)
{int i,j;

for(i=3;i*i<=1000000;i+=2 )
        if(!viz[i])
            for(j=i*i;j<=1000000;j+=2*i)
                viz[j]=1;
pr[1]=2;
int it=1;
for(i=3;i<=1000000&&it<=x;i+=2)
        if(!viz[i])
            pr[++it] = i;
}


void Solve2()
{int i,pos,pos1,pos2,nr,r,c,aux1,aux2;;
fscanf(f,"%d%d",&n,&k);
for(i=1;i<=n;++i)
        fscanf(f,"%d",&v[i]);
Generate(k + 1);
pos=1;
for(i=1;i<=k;++i )
    {nr=pr[i];
     if(pos==1)
        {pos+=nr;
         pos%=n;
            if(pos==0)
                pos=n;
         }
        else
        {r=nr%(n - 1);
         c=nr/(n - 1);
         if(pos-1<=r) --pos;
         pos-=c;
         while(pos < 1 ) pos += n;
        }
     pos %= n;
     if(pos==0)
     pos=n;
    }
pos1=pos+1;
pos2=pos-1;

if(pos1>n) pos1-=n;
if(pos2<1) pos2+=n;

for(i=k;i>0;--i )
    {nr=(pr[i]+1) % n;
     if(nr==0) nr = n;
     if(pos1 == nr )
            {pos1 = 1;
             continue;}
     aux1 = nr;
        r = pr[i]%(n - 1);
        c = pr[i]/(n - 1);
        aux2 = aux1 - r;
        while( aux2 < 1 )
            aux2 += n;

        if( aux2 <= aux1 )
        {
            if( aux2 <= pos1 && pos1 < aux1 )
                ++pos1;
        }

        else
        {
            if( pos1 < aux1 || pos1 >= aux2 )
                ++pos1;
        }

        pos1 += c;

        pos1 %= n;
        if( pos1 == 0 )
            pos1 = n;

        //printf("%d %d %d\n", aux1 , aux2 , pos1);

        //printf("%d %d %d\n", aux1, aux2, pos1);
        //printf("%d ",pos1);
    }

    for(int i = k ; i > 0 ; --i )
    {
        nr = (pr[i] + 1) % n;

        if( nr == 0 )
            nr=n;
        if( pos2 == nr )
        {pos2=1;
         continue;
        }
        aux1 = nr;
        r = pr[i] % (n - 1);
        c = pr[i] / (n - 1);

        aux2 = aux1 - r;
        while( aux2 < 1 )
            aux2 += n;

        if( aux2 <= aux1 )
        {
            if( aux2 <= pos2 && pos2 < aux1 )
                ++pos2;
         }
        else
        {if( pos2 < aux1 || pos2 >= aux2 )
                ++pos2;
        }
        pos2+=c;
        pos2%=n;
        if(pos2==0)
            pos2=n;
    }

    pos1%=n;
    pos2%=n;

    if(pos1==0) pos1=n;

    if(pos2==0) pos2=n;

    fprintf(g,"%d %d",v[pos1], v[pos2]);
}

int main()
{
    int p;
    fscanf(f,"%d", &p);
    if( p == 1 )
        Solve1();

    else
        Solve2();

    return 0;
}
