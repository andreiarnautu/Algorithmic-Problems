#include <iostream>
using namespace std;

int n,m,k,a[101][101];
int s[101][101];

int main()
{
	cin >> n >> m >> k;
	for(int i = 1 ; i <= n ; ++i)
		for(int j = 1 ; j <= m ; ++j)
			cin >> a[i][j];
	for(int i = 1 ; i <= n ; ++i)
		for(int j = 1 ; j <= m ; ++j)
			s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
	long long int Max = 0;
	for(int p = 1 ; p <= k ; p ++)
	{
		int i1,j1,i2,j2;
		cin >> i1 >> j1 >> i2 >> j2;
		int SC = s[i2][j2] - s[i1-1][j2] - s[i2][j1-1] + s[i1-1][j1-1];
		if(SC > Max)
			Max = SC;
	}
	cout << Max << endl;
	return 0;
}
