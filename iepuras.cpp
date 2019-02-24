#include <iostream>
#include <fstream>
using namespace std;
int m,n;
char a[201][201];
int di[4]={-1,0,1,0};
int dj[4]={0,-1,0,1};
struct zid{ int i,j; };
zid z1[50],z2[50];


int afara(int i,int j)
{  if (i<1 || i>m) return 1;
   if (j<1 || j>n) return 1;
   return 0;
}

int explod(int i,int j)
{  int k,i1,j1;
   if (a[i][j]=='6' || a[i][j]=='*')
     return 1;
   for (k=0;k<4;k++)
   {  i1=i+di[k];
      j1=j+dj[k];
      if (i1>=0 && i1<=m && j1>=1 && j1<=n)
	if (a[i1][j1]=='6')
	  a[i1][j1]='*';
	else
	  if (a[i1][j1]=='*')
	    return 1;
   }
   return 0;
}

int main()
{  int k,i0,j0,d,i,j,n1=0,n2=0,pz=1;
   long nrm,p=0,q=0;
   ifstream f("iepuras.in");
   ofstream g("iepuras.out");

   nrm=0;
   f>>m>>n;
   f>>i0>>j0>>d;
   for (i=1;i<=m;i++)
     for (j=1;j<=n;j++)
     {  f>>a[i][j];
	if (a[i][j]=='7') nrm++;
	if (a[i][j]=='8')
	{ z1[n1].i=i;
	  z1[n1].j=j; n1++;
	}
     }
   f>>n2;
   for (i=0;i<n2;i++)
     f>>z2[i].i>>z2[i].j;
   f.close();

   i=i0; j=j0;
   while (1)
   { i=i+di[d-1]; j=j+dj[d-1]; p++;

     if (i==3 && j==190)
       cout<<"bla";
     // afara
     if (afara(i,j))
     {  g<<"RATACIT"<<endl;
	g<<i-di[d-1]<<" "<<j-dj[d-1]<<endl;
	g<<q<<" "<<p;
	break;
     }

     // morcov
     if (a[i][j]=='7') { q++; a[i][j]='0'; }

     // e bomba sau in vecinatatea unei bombe pregatita sa explodeze
     if (explod(i,j))
     {  g<<"INGERAS"<<endl;
	g<<i<<" "<<j<<endl;
	g<<q<<" "<<p;
	break;
     }

     // a cules toti morcovii
     if (q==nrm)
     {  g<<"FERICIT"<<endl;
	g<<i<<" "<<j<<endl;
	g<<q<<" "<<p;
	break;
     }

     if (a[i][j]=='9')
     {  if (pz==1)
	{ for (k=0;k<n1;k++)
	    a[z1[k].i][z1[k].j]='0';
	  for (k=0;k<n2;k++)
	    a[z2[k].i][z2[k].j]='8';
	  pz=2;
	}
	else
	{ for (k=0;k<n2;k++)
	    a[z2[k].i][z2[k].j]='0';
	  for (k=0;k<n1;k++)
	    a[z1[k].i][z1[k].j]='8';
	  pz=1;
	}
     }

     // sageata, schimba directia
     if (a[i][j]=='1') { d=1; a[i][j]='0'; }
     if (a[i][j]=='2') { d=2; a[i][j]='0'; }
     if (a[i][j]=='3') { d=3; a[i][j]='0'; }
     if (a[i][j]=='4') { d=4; a[i][j]='0'; }

     // pom sau zid, schimba directia
     if (a[i+di[d-1]][j+dj[d-1]]=='5' || a[i+di[d-1]][j+dj[d-1]]=='8')
       if (d==1) d=3;
       else
	if (d==2) d=4;
	else
	  if (d==3) d=1;
	  else
	    d=2;

   }
   g.close();

}
