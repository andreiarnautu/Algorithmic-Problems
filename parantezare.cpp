#include <cstdio>
#include <stack>
#include <cstring>
#define Dim 100013
using namespace std;

FILE *fin=freopen("parantezare.in","r",stdin);
FILE *fout=freopen("parantezare.out","w",stdout);

stack <int> St;
int P[Dim];
char s[Dim];

void Compute()
{
    int len;
    len = strlen(s);

    for(int i = 0; i < len ; ++i)
    {
        if( s[i] == '(' )
            St.push(i);
        else if( s[i] == ')' )
        {
            P[St.top()] = i;
            St.pop();
        }
    }

}

void Answer()
{
    int m, x;
    scanf("%d", &m);

    for(int i = 1; i <= m ; ++i)
    {
        scanf("%d", &x);
        printf("%d ", P[x]);
    }
}

int main()
{
    scanf("%s", s);
    Compute();
    Answer();
    return 0;
}
