#include <map>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;
ofstream out("bacan.out");
FILE *fin=freopen("bacan.in","r",stdin);


/*class CompS
{
    public:
        bool operator() (const char *x, const char *y)
        {
            return strcmp(x, y) <  0;
        }
};
*/
map<string, int> HASH;
map<string, int>::iterator it;
string s, s1;
char c, s2[30], s3[30], s4[30];

int main()
{
    int n, i, pos, x, j, len;
    char c;
    scanf("%d ", &n);

    for(i = 0; i < n; ++i)
    {
        gets(s2);
        len = strlen(s2);
        for(j = len - 1; j >= 0; --j)
            if( s2[j] == '*' )
            {
                pos = j;
                break;
            }
        strncpy(s3, s2 + pos + 2, len - pos - 1);
        strcpy(s2 + pos, s2 + len);
        s1 = s2;
        x = atoi(s3);
       // s1 = s.substr(0, pos - 1);
        HASH[s1] += x;
    }

    out << HASH.size() << "\n";

    for(it = HASH.begin(); it != HASH.end(); ++it)
        out << it -> first << " * " << it -> second << '\n';

    return 0;
}
