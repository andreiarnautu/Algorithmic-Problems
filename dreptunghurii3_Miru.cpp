#include<cstdio>
#include<algorithm>
#define DIM 3003
using namespace std;

FILE *fin = freopen("dreptunghiuri3.in","r",stdin);
FILE *fout = freopen("dreptunghiuri3.out","w",stdout);

int N, M, K, L, C, S, pas, l1, c1, l2, c2, nr1, nr2;
int vi[DIM], vj[DIM];
int w[DIM][DIM], MAX = -2000000000;
long long sol;
int line[DIM], col[DIM], Line[DIM], Col[DIM];

struct {int i1, i2, j1, j2, val;} v[1002];

int bs_line(int);
int bs_col(int);
void LINE();
void COL();

int main()
    {
        scanf("%d%d%d", &N, &M, &K);


        for (int i = 1; i <= K; i++) /* O(K) */
        {
            //scanf("%d%d%d%d%d", &v[i].j1, &v[i].i1, &v[i].j2, &v[i].i2, &v[i].val);
            scanf("%d%d%d%d%d", &v[i].i1, &v[i].j1, &v[i].i2, &v[i].j2, &v[i].val);
            pas = 3 * i;
            vi[pas] = v[i].i1, vi[pas - 1] = v[i].i2, vi[pas - 2] = v[i].i2 + 1;
            vj[pas] = v[i].j1, vj[pas - 1] = v[i].j2, vj[pas - 2] = v[i].j2 + 1;
        }


        LINE(); /* O(K log K) */
        COL(); /* O(K log K) */

        /* pentru for-ul de mai jos: O(K log K) */
        for (int i = 1; i <= K; i++)
        {

            l1 = bs_line(v[i].i1), l2 = bs_line(v[i].i2);
            c1 = bs_col(v[i].j1), c2 = bs_col(v[i].j2);

            w[line[l1]][col[c1]] += v[i].val; w[line[l2] + 1][col[c2] + 1] += v[i].val;
            w[line[l1]][col[c2] + 1] -= v[i].val;
            w[line[l2] + 1][col[c1]] -= v[i].val;
        }

        L = nr1 - 1;
        C = nr2 - 1;

        //printf("\n%d %d\n", L, C);

        /* K^2 pentru forul de mai jos */

        for (int i = 1; i <= L; i++)
        {
            for (int j = 1; j <= C; j++)
            {
                w[i][j] += w[i - 1][j] + w[i][j - 1] - w[i - 1][j - 1];

                if (w[i][j] == MAX)
                    sol += 1LL * (Line[i + 1] - Line[i]) * (Col[j + 1] - Col[j]);
                else
                    if (w[i][j] > MAX)
                    {
                        MAX = w[i][j];
                        sol = 1LL * (Line[i + 1] - Line[i]) * (Col[j + 1] - Col[j]);
                    }
               // printf("%lld ", sol);
            }
            //printf("\n");
        }

        printf("%d %lld", MAX, sol);

    }

void LINE()
{
    sort (vi + 1, vi + 1 + 3 * K);
    for (int i = 1; i <= 3 * K; i++)
        if (vi[i] != vi[i - 1])
        {
            line[i] = ++nr1;
            Line[nr1] = vi[i];
            //printf("%d ", vi[i]);
        }
        else
            line[i] = nr1;

    //printf("\n");
}

void COL()
{
    sort (vj + 1, vj + 1 + 3 * K);
    for (int i = 1; i <= 3 * K; i++)
        if (vj[i] != vj[i - 1])
        {
            col[i] = ++nr2;
            Col[nr2] = vj[i];
            //printf("%d ", vj[i]);
        }
        else
            col[i] = nr2;

    //printf("\n");
}

 int bs_line (int val)
 {
     int left = 1, right = 3 * K, aux;

     while (left <= right)
     {
         aux = (left + right) / 2;
         if (vi[aux] < val)
            left = aux + 1;
         else
            right = aux - 1;
     }

     return left;
 }

 int bs_col (int val)
 {
     int left = 1, right = 3 * K, aux;

     while (left <= right)
     {
         aux = (left + right) >> 1;
         if (vj[aux] < val)
            left = aux + 1;
         else
            right = aux - 1;
     }

     return left;
 }
