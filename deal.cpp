//Em. Cerchez 100 puncte
#include <cstdio>
#include <cassert>
#include <fstream>
#define MAXN 100008
using namespace std;

int nr[MAXN];//nr[i]=numarul de aparitii ale valorii i
int n;
int sol[MAXN]; //aici construiesc solutia

int main()
{
 int m = 0, i, a;
 freopen("deal.in", "r", stdin);
 freopen("deal.out", "w", stdout);

 scanf("%d", &n);
 assert((1 <= n) && (n <= 100000));

 m=0; //in m calculez maximul
 for (i = 0; i < n; ++i)
     {
      scanf("%d", &a);
      assert((1 <= a) && (a <= 100000));
      ++nr[a];
      if (m<a) m=a;
     }


 int k = -1;
 //verific daca exista un element majoritar
 int jum=(n+1)/2;
 for (i=0; i <= m; ++i)
     if (nr[i] > jum)
         { k = i; break; }

 //k este o valoare care apare de cel putin jum ori
 if (k != -1)
    {
    int l = 0;
    if (k != m) //k nu este maximul
       {
        //parcurg valorile i mai mari decat k si formez perechi de forma k, i
		for (i = m; i > k; --i)
            {
			 while (nr[i] > 0)
                   {
				   sol[l++] = k; --nr[i];
				   sol[l++] = i; --nr[k];
				   }
			}
		}
    int r = n - 1;
    //parcurg valorile pana la k si incep completarea vectorului solutie de la coada
    for (i = 0; i <= k; ++i)
        {
		 while (nr[i] > 0)
            {
	        if (r < l){break;}
	        sol[r--] = k; --nr[k];
	        if (r < l) {break; }
	        sol[r--] = i; --nr[i];
			}
		}
    }
else
//if (k == -1) //nu exista un element majoritar
   {
	for (k=m,i=1; i<n; )
		if (nr[k]) {sol[i]=k; nr[k]--; i+=2;}
			else k--;
	for (i=0; i<n; )
		if (nr[k]) {sol[i]=k; nr[k]--; i+=2;}
			else k--;
   }

//calculez suma inaltimilor dealurilor
long long int rez = 0;
for (i = 0; i < n; ++i)
    {
     int j = i;
     while ((j < n) && (sol[j] <= sol[j + 1])) ++j;
     if (j-i+1>1) rez += sol[j];
     i = j;
    }
ifstream in("deal.in");
ofstream out("deal.out");
    out<<rez;
//printf("%I64d\n", rez);
/*
for (i=0; i<n; ++i)	printf("%d ", sol[i]);
printf("\n");
for (i=0; i<n; ++i)	printf("%d ", a[i]);*/
return 0;
}

