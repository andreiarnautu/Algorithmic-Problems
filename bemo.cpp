/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;

FILE *f = freopen("bemo.in", "r", stdin);
FILE *g = freopen("bemo.out", "w", stdout);

const int N_MAX = 1501;
const int buffDIM = 10000;

int v[N_MAX][N_MAX];
short int x[N_MAX * N_MAX], y[N_MAX * N_MAX];
int from[N_MAX], to[N_MAX];
bitset< N_MAX > viz[N_MAX];
int n, m;

class inputReader{
    char buffer[buffDIM];
    int pos;

public:

    bool digit(char c)
    {
        return ('0' <= c && c <= '9');
    }

    void get_buffer()
    {
        fread(buffer, 1, buffDIM, stdin);
        pos = 0;
    }

    void get_int(int &nr)
    {
        nr = 0;

        while (!digit(buffer[pos]))
        {
            if (++pos == buffDIM)
                get_buffer();
        }

        while (digit(buffer[pos]))
        {
            nr = nr * 10 + buffer[pos] - '0';

            if (++pos == buffDIM)
                get_buffer();
        }

    }
}cin;

void read()
{
    cin.get_int(n);
    cin.get_int(m);

    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
        {
            cin.get_int(v[i][j]);

            x[v[i][j]] = i;
            y[v[i][j]] = j;
        }

    for (int i=1; i<=m; i++)
        to[i] = n;
}

void solve()
{
    for (int i = 1; i <= n * m; i++)
    {
        int linie = x[i];
        int coloana = y[i];

        if (linie < from[coloana] || linie > to[coloana])
            continue;

        for (int j = 1; j < coloana; j++)
            to[j] = min(to[j], linie);

        for (int j = coloana + 1; j <= m; j++)
            from[j] = max(from[j], linie);

        viz[x[i]][y[i]] = 1;
    }
}

void write()
{
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            if (viz[i][j])
                printf("%d ", v[i][j]);
        }
    }
}

int main()
{
    read();
    solve();
    write();
    return 0;
}
