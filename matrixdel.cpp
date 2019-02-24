#include <fstream>
using namespace std;
ifstream in("matrixdel.in");
ofstream out("matrixdel.out");

int mat[100][100];

void prelucrare(int m, int n)
{
    int i,j,p,q,x,ok;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            in>>mat[i][j];
    in>>p;
    for(i=0;i<p;i++)
    {
        in>>x;
        for(j=0;j<n;j++)
            mat[x-1][j]=-1;
    }
    in>>q;
    for(j=0;j<q;j++)
    {
        in>>x;
        for(i=0;i<m;i++)
            mat[i][x-1]=-1;
    }
    for(i=0;i<m;i++)
    {
        ok=0;
        for(j=0;j<n;j++)
            if(mat[i][j]!=-1)
                {
                    out<<mat[i][j]<<" ";
                    ok=1;
                }
        if(ok==1)
            out<<endl;
    }
}

int main()
{
    int m,n;
    in>>m>>n;
    prelucrare(m,n);
    return 0;
}
