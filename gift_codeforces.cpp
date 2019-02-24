#include <cstdio>
#include <cstring>
using namespace std;

char s[13], aux[13];

int main()
{
    int len, i, j, l;
    bool ok;
    gets(s);
    len = strlen(s);
    for(i = 0; i <= len; ++i)
    {
        for(j = i + 1; j <= len; ++j)
            aux[j] = s[j - 1];
        for(j = i - 1; j >= 0; --j)
            aux[j] = s[j];
        for(l = 97; l <= 122; ++l)
        {
            aux[i] = l;
            ok = 1;
            for(j = 0; j <= len; ++j)
                if( aux[j] != aux[len - j] )
                {
                    ok = 0;
                    break;
                }
            if(ok)
            {
                printf("%s", aux);
                return 0;
            }
        }
    }

    printf("NA");
    return 0;
}
