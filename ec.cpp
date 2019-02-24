// How about a coding trick?
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define DIM 250250
using namespace std;
FILE *fin=freopen("ec.in","r",stdin);
FILE *fout=freopen("ec.out","w",stdout);

int T[DIM];
int n, k, t1, t2, sol1, sol2;
bool ok;
char S[50];

void Read()
{
    int i;
    scanf("%d %d", &n, &k);
    for(i = 1; i <= n * n; ++i)
        scanf("%d ", &T[i]);
    sort(T + 1, T + n * n + 1);

}

inline int EcType()
{
    int ret = 1;
    ok = 0;

    for(int i = 0; i < strlen(S) && i < 10; ++i)
        if( S[i] == '^' )
        {
            ret = 2;
            ok = 1;
        }

    int val = 0, i = 0;
    while( '0' <= S[i] && S[i] <= '9' )
        val = val * 10 + (S[i] - '0'), ++i;
    //if( !val )
        //ret = 1;

    return ret;
}

inline bool binary(long long int val)
{
    int st = 1, dr = n * n, m;
    while( st <= dr )
    {
        m = (st + dr) / 2;
        if( T[m] == val )
            return 1;
        if( T[m] > val )
            dr = m - 1;
        else
            st = m + 1;
    }
    return 0;
}

inline void Type_1()
{
    ++t1;
    int i = 0, a = 0, b = 0, c = 0;

    //if( ok )
        //i = 5;

    while( '0' <= S[i] && S[i] <= '9' )
        a = a * 10 + ( S[i] - '0' ), ++i;
    i += 2;
    while( '0' <= S[i] && S[i] <= '9' )
        b = b * 10 + ( S[i] - '0' ), ++i;
    ++i;
    while( i < strlen(S) )
        c = c * 10 + ( S[i] - '0' ), ++i;

    if( a == 0 && ok )
        {   --t1; return;  }

    //printf("%d %d %d\n", a, b, c);
    c -= b;
    if( a == 0 || c % a != 0 )
        return;
    long long int aux = c / a;
    if( binary(aux) )
        {++sol1;}//printf("%s\n", S);}
}

inline void Type_2()
{
    ++t2;
    int a = 0, b = 0, c = 0, d = 0, i = 0;
    while( '0' <= S[i] && S[i] <= '9' )
        a = a * 10 + ( S[i] - '0' ), ++i;
    i += 4;
    while( '0' <= S[i] && S[i] <= '9' )
        b = b * 10 + ( S[i] - '0' ), ++i;
    i += 2;
    while( '0' <= S[i] && S[i] <= '9' )
        c = c * 10 + ( S[i] - '0' ), ++i;
    ++i;
    while( i < strlen(S) )
        d = d * 10 + ( S[i] - '0' ), ++i;

    //printf("%d %d %d %d\n", a, b, c, d);
    c -= d;
    long long int delta, aux;
    delta = b * b - 4 * a * c;
    if( a == 0 )
        {
            if( !b )
                return;
            aux = (-c) / b;
            if( binary(aux) )
                ++sol2;
            return;
        }
    //printf("%lld ", delta);
    if( delta < 0 )
        return;
    aux = sqrt((long double) delta);
    if( aux * aux != delta )
        return;
    //printf("%s ",S);
    long long int val1, val2;

    if( (-b + aux) % (2 * a) != 0 || (-b -aux) % (2 * a) != 0 )
        return;

    val1 = (-b + aux) / (2 * a);
    val2 = (-b - aux) / (2 * a);
    //printf("%lld %lld\n", val1, val2);
    if( binary(val1) && binary(val2) )
        {++sol2;}//printf("%s\n", S);}
}

int main()
{
    int type;
    Read();

    for(int i = 1; i <= k; ++i)
    {
        gets(S);
        type = EcType();
        if( type == 1 )
            Type_1();
        else
            Type_2();
    }
    printf("%d %d\n", t1, sol1);
    printf("%d %d\n", t2, sol2);
    return 0;
}
