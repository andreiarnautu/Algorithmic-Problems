/*
	implementare Dan Pracsiu
	complexitate O( L x C + Q )
*/

#include<cstdio>
#define Dim 1002
#define InFile "acces.in"
#define OutFile "acces.out"

using namespace std ;

int a[Dim][Dim], b[Dim][Dim], L, C ;

inline int Minim(int a, int b)
{
	return a < b ? a : b;
}

void ConstructieB()
{
	int i, j ;
	// prima linie
	for (i=1 ; i<=C ; i++)
		if (a[1][i] == 1) b[1][i] = 0;
		else b[1][i] = b[1][i-1] + 1;

	// prima coloana:
	for (i=1 ; i <= L ; i++)
		if (a[i][1] == 1) b[i][1] = 0 ;
		else b[i][1] = b[i-1][1] + 1 ;

	// construiesc restul matricei
	for (i=2 ; i <= L ; i++)
		for (j=2 ; j<=C ; j++)
			if (a[i][j] == 1) // perete
			{
				if ( (b[i-1][j] == 0) || (b[i][j-1] == 0) )
					b[i][j] = 0 ;
				else if ( (b[i-1][j] > 0) && (b[i][j-1] > 0) )
					b[i][j] = -b[i-1][j-1] ;
				else b[i][j] = Minim(b[i-1][j], b[i][j-1]);
			}
			else // liber!
			{
				if ( (b[i-1][j] > 0) && (b[i][j-1] > 0) )
				{
					b[i][j] = 1 + b[i-1][j] + b[i][j-1] ;
					if (b[i-1][j-1] < 0)
						b[i][j] = b[i][j] + b[i-1][j-1] ;
					else
						b[i][j] = b[i][j] - b[i-1][j-1] ;
				}
				else
					if (b[i-1][j] > 0) b[i][j] = 1 + b[i-1][j] ;
					else if (b[i][j-1] > 0) b[i][j] = 1 + b[i][j-1] ;
					else b[i][j] = 1 ;
			}
}

int main()
{
	int i, j, K, p, q;
	freopen(InFile, "r", stdin);
	freopen(OutFile, "w", stdout);

	scanf("%d %d", &L, &C) ;
	for (i=1 ; i<=L ; i++)
		for (j=1 ; j<=C ; j++)
			scanf("%d", &a[i][j]);
	ConstructieB();

	scanf("%d", &K);

	for (i=1 ; i <= K ; i++)
	{
		scanf("%d %d", &p, &q) ;
		printf("%d\n", b[p][q]);
	}

	return 0 ;
}
