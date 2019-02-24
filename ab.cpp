#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
using namespace std;
ifstream in("ab.in");
ofstream out("ab.out");
FILE *fin=freopen("ab.in","r",stdin);
FILE *fout=freopen("ab.out","w",stdout);
long A[1000110], B[1000110], secv, max1, max2;
string S;
long long int Sol;

int main()
{
    int nrA = 0, nrB = 0;
    char c = 'x';
    //getline(in, S);
    while( !in.eof() )
    {
        in >> c;
        if( in.eof() )
            break;
        if( c == 'a' )
        {
            ++nrA;
        }
        else if( c == 'b' )
            ++nrB;
        if( nrA == nrB )
        {
            ++Sol;
            secv++;
            Sol += secv - 1;
        }
        else if( nrA > nrB )
        {
            ++A[nrA - nrB];
        //Sol += A[nrA - nrB] - 1;
        }
        else
        {
            ++B[nrB - nrA];
          //  Sol += B[nrB - nrA] - 1;
        }
    }
    if( A[1] == 0 && secv == 0 && nrB - nrA > 100000 )
    {
        printf("0");
        return 0;
    }
    for(int i = 1 ; A[i] ; ++i )
    {
        Sol += 1ll * A[i] * (A[i] - 1) / 2;
    }
    for(int i = 1 ; B[i] ; ++i )
    {
        Sol += 1ll * B[i] * (B[i] - 1) / 2;
    }
    printf("%lld", Sol);
}
