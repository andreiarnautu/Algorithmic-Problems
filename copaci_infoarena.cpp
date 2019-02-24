#include <cstdio>
#include <cstdlib>
using namespace std;
FILE *fin=freopen("copaci.in","r",stdin);
FILE *fout=freopen("copaci.out","w",stdout);
struct punct
{
    long long x, y;
};
punct v[100001];

long long n,i,a,b;

long long cmmdc( long long a, long long b )
{
	long long r;
	while( b )
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}


int main()
{

    scanf("%lld",&n);
    for(i=1;i<=n;i++)
        scanf("%lld%lld",&v[i].x,&v[i].y);
    v[n+1].x=v[1].x;
    v[n+1].y=v[1].y;
 //   b=cmmdc(llabs(v[n].x-v[1].x),llabs(v[n].y-v[1].y));
    for(i=1;i<=n;i++)
        b+=cmmdc(llabs(v[i].x-v[i+1].x),llabs(v[i].y-v[i+1].y));

     long long x1,x2,y1,y2;
    x1=v[n].x;
    y1=v[n].y;
    x2=v[1].x;
    y2=v[1].y;
   // a=x1*y2-x2*y1;
    for(i=1;i<=n;i++)
    {
        x1=v[i].x;
        y1=v[i].y;
        x2=v[i+1].x;
        y2=v[i+1].y;
        a+=x1*y2-x2*y1;
    }
    //if(a%2==1)
      //  ++a;
    a=llabs(a*0.5);

    long long p=a-(b/2)+1;
    printf("%lld",p);
    return 0;
}
