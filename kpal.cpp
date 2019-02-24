#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
ifstream in("kpal.in");
ofstream out("kpal.out");
int K, Sol, Length;
char S[5003];


void Read()
{
    in >> K;
    in.get();
    in.get(S, 5002);
}

void Middle(int x)
{
    int p, i, Dif = 0;
    p = min( x , Length - 1 - x);
    if( p <= K )
    {
        Sol += p;
        return;
    }
    i = 1;
    do
    {
        if( S[x - i] != S[x + i] )
            ++Dif;
        if( Dif <= K )
            ++Sol;
        if( Dif > K || i > p )
            return;
        ++i;
    }while( Dif <= K && i <= p );
}

void Virtual_Middle(int a, int b)
{
    int  Dif = 0;
    if( min( a + 1 , Length - b ) <= K )
    {
        Sol += min( a + 1 , Length - b );
        return ;
    }
    do
    {
        if( S[a] != S[b] )
            ++Dif;
        if( Dif <= K )
            ++Sol;
        if( Dif > K || a == 0 || b == Length )
            return;
        --a;
        ++b;
    }while( Dif <= K && a >= 0 && b < Length );
}

int main()
{
    Read();
    Length = Sol = strlen(S);
    int i;
    for( i = 1 ; i < Length - 1 ; ++i )
        Middle( i );
    for( i = 0 ; i < Length - 1 ; ++i )
        Virtual_Middle( i , i + 1 );
    out << Sol;
    return 0;
}
