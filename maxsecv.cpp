#include <cstdio>
using namespace std;
FILE *fin=freopen("maxsecv.in","r",stdin);
FILE *fout=freopen("maxsecv.out","w",stdout);

int l1, l2;

int main()
{
    int x, n, len = 0;
    scanf("%d", &n);

    for(int i = 0; i < n ; ++i)
    {
        scanf("%d", &x);
        if(x)
            ++len;
        else
        {
            if(len > l1)
            {
                l2 = l1;
                l1 = len;
            }
            else if( len > l2 )
                l2 = len;
            len = 0;
        }
    }
    if( len > l1 )
    {
        l2 = l1;
        l1 = len;
    }
    else if(len > l2)
        l2 = len;

    printf("%d", l1 + l2);
    return 0;
}
