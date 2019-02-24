#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("patru.in");
ofstream out("patru.out");
long long p[32550],n,k,x,v[20001],nr,P[10];
void numere()
{
    long long i,j,a,b;
    for(i=1;i<=178;i++)
        for(j=i;j<=178;j++)
        {
            a=i*i*i*i;
            b=j*j*j*j;
            p[x]=a+b;
            ++x;
        }
}
int main()
{
    long long i,j,s;
    int u;
    for (i=0;i<=9;i++)
		P[i] = i*i*i*i%10;
    in>>n>>k;
    numere();
    sort(p,p+x);
    for(i=1;i<=n;i++)
    {
        in>>v[i];
        if(std::binary_search(p,p+x,v[i]))
            ++nr;
    }
    out<<nr<<'\n';
    s=0;
    nr=0;
	for (i=1;i<=k;i++)
    {
		s += P[v[i]%10];
	}
	nr = s%10 == 4;

	for (i=2;i+k-1 <= n;i++)
    {
		s-=P[v[i-1]%10];
		s+=P[v[i+k-1]%10];
		nr += (s%10 == 4);
	}
    out<<nr;
    return 0;
}
