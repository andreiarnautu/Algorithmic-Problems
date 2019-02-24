#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin=freopen("kbiti.in","r",stdin);
FILE *fout=freopen("kbiti.out","w",stdout);



int main()
{
    int t;
    long long int sol;
    char s[35];

    scanf("%d", &t);
    getchar();
    for(; t > 0 ; --t )
    {
        gets(s);

        sol = 1;
        for(int i = strlen(s) - 1 ; i >= 0 ; --i )
            if( s[i] == '1' )
                sol = 1LL * sol + (1LL * 1 << strlen(s) - i - 1);

        printf("%lld\n", sol);

    }

    return 0;
}
