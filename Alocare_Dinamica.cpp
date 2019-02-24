// Alocarea dinamica a listei de adiacenta a unui graf
#include <vector>
#include <cstdio>
using namespace std;
FILE *fin=freopen("alocare.in","r",stdin);
FILE *fout=freopen("alocare.out","w",stdout);
struct {vector<int>v;} a[100];
int n,viz[100],C[100];
void DFS(int x)
{
    printf("%d ",x);
    viz[x]=1;
    for(int i=0;i<a[x].v.size();i++)
        if(!viz[a[x].v[i]])
            DFS(a[x].v[i]);
}
void BFS(int x)
{
    int p,u;
    printf("%d ",x);
    viz[x]=1;
    C[0]=x;
    p=u=0;
    while(p<=u)
    {
        x=C[p++];
        for(int i=0;i<a[x].v.size();i++)
            if(!viz[a[x].v[i]])
            {
                printf("%d ",a[x].v[i]);
                viz[a[x].v[i]]=1;
                C[++u]=a[x].v[i];
            }
    }
}
int main()
{
    int x,y;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        a[x].v.push_back(y);
        a[y].v.push_back(x);
    }
  /*  for(int i=1;i<=6;i++)
    {
        for(int j=0;j<a[i].v.size();j++)
            printf("%d ",a[i].v[j]);
        printf("\n");
    }*/
    BFS(3);
    return 0;
}
