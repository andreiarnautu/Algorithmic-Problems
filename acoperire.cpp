#include <cstdio>
using namespace std;
FILE *fin=freopen("acoperire.in","r",stdin);
FILE *fout=freopen("acoperire.out","w",stdout);

int A[300][300], val = 0;

void Pos1(int x, int y)
{
    A[x][y] = A[x][y - 1] = A[x + 1][y] = A[x + 2][y] = val;
}

void Pos2(int x, int y)
{
    A[x][y] = A[x][y + 1] = A[x + 1][y] = A[x + 2][y] = val;
}

void Pos3(int x, int y)
{
    A[x][y] = A[x][y - 1] = A[x - 1][y] = A[x - 2][y] = val;
}

void Pos4(int x, int y)
{
    A[x][y] = A[x][y + 1] = A[x - 1][y] = A[x - 2][y] = val;
}

void Pos5(int x, int y)
{
    A[x][y] = A[x - 1][y] = A[x][y + 1] = A[x][y + 2] = val;
}

void Pos6(int x, int y)
{
    A[x][y] = A[x + 1][y] = A[x][y + 1] = A[x][y + 2] = val;
}

void Pos7(int x, int y)
{
    A[x][y] = A[x - 1][y] = A[x][y - 1] = A[x][y - 2] = val;
}

void Pos8(int x, int y)
{
    A[x][y] = A[x + 1][y] = A[x][y - 1] = A[x][y - 2] = val;
}

void Gen_First(int x, int y)
{
    ++val; Pos6(x, y + 1);
    ++val; Pos7(x + 1, y + 4);
    ++val; Pos5(x + 2, y);
    ++val; Pos6(x + 3, y);
    ++val; Pos6(x + 4, y + 1);
    ++val; Pos7(x + 5, y + 4);
    ++val; Pos7(x + 2, y + 5);
    ++val; Pos8(x + 3, y + 5);
}

int main()
{
    int n, i, j, i1, j1, i2, j2, i3, j3, i4, j4, m, cnt, x, y;
    scanf("%d", &n);

    if(n % 4 != 2)
    {
        printf("-1");
        return 0;
    }

    i1 = j1 = m = (n - 6) / 2;
    i2 = i1; j2 = j1 + 5;
    i3 = i1 + 5; j3 = j1;
    i4 = i1 + 5; j4 = j1 + 5;

    Gen_First(i1, j1);

    m /= 2; cnt = 1;

    while(m)
    {
        ++val; Pos1(i1 - 2, j1);
        ++val; Pos2(i2 - 2, j2);
        ++val; Pos3(i3 + 2, j3);
        ++val; Pos4(i4 + 2, j4);
        x = i1 - 1, y = j1 - 2;
        for(i = 1; i <= cnt + 1; ++i, x += 4)
        {
            ++val; Pos2(x, y);
        }
        x = i1 + 2, y = j1 - 1;
        for(i = 1; i <= cnt + 1; ++i, x += 4)
        {
            ++val; Pos3(x, y);
        }
        x = i1 - 2, y = j1 + 1;
        for(i = 1; i <= cnt; ++i, y += 4)
        {
            ++val; Pos6(x, y);
        }
        x = i1 - 1, y = j1 + 4;
        for(i = 1; i <= cnt; ++i, y += 4)
        {
            ++val; Pos7(x, y);
        }
        x = i2 - 1, y = j2 + 1;
        for(i = 1; i <= cnt + 1; ++i, x += 4)
        {
            ++val; Pos2(x, y);
        }
        x = i2 + 2, y = j2 + 2;
        for(i = 1; i <= cnt + 1; ++i, x += 4)
        {
            ++val; Pos3(x, y);
        }
        x = i3 + 2, y = j3 + 1;
        for(i = 1; i <= cnt; ++i, y += 4)
        {
            ++val; Pos5(x, y);
        }
        x = i3 + 1, y = j3 + 4;
        for(i = 1; i <= cnt; ++i, y += 4)
        {
            ++val; Pos8(x, y);
        }

        i1 -= 2, j1 -= 2, i2 -= 2, j2 += 2, i3 += 2, j3 -= 2, i4 += 2, j4 += 2;
        ++cnt;
        --m;
    }

    for(i = 0; i < n ; ++i)
    {
        for(j = 0; j < n ; ++j)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    return 0;
}
