#include <cstdio>
#include <deque>
using namespace std;

FILE *fin=freopen("paranteze.in","r",stdin);
FILE *fout=freopen("paranteze.out","w",stdout);

deque <char> D1;
deque <int> D2;
int best, n;
char s[1000003];

inline int open(char c)
{
    if( c == '(' || c == '[' || c == '{' )
        return 1;
    return 0;
}

inline char pereche(char c)
{
    if( c == '(' )
        return ')';
    if( c == ')' )
        return '(';
    if( c == '[' )
        return ']';
    if( c == ']' )
        return '[';
    if( c == '{' )
        return '}';
    if( c == '}' )
        return '{';
}

void Solve()
{
    int i, val;
    char c;
    D2.push_back(0); D1.push_back('8');

    for(i = 1; i <= n ; ++i)
    {
        c = s[i - 1];
        if(open(c))
        {
            D1.push_back(c);
            D2.push_back(0);
        }
        else
        {
            if( !D1.empty() && D1.back() == pereche(c) )
            {
                val = 2 + D2.back();
                if( val > best )
                    best = val;
                D1.pop_back(); D2.pop_back();
                if( !D1.empty() && (open(D1.back()) || D1.back() == '8') )
                {
                    D2.back() = D2.back() + val;
                    if( D2.back() > best )
                        best = D2.back();
                }
            }
            else
            {
                D1.clear();
                D2.clear();
                D1.push_back('8');
                D2.push_back(0);
            }
        }
    }
    printf("%d", best);
}

int main()
{
    scanf("%d", &n);gets(s);
    gets(s);
    Solve();
}
