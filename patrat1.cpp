//n^3
#include <fstream>
#include <iostream>
#define DIM 300
#define INF 1000000

using namespace std;

int di[] = {-1, 1,-1,1,0, 0,1,-1};
int dj[] = { 1,-1,-1,1,1,-1,0, 0};

int a[DIM][DIM];
int n, m, i, j, k, maxim, stele, patrate, ok, d, iv, jv, t;

int main(){
    ifstream fin("patrat1.in");
    ofstream fout("patrat1.out");

    fin>>n>>m;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            fin>>a[i][j];

    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) {
            ok = 1;
            for (d=0;d<=7;d++) {
                iv = i + di[d];
                jv = j + dj[d];
                if (a[iv][jv] >= a[i][j])
                    ok = 0;
            }
            stele+=ok;
            if (ok == 1){
                a[i][j] = INF;
                //cout<<i<<" "<<j<<"\n";
            }
        }

    for (i=1;i<n;i++)
        for (j=i+1;j<=n;j++) {
            t = j-i;
            for (k=1; k+t<=m; k++)
                if (a[i][k] == INF && a[i][k+t] == INF && a[j][k] == INF && a[j][k+t] == INF) {
                    patrate++;
                    if (t > maxim)
                        maxim = t;
                }
        }

    fout<<stele<<"\n"<<patrate<<"\n"<<maxim+1;
    return 0;
}
