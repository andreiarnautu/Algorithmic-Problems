#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("joc12.in","r",stdin);
FILE *fout=freopen("joc12.out","w",stdout);

char S1[153], S2[153], S3[303];
int Last1, Last2, Last = -1, V1[303], V2[303];

void Read()
{
    gets(S1);
    gets(S2);
    gets(S3);
}

void Search(int x)
{

}

void Solve()
{
    for(int i = 0 ; i < strlen(S3) ; ++i )
        Search(i);
}

int main()
{
    Read();
    Solve();
    return 0;
}
