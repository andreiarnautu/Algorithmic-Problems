#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;
 
FILE *fin=freopen("editor.in","r",stdin);
FILE *fout=freopen("editor.out","w",stdout);
 
stack <char> St, Aux;
char s[60001];
 
 
 
char Pair(char c)
{
    if( c == '(' )
        return ')';
    if( c == ')' )
        return '(';
    if( c == '[' )
        return ']';
    if( c == ']' );
        return '[';
}
 
void Check()
{
    while( !Aux.empty() )
        Aux.pop();
 
    while( !St.empty() )
    {
        if( St.top() == '(' || St.top() == '[' )
        {
            if( Aux.empty() || Aux.top() != Pair(St.top()) )
            {
                printf(":(\n");
                return;
            }
            else
                Aux.pop();
        }
 
        else
            Aux.push(St.top());
 
        St.pop();
    }
    if( !Aux.empty() )
    {
        printf(":(\n");
        return;
    }
    printf(":)\n");
}
 
void Solve()
{
    int i, len;
    while( !St.empty() )
        St.pop();
    gets(s);
    len = strlen(s);
 
    for(i = 0; i < len ; ++i)
    {
        if( s[i] == ')' || s[i] == '(' || s[i] == ']' || s[i] == '[' )
            St.push( s[i] );
        else if( s[i] == '*' )
        {
            if( !St.empty() )
                St.pop();
        }
        else
            Check();
    }
}
 
int main()
{
    int t;
    scanf("%d", &t); getchar();
    for(; t > 0; --t)
        Solve();
}