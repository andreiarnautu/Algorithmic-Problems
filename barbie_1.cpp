// Infoarena - Arhiva Educationala rucsac
// Februrie 2012 Marius Dumitran
// Programare dinamica clasica timp O(N*G) memorie O(G)

#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
#define maxn 5001
#define maxg 10001

using namespace std;

long long W[maxn], P[maxn];
long long Optim[maxg];

int main() {

    freopen("barbie.in", "r", stdin);
    freopen("barbie.out", "w", stdout);
    int N, G, G1;
    scanf("%d %d", &G1, &G);
    G-=G1;
    scanf("%d",&N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d %d", &P[i], &W[i]);
    }

    Optim[0] = 0;
    long long sol = 123456789;
    long long qq;
    for( int i = 1; i <= N; ++i)
        for( int j = G - W[i]; j >= 0; --j) {
            if( Optim[j+W[i]] < Optim[j] + P[i] )
            {
                qq=(G-j)/W[i];
                Optim[j+W[i]*qq] = Optim[j] + qq*P[i];
                if( Optim[j+W[i]*qq] < sol)
                    sol = Optim[j+qq*W[i]];
            }
        }
    printf("%d", sol);
    return 0;
}
