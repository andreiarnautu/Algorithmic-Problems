#include <bits/stdc++.h>
const int MAX_N = 61;
const int MAX_L = 11;
const int INF = 1e9;
using namespace std;

ifstream fin("miting.in");
ofstream fout("miting.out");

int task, n, m;
char s[MAX_L], a[MAX_N][MAX_N];
int costmin[MAX_L][MAX_L][MAX_N][MAX_N], lin[MAX_L], col[MAX_L], sol=INF;

struct Cost
{
    int x;
    int y;
    int cost;

    bool operator < (const Cost &other) const {
        return this->cost > other.cost;
    }

    Cost operator + (const Cost &other) const {
        return Cost {
            this->x+other.x,
            this->y+other.y,
            this->cost+other.cost,
        };
    }
};

Cost dif[]={
    {-1, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {0, -1, 1},
};

void optimize(int st, int dr)
{
    int i, j, dir;
    priority_queue<Cost > pq;

    //  Baga elementele initiale
    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
          if(a[i][j] != '#')
            pq.push(Cost{i, j, costmin[st][dr][i][j]});

    while(!pq.empty()) {
        Cost c = pq.top(); pq.pop();

        for(dir = 0; dir < 4; dir++) {
            Cost vecin = c + dif[dir];

            if(vecin.x >= 1 && vecin.x <= n && vecin.y >= 1 && vecin.y <= m && a[vecin.x][vecin.y] != '#')
                if(vecin.cost < costmin[st][dr][vecin.x][vecin.y]) {
                    costmin[st][dr][vecin.x][vecin.y] = vecin.cost;
                    pq.push(vecin);
                }
        }
    }
}
int main()
{
    int i, j, linmin, colmin, linmax, colmax, k, lungime, delta, st, dr, x, y;
    linmin=colmin=MAX_N;
    linmax=colmax=-1;
    fin>>task;
    fin>>n>>m;
    fin.get();
    fin>>(s+1);
    lungime=strlen(s+1);
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++) {
            fin>>a[i][j];
            if(a[i][j]>='A' && a[i][j]<='Z') {
                if(i<linmin)
                    linmin=i;
                if(i>linmax)
                    linmax=i;
                if(j<colmin)
                    colmin=j;
                if(j>colmax)
                    colmax=j;
                for(k=1; k<=lungime; k++)
                    if(s[k]==a[i][j]) {
                        lin[k]=i;
                        col[k]=j;
                        break;
                    }
            }
        }
    if(task==1) {
        fout<<(linmax-linmin+1)*(colmax-colmin+1)<<'\n';
        return 0;
    }
    //  Initializam cu inf
    for(st = 0; st < MAX_L; st++)
        for(dr = 0; dr < MAX_L; dr++)
            for(i = 0; i < MAX_N; i++)
                for(j = 0; j < MAX_N; j++)
                  costmin[st][dr][i][j]=INF;


    for(k = 1; k <= lungime; k++) {
        costmin[k][k][lin[k]][col[k]] = 0;
        optimize(k, k);
    }

    //  Vezi ca aici te complicai inutil cu delta cum faceai tu. Am afisat pentru ce (st,dr) ajungeai sa rulezi si nu ajungea niciodata in cazul (1, lungime).
    //  E mult mai simplu asa.
    for(delta = 1; delta < lungime; delta++)
        for(st = 1; st + delta <= lungime; st++) {
            dr = st + delta;

            for(x = 1; x <= n; x++)
                for(y = 1; y <= m; y++)
                  for(k = st; k < dr; k++)
                    costmin[st][dr][x][y] = min(costmin[st][dr][x][y], costmin[st][k][x][y]+costmin[k+1][dr][x][y]);

            optimize(st, dr);
        }

    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
          sol = min(sol, costmin[1][lungime][i][j]);

    fout << sol << '\n';
    return 0;
}
