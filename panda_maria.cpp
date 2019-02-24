/**
  *
  *             MARIA E UN PANDA!
  *
  */

#include<fstream>
#include<iostream>
#include<queue>
#include<climits>
#define x first
#define y second
using namespace std;

int Map[501][501],Coduri[501][501],Traseu[501][501];
int N,M,nr_tarcuri,S,cod_ursulet,i,j;
int tarcuri[250001][2];

int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};


queue < pair < int, int > > Q;

pair < int, int> start;

bool sunt_complementare (int a, int b){

        int k;
        k=(1<<S)-1; //2 la puterea S
        a=a&k; //ultimele x cifre ale lui a
        b=b&k; //ultimele x cifre ale lui b

        /*** Aici e schimbarea. Tu nu puneai a^b in paranteza. Ideea e ca daca scrii a^b==k e ca si cum ai zice a^(b==k) */
        if ((a^b)==k) return 1; //daca sunt complementare
        return 0;

}

bool ok (int i, int j){

    if (i>N || i<=0 || j>M || j<=0) return 0; //iese din matrice
    if (Traseu[i][j]!=0) return 0; //am trecut deja pe aici
    return 1;

}

int main (){
    int p,cod,x1,y1,x2,a,b,c,nr=0;
    ifstream f ("panda.in");
    ofstream g ("panda.out");
    f>>p>>N>>M;
    f>>nr_tarcuri;
    f>>start.x>>start.y;
    f>>cod_ursulet; //codul ursuletului
    f>>S;
    Q.push(start);
    for (i=1; i<=nr_tarcuri; i++){
       f>>x1>>x2;
        //Q.push(make_pair(x1,x2));
        tarcuri[i][1]=x1;
        tarcuri[i][2]=x2;
    }
    if (p==1)
    {
        //nu am nevoie sa retin intr-o matrice codurile tarcurilor

        for (i=1; i<=N; i++) {
            for (j=1; j<=M; j++)
            {
                f>>cod;
                //g << cod << " ";
                if (i!=start.x || j!=start.y)
                if (sunt_complementare(cod_ursulet,cod)==1) nr++;
            }
            //g << '\n';
        }
            g<<nr; return 0;
    }
    Traseu[start.x][start.y]=1;
    for (i=1; i<=N; i++)
    for (j=1; j<=M; j++)
    f>>Coduri[i][j];
    Map[start.x][start.y]=1;
    for (i=1; i<=N; i++)
        for (j=1; j<=M; j++)
    {
        if (i!=start.x || j!=start.y)
        {
        if (sunt_complementare(cod_ursulet,Coduri[i][j]) )
            Map[i][j]=1;
        //else Map[i][j]=0;
        }
    }
     while (!Q.empty()){

         x1=Q.front().x;
         y1=Q.front().y;
         Q.pop();
         for (int d=0; d<4; d++){
            if (ok(x1+dx[d],y1+dy[d])==1 && Map[x1+dx[d]][y1+dy[d]]==1)
            {
                Q.push(make_pair(x1+dx[d],y1+dy[d]));
                Traseu[x1+dx[d]][y1+dy[d]]=Traseu[x1][y1]+1;
            }
         }

     }
     int lmin,nt=1;
     lmin=INT_MAX;
    /* for (i=1; i<=N; i++)
        for (j=1; j<=M; j++)
     {
        cout<<Map[i][j]<<" ";
        if (j==M) cout<<'\n';
     }*/
     for (i=1; i<=nr_tarcuri; i++)
     {
         if (Traseu[tarcuri[i][1]][tarcuri[i][2]]<lmin && Traseu[tarcuri[i][1]][tarcuri[i][2]]!=0)
                {nt=1; lmin=Traseu[tarcuri[i][1]][tarcuri[i][2]];}
         else if (Traseu[tarcuri[i][1]][tarcuri[i][2]]==lmin && Traseu[tarcuri[i][1]][tarcuri[i][2]]!=0) nt++;
     }
    g<<lmin-1<<" "<<nt;
    return 0;
}
