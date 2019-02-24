#include <cstdio>
using namespace std;
FILE *fin=freopen("joc8.in","r",stdin);
FILE *fout=freopen("joc8.out","w",stdout);

int main()
{
    int op, st, dr, m, ok = 0;
    scanf("%d%d", &st, &dr);
    while( !ok && st <= dr )
    {
        scanf("%d", &op);
        m = (st + dr) / 2;
        if(op)
            ok = 1;
        else
        {
            scanf("%d", &op);
            if(op)
                dr = m - 1;
            else
                st = m + 1;
        }
    }
    if(ok)
        printf("%d", m);
    else
        printf("0");
    return 0;
}
