#include <fstream>
#include <cmath>
using namespace std;
unsigned int uz[10];
int co[10];
int c;
unsigned int n, maxim;

int main()
{
 unsigned int i, j, k, x, aux;
 ifstream fin("joc14.in");
 ofstream fout("joc14.out");
 fin>>n;
 for (i=0; i<n; i++)
     {
      fin>>x;
      uz[x]++;
     }
 for (i=1; i<10; i++)
     if (uz[i]) c++;
 fout<<c<<'\n';
 maxim=sqrt(double(n));
 fout<<maxim<<'\n';
 for (i=1; i<=9; i++) co[i]=i;
 for (i=1; i<9; i++)
     for (j=i+1; j<=9; j++)
         if (uz[co[i]]<uz[co[j]])
            {aux=co[i]; co[i]=co[j]; co[j]=aux;}

 k=1;
 for (i=0; i<maxim; i++)
     {
     for (j=0; j<maxim; )
         if (uz[co[k]])
            {fout<<co[k]; uz[co[k]]--; j++;}
            else
            k++;
     fout<<'\n';
     }
 fout.close();
 return 0;
}




