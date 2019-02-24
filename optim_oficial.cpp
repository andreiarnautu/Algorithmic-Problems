#include<fstream>
using namespace std;
int x[10],y[31],n,k;
long long valmin,valmax,a[31],val;
void comb(int t)
{
	int i;
	long long s,p;
	if(t==k+1)
	{
		for(i=1;i<n;i++)
			y[i]=1;

		for(i=1;i<=k;i++)
			y[x[i]]=2;

		s=0;
		p=1;
		for(i=1;i<n;i++)
			if(y[i]==2)
				p=p*a[i];
			else
			{
				s=s+p;
				p=a[i];
			}
		s=s+p;
		if(s<valmin)
			valmin=s;
		else if(s>valmax)
			valmax=s;
	}
	else
		for(i=x[t-1]+1;i<=n-1;i++)
		{
			x[t]=i;
			comb(t+1);
		}
}


int main()
{
	int i;
	ifstream f("optim.in");
	ofstream g("optim.out");
	f>>n>>k;
	for(i=0;i<n;i++)
		f>>a[i];
	val=a[0];
	for(i=1;i<=k;i++)
		val=val*a[i];
	for(i=k+1;i<n;i++)
		val=val+a[i];
	valmin=valmax=val;
	comb(1);
	g<<valmin<<' '<<valmax<<'\n';
}

