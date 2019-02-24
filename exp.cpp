#include <cstdio>
#include <fstream>
using namespace std;
ifstream in("exp.in");
ofstream out("exp.out");
FILE *fin=freopen("exp.in","r",stdin);
FILE *fout=freopen("exp.out","w",stdout);
int N;
char s[64006];
long Sum;

void Read()
{
    in>>N;
    in>>s;
    //scanf("%s",&s);
 //   printf("%s",s);
}

int Min(long long x)
{
    int c , ok =0, r;
    while( x > 0 )
    {
        r = x % 10;
        if( !ok )
        {
            c = r;
            ok = 1;
        }
        else if( r < c )
            c = r;
        if( c == 0 )
            return c;
        x /= 10;
    }
    return c;
}

int Max(long long x)
{
    int c, r, ok=0;
    while( x > 0 )
    {
        r = x % 10;
        if( !ok )
        {
            c = r;
            ok = 1;
        }
        else if( r > c)
            c = r;
        if( c == 9 )
            return c;
        x /= 10;
    }
    return c;
}

void Solve()
{
    long long x, y;
    for(int i=0; i<N ; ++i)
    {
        scanf("%d%d",&x,&y);
        if( s[i] == '-' )
            Sum -= Min(x) * Min(y);
        else
            Sum += Max(x) * Max(y);
    }
    out<<Sum<<'\n';
}

int main()
{
    Read();
    Solve();
    return 0;
}
