#include<fstream>
using namespace std;
int n,nd,dmax,nmax,nr,dist,h,p;
ifstream f("domino1.in");
ofstream g("domino1.out");
int main()
{ int i;
f>>n;
dist=0;
nd=0;
for(i=1;i<=n;i++)
{f>>p>>h;
if(p>dist)
{nd++;
if(nr>nmax) nmax=nr;
dist=p+h;
nr=1;
}
else{nr++;
if(dist< p+h )
dist=p+h;
}
}
if(nr>nmax) nmax=nr;
g<<nd<<" "<<nmax <<'\n';
g.close();
return 0;
}
