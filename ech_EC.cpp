//Em. Cerchez 100 puncte
#include <fstream>
#include <cassert>

using namespace std;

ifstream fin("ech.in");
ofstream fout("ech.out");

int a[50];
int lg=0;
int nx[50];

void add(int x);
int rest();
int ech();
void citire();
void afisare();


int main()
{int r;
 citire();
 r=rest();
 if (r) add(11-r);
    else add(11);
 while (!ech())
	   add(11);
 afisare();
 return 0;
}

void add(int x)
{int i, t=0, s;
 nx[0]=x%10; nx[1]=x/10;
 for (i=0; i<lg; i++)
     {s=a[i]+nx[i]+t;
      a[i]=s%10;
      t=s/10;}
 if (t+nx[i]) a[lg++]=t+nx[i];
}

int rest()
{int i, r=0;
 for (i=lg-1; i>=0; i--)
     {
     	r=r*10+a[i];
     	r=r%11;
     }
 return r;
}

int ech()
{ int s1=0, s2=0;
  for (int i=0; i<lg; i+=2)
	   s1+=a[i], s2+=a[i+1];
  return s1==s2;
}

void citire()
{char c;
 int st, dr, aux;
 while (fin>>c)
       	a[lg++]=c-'0';
 //inversez a
 for (st=0, dr=lg-1; st<dr; st++, dr--)
      {	aux=a[st]; a[st]=a[dr]; a[dr]=aux;     }
}

void afisare()
{int i;
 for (i=lg-1; i>=0; i--)   fout<<a[i];
 fout<<'\n';
 fout.close();
}
