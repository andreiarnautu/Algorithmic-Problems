#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("cod1.in","r",stdin);
FILE *fout=freopen("cod1.out","w",stdout);
int n,f[30],k,h;
char s[252];
long long nr1=1,nr2=1;
int main()
{
    int i;
    scanf("%d",&n);
    getchar();
    gets(s);
    for(i=0;i<strlen(s);i++)
        ++f[s[i]-97];
    for(i=0;i<27;i++)
    {
        if(f[i]==1)
            ++k;
        else if(f[i]>1)
            ++h;
    }
    for(i=k+h-n+1;i<=k+h;i++)
    nr1=(nr1*i)%9901;
   // printf("%d ",nr1);
    nr2=h*n*(n-1)/2;
    for(i=k+h-n+2;i<=k+h-1;i++)
        nr2=(nr2*i)%9901;
  //  printf("%d ",nr2);
    nr1=(nr1+nr2)%9901;
    printf("%d",nr1);
    return 0;
}
