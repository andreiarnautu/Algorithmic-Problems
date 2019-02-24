//Sofia Vitelaru - 100 puncte
#include <fstream>
using namespace std;
ifstream f("arrows.in");
ofstream g("arrows.out");
int t[502][502],n,m,i,j,nr,x,y,  dx[]={0,0,-1,0,1},dy[]={0,1,0,-1,0},tk,val,l,c,Max,nr1,tip;
bool ciclu[501][501];
char a[501][501];
int main()
{
  f>>tip>>n>>m;
  for(i=1;i<=n;i++){
    for(j=1;j<=m;j++){
        f>>x;
        a[i][j]=x;
    }
  }
  int mx=n*m*1000;
  for(i=0;i<=m+1;i++)
     t[0][i]=t[n+1][i]=-1;
  for(i=0;i<=n+1;i++)
    t[i][0]=t[i][m+1]=-1;
  for(i=1;i<=n;i++)
     for(j=1;j<=m;j++)
      if(t[i][j]==0){    //daca punctul nu a fost atins
         nr=mx;x=i;y=j;
         while(t[x][y]==0&&t[x][y]!=-1){    //incerc sa determin un ciclu
             nr++;
             t[x][y]=nr;
             int k=a[x][y];
             x=x+dx[k];
             y=y+dy[k];
         }
         if(t[x][y]!=-1){         // am gasit un ciclu
            if(t[x][y]>mx){
                    nr=nr-mx;
                tk=tk+nr;
             int l=x, c=y;nr1=t[x][y]-mx;
             int val=(nr-nr1+1)*1000;
             if(val>Max)
                Max=val;
             do{
                 t[x][y]=val;ciclu[x][y]=1;
                 int k=a[x][y];
                  x=x+dx[k];
                   y=y+dy[k];
              }while(!(l==x&&c==y));

              if(!(x==i&&y==j)){
                 val=t[l][c];
                 nr=nr1-1;
                 l=i;c=j;
                 if(nr*1000+val>Max)
                    Max=nr*1000+val;
                 while(!(l==x&&c==y)){
                        t[l][c]=nr*1000+val;ciclu[l][c]=1;
                       nr--;
                      int k=a[l][c];
                      l=l+dx[k];
                      c=c+dy[k];
                 }
               }
             }
         else
         if(ciclu[x][y]==1){    //am ajuns intr-un punct ce face parte dintr-un ciclu det anterior
             tk=tk+nr-mx;
               val=t[x][y];
                 nr=nr-mx;
                 l=i;c=j;
                 if(nr*1000+val>Max)
                    Max=nr*1000+val;
                 while(!(l==x&&c==y)){
                        t[l][c]=nr*1000+val;ciclu[l][c]=1;
                       nr--;
                      int k=a[l][c];
                      l=l+dx[k];
                      c=c+dy[k];
                 }
             }
        else
             {
                 val=t[x][y];
                 nr=nr-mx;
                  l=i;c=j;
                  if(nr+val>Max)
                    Max=nr+val;
                 while(!(l==x&&c==y)){
                        t[l][c]=nr+val;
                         nr--;
                      int k=a[l][c];
                      l=l+dx[k];
                      c=c+dy[k];
                 }
             }
            }
        else
        {
        l=i;c=j;nr=nr-mx;
         while(t[l][c]!=-1){
            t[l][c]=nr--;
            int k=a[l][c];
                l=l+dx[k];
                c=c+dy[k];

         }
         if(t[i][j]>Max)
             Max=t[i][j];
        }
         }
f>>x>>y;
if(tip==1){
    g<<t[x][y]<<'\n';
    return 0;
}
if(tip==2){
        g<<tk<<'\n';
        return 0;
}
g<<Max<<'\n';
    return 0;
}
