#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;
FILE *fin=freopen("par.in","r",stdin);
FILE *fout=freopen("par.out","w",stdout);

int n, cnt;
stack <char> Stack;
char c;

int main()
{
    scanf("%d ", &n);
    for(int i = 1; i <= n ; ++i)
    {
        c = getchar();
        if( c == '(' )
            Stack.push(c);
        else
        {
            if( !Stack.empty() )
                Stack.pop();
            else
            {
                Stack.push('(');
                ++cnt;
            }
        }
    }
    if( Stack.size() % 2 == 0 )
        printf("%d", cnt + Stack.size() / 2);
    else
        printf("-1");
    return 0;
}
