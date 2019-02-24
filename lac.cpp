#include<fstream>
#include<queue>
#include<iostream>

#define x first
#define y second

using namespace std;

queue <pair < int , int > > Q;
int Map[1005][1005],n,m,i,j,dir,nrp,nri;
bool margine;

bool ok (int i, int j)
{
    if (i<1 || j<1 || i>n || j>m) return 0;
    return 1;
}

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

bool a[1005][1005]; //matricea care retine daca pozitia a mai fost in coada sau nu
// daca a[i][j] == 1 inseamna ca in Map[i][j] se afla valoarea 1 si nu i-au mai fost verificati vecinii pana acum

int q=2;

pair < int, int > start;
pair < int, int > v[1004004]; //vectorul va tine toate pozitiile datelor nenule din map

int main ()
{
    ifstream f ("lac.in");
    ofstream g ("lac.out");
    int vecini=0,k=1;
    f>>n>>m;
    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
        {
            f>>Map[i][j];
            if (Map[i][j]==1) {
                   if (Q.empty())  Q.push(make_pair(i,j));
                   a[i][j]=1;
                   v[k++]=make_pair(i,j);
            }
        }
        //cout<<k;
        // k-1 va fi nr de pozitii nenule din map
    while (!Q.empty())
    {
        //vecini=0;
        start.x=Q.front().x;
        start.y=Q.front().y;
        Q.pop();
        Map[start.x][start.y]=0; //ca sa nu o mai gaseasca a doua oara ca si vecin
        if (start.x==1 ||start.x==n || start.y==1 || start.y==m) margine=true;
        a[start.x][start.y]=0;
        for (dir=0; dir<4; dir++)
        {
           if (ok(start.x+dx[dir],start.y+dy[dir]) && Map[start.x+dx[dir]][start.y+dy[dir]]==1)
            {
                Q.push(make_pair(start.x+dx[dir],start.y+dy[dir]));
                a[start.x+dx[dir]][start.y+dy[dir]]=0;
                if (start.x+dx[dir]==1 ||start.x+dx[dir]==n || start.y+dy[dir]==1 || start.y+dy[dir]==m) margine=true;
                //vecini=1;
            }
        }

        if (Q.empty())
        {
            if (margine==false) nri++;
            else nrp++;

            margine=0;
            for (i=q; i<k; i++)
            {
              if (a[v[i].x][v[i].y]==1 ) {Q.push(v[i]); break;}
            }
              q=i+1;
        }
    }
    g<<nri<<" "<<nrp;
    return 0;

}
