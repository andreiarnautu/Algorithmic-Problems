#include <cstring>
#include <fstream>
using namespace std;
ifstream fin("astre.in");
ofstream fout("astre.out");
short A[102][102], Nr=1;
void Read()
{
    char s[102];
    while(!fin.eof())
    {
        fin >> s;
        if( fin.eof() )
            break;
        for(int i=0; i < strlen(s); ++i)
            A[Nr][i+1] = s[i] - 48;
        A[Nr][0]=strlen(s);
        ++Nr;
    }
}
int Verifica(int x, int y)
{
    int v1[208], v2[208];
    for(int i=1; i<=A[x][0] ; ++i)
    {
        v1[i] = A[x][i];
        v2[A[y][0]+i] = A[x][i];
    }
    for(int i=1; i<=A[y][0] ; ++i)
    {
        v1[A[x][0]+i] = A[y][i];
        v2[i] = A[y][i];
    }
    for(int i=1; i<=A[x][0]+A[y][0] ; ++i)
    {
        if( v1[i] > v2[i] )
            return 1;
        if( v1[i] < v2[i] )
            return 0;
    }
    return 1;
}
void Change(int x, int y)
{
    int v[104];
    for(int i=1; i<=A[x][0] ; ++i)
        v[i] = A[x][i];
    for(int i=1; i<=A[y][0] ; ++i)
        A[x][i] = A[y][i];
    for(int i=1; i<=A[x][0] ; ++i)
        A[y][i] = v[i];
    int aux;
    aux = A[x][0];
    A[x][0] = A[y][0];
    A[y][0] = aux;
}
void Solve()
{
    int i, j;
    for( i=1; i<Nr-1 ; ++i)
        for( j=i+1; j<Nr ; ++j)
            if( !Verifica(i,j) )
                Change(i,j);
    for(int i=1; i<Nr ; ++i)
    {
        for(int j=1; j<=A[i][0]; ++j)
            fout << A[i][j];
        //fout << '\n';
    }
}
int main()
{
    Read();
    Solve();
}
