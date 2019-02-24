#include <cstdio>
using namespace std;
FILE *fin=freopen("colina.in","r",stdin);
FILE *fout=freopen("colina.out","w",stdout);
int N, M, P;
long V[100001];

void Read()
{
    scanf("%d%d", &M, &N);
    for(int i = 1; i <= N ; ++i )
        scanf("%d", &V[i]);
    for(int i = 1; i <= N ; ++i )
        if( V[i] > V[i - 1] && V[i] > V[i + 1] )
        {
            P = i;
            break;
        }
}

int main()
{
    Read();
}
