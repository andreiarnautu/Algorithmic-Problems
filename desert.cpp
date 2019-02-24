#include <cstdio>
using namespace std;
FILE *fin=freopen("desert.in","r",stdin);
FILE *fout=freopen("desert.out","w",stdout);
int n,k,pp;
double p;
double dist(int n)
{
    if(n<3)
        return k*n/p;
    return k/((2*n-3)*p)+dist(n-1);
}
int main()
{
    double d;
    scanf("%d%d%d",&n,&k,&pp);
    p=(double)pp;
//    printf("%d %d %d ",n,k,pp);
    p=p/100;
   // printf("%f",p);
    d=dist(n);
    printf("%.3f",d);
    return 0;
}
