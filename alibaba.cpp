#include <cstdio>
#include <stack>
using namespace std;
FILE *fin=freopen("alibaba.in","r",stdin);
FILE *fout=freopen("alibaba.out","w",stdout);

stack <int> St;
int n, k, nr, cif, V[10003];
char S[10003];

int main()
{
    scanf("%d %d ", &n, &k);
    scanf("%s", S);
    for(int i = 1; i <= n ; ++i)
    {
        cif = S[i - 1] - 48;
        while( !St.empty() && St.top() < cif && n - i + nr >= n - k )
        {
            St.pop();
            --nr;
        }
        if( nr < n - k )
        {
            St.push(cif);
            ++nr;
        }
    }
    for(int i = 1; i <= nr ; ++i)
    {
        V[i] = St.top();
        St.pop();
    }

    for(int i = nr; i > 0; --i)
        printf("%d", V[i]);
    return 0;
}
