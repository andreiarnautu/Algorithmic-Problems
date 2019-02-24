/**
  *  Worg
  *  Mar 9, 2018
  *  10:25:10 AM
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("kgon.in", "r", stdin); FILE *fout = freopen("kgon.out", "w", stdout);

const int maxN = 1e5 + 5;
const double pi = std::acos(-1.0);
const double eps = 1e-5;

/*-------- Data --------*/
int n, k;
double r;

double d[maxN];

int dp[maxN];
/*-------- --------*/

void ReadInput() {
	scanf("%d%d", &n, &k); scanf("%lf", &r);

	for(int i = 1; i <= n; i++) {
	  scanf("%lf", &d[i]);
	}
}

int Solve() {
	int ans = 0;
	double dist = 2 * pi * r / (double)k;

	for(int i = 1, j = 1; i <= n; i++) {
		while(d[i] - d[j] > dist + eps) {
			j++;
		}

		double distHere = d[i] - d[j] - dist;
		if(-eps <= distHere && distHere <= eps) {
			dp[i] = dp[j] + 1;
		}

		ans += (dp[i] == k - 1);
	}

	return ans;
}

int main() {
	ReadInput();

	printf("%d\n", Solve());

	return 0;
}
