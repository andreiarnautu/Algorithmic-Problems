// Complexitate O(n)

#include <fstream>
#include <iostream>
#include <cstdlib>

#define IN   "panouri.in"
#define OUT  "panouri.out"
#define DIM1 15001
#define DIM2 1001
using namespace std;
unsigned int a[DIM1];
unsigned int b[DIM2], fr[DIM1];
/*
	 b[i] = 1 => panoul de tip i apartine firmei.
	 frecventa, fr[i] = x,  daca b[i] = 1
	 (panoul de tip i apartine firmei si daca numarul i apare
	 de x ori in subsecventa a[s..f])
 */
unsigned  int n, m, s, f, i, nr, best, x;
unsigned  int minim, maxim;
ofstream fout(OUT);

void ReadData();
void Solve();

int main()
{
	ReadData();
	Solve();
	return 0;
}

void  ReadData()
{
	ifstream fin(IN);
	fin >> n >> m;
    for (i = 1; i <= n; i++ )
		 fin >> a[i];
    for (i = 1; i <= m; i++ )
    {
		fin >> x;
        b[x] = 1;
	}
    fin.close();
}

void Solve()
{
	s = 1; f = 1;
    nr = 0;
    if ( b[a[s]] == 1 )
   		fr[a[s]] = 1, nr = 1;

  	while (f < n && nr < m)           // cautam cel mai mic al 2-lea indice f astfel ca in a[s..f]
  	{                                 // sa fie continute toate numerele din b[]
  		f++;
		if (b[a[f]] == 1)             // face parte din b[]
        {
			if ( fr[a[f]] == 0 )      //  o singura aparitie in secventa
				nr++;
			fr[a[f]]++;
		}
    }

    if ( nr < m )                      // nu exista solutie
    {
   //     fout << nr << '\n';
    	fout << -1 << '\n';
    	fout.close();
    	return;
	}

    while (b[a[s]] == 0 || (b[a[s]] == 1 && fr[a[s]] > 1))
    	--fr[a[s++]];                  // marim s cat se poate astfel ca in secventa a[s..f]
    	                               // sa apara toate numerele din b
	best = DIM1;
	if (best > f - s)
		best = f - s, minim = s, maxim = f;

	for (f = f + 1; f <= n; f++ )
    {
		if (b[a[f]] == 1)
            fr[a[f]]++;

        while (b[a[s]] == 0 || (b[a[s]] == 1) && (fr[a[s]] > 1))
            --fr[a[s++]];              // la fiecare incrementare a indicelui f incercam
                                       // sa marim pe cat posibil si indicele s

        if (best > f - s)
            best = f - s, minim = s, maxim = f;
	}

    fout <<  best << '\n';
//  fout << min << " " << max << '\n';
    fout.close();
}

