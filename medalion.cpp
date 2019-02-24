#include <fstream>
using namespace std;
ifstream fin("medalion.in");
ofstream fout("medalion.out");
int a[321][321];
long long n,m,p,k;

void calcul()
{ long long s,max=0;
   for(int i=1;i<=n;i++)
	{ s=0;
        for(int j=1;j<=n;j++)
            s+=a[i][j];
        if (s>max) max=s;
	}
    fout<<max<<endl;
 }

int main()
{
	long long val,linie,spira,j;
	fin>>k>>n>>p;
	fin.close();
	m=n/2+n%2;a[m][m]=1;linie=m;
	val=2;spira=1;
	while(linie>=1)
	{
		for(j=1;j<=2*spira-1;j++)//dreapta
			{a[linie][linie+j]=val;val=1+val%k;}
		for(j=1;j<=2*spira-1;j++)//jos
			{a[linie+j][m+spira]=val;val=1+val%k;}
		for(j=m+spira-1;j>=m-spira;j--)//stanga
			{a[m+spira][j]=val;val=1+val%k;}
		for(j=m+spira-1;j>=m-spira;j--)//sus
			{a[j][m-spira]=val;val=1+val%k;}
		spira++;
		linie--;
    }
	calcul();
//cerinta b
	val=(1+4*p*p+3*p)%k;
	if (val==0) fout<<k<<endl;
		else fout<<val<<endl;
	fout.close();
	return 0;
}
