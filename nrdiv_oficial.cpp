#include <fstream>
#include <cmath>
#define NMAX 100
#define VMAX 10000001
#define NRMAXPRIM 10000

using namespace std;
ifstream fin("nrdiv.in");
ofstream fout("nrdiv.out");
int N, nrprim;
long long int v[NMAX], vmax, prim[NRMAXPRIM];
char ciur[VMAX];
int main()
{int i, p;
 long long int nr, d, j;
 fin>>N;
 //preprocesare (determinare numere prime)

 for (i=0; i<N; i++)
     {
     	fin>>v[i];
     	if (v[i]>vmax) vmax=v[i];
     }
 //ciur
 vmax=sqrt((double)vmax);
 for (d=2; d*d<=vmax; d++)
      if (!ciur[d])
          for (j=d*d; j<=vmax; j+=d)
              ciur[j]=1;
 //transfer intr-un vector numerele prime <=vmax
 prim[0]=2; nrprim=1;
 for (d=3; d<=vmax; d+=2)
      if (!ciur[d]) prim[nrprim++]=d;
 //descompunere in factori primi eficient, euler
 for (i=0; i<N; i++)
     {
     	nr=1;
	for (j=0; j<nrprim && prim[j]*prim[j]<=v[i]; j++)
		     {
		      for (p=0; v[i]%prim[j]==0; p++,v[i]/=prim[j]);
		      nr*=(p+1);
		      }
     	 if (v[i]>1) nr*=2;
		 fout<<nr<<'\n';
     }
 fout.close();
 return 0;
}
