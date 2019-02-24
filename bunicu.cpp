#include <cstdio>

using namespace std;

FILE *fin=freopen("bunicu.in","r",stdin);
FILE *fout=freopen("bunicu.out","w",stdout);

char S[1003];
bool F[1003];
int N, cnt, pos, j;


void Write(int D, int k)
{
    for(int i = 0 ; i < D ; ++i )
    {
        if( i == k )
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void Solve()
{
    scanf("%d", &N);
    for(int i = 0 ; i < N ; ++i )
        F[i] = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%s", &S);
        cnt = 0;
        pos = 0;
        for( j = 0 ; j < N ; ++j )
            if( S[j] == '1' )
            {
                ++cnt;
                pos = j;
            }
        if( cnt == 1 )
            F[pos] = 1;
    }

    for(int i = 0; i < N ; ++i )
    {
        if( !F[i] )
        {
            Write(N , i);
            return;
        }
    }
    Write(N, N);
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
        Solve();
}
