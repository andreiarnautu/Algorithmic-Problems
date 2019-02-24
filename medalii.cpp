#include <cstdio>
using namespace std;
FILE *fin = freopen("medalii.in","r",stdin);
FILE *fout = freopen("medalii.out","w",stdout);
int N, Prev[50001];
struct {int an, p;} A[50001];

void Read()
{
    int x = 0, Val = 0;
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d%d", &A[i].an, &A[i].p);
        Prev[i] = x;
    }
    int j;
    for(int i = 1 ; i <= N ; ++i )
    {
        for( j = i + 1 ; j <= N ; ++j )
        {
            Prev[j] = i;
            if( A[j].p >= A[i].p )
                break;
        }
        i = j - 1;
    }
    Prev[N + 1] = Prev[N];
   // for(int i = 1 ; i <= N ; ++i )
      //  printf("%d ",Prev[i]);
}

int Binary_Search(int k)
{
    int st = 0, dr, m;
    dr = N;
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        if( A[m].an == k )
            return m;
        else if( A[m].an > k )
            dr = m;
        else
            st = m;
    }
    if( A[st].an > k )
        return st;
    return st + 1;
}

void Solve()
{
    int M, x, y, Pos1, Pos2;
    scanf("%d", &M);
    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%d%d", &x, &y);
        Pos1 = Binary_Search(x);
        Pos2 = Binary_Search(y);
        if( y > A[Pos2].an )
            ++Pos2;
      //  printf("%d %d",Pos1,Pos2);
        if( A[Pos1].an != x )
        {
            if( A[Pos2].an != y )
            {
                printf("POATE\n");
                continue;
            }
            if(Prev[Pos2] > Pos1)
                printf("NU\n");
            else
                printf("POATE\n");
        }
        else if( A[Pos2].an != y )
        {
            if( Prev[Pos2] > Pos1 )
                printf("NU\n");
            else
                printf("POATE\n");
        }
        else if( Pos2 - Pos1 != y - x )
        {
            if( A[Pos2].p >= A[Pos1].p )
                printf("NU\n");
            else if( Prev[Pos2] != Pos1 )
                printf("NU\n");
            else
            {
                    printf("POATE\n");
            }
        }
        else
        {
            if( A[Pos2].p >= A[Pos1].p )
                printf("NU\n");
            else if( Prev[Pos2] != Pos1 )
                printf("NU\n");
            else
                printf("DA\n");
        }
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
