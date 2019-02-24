#include <fstream>
using namespace std;
ifstream cin("matrixdel.in");
ofstream cout("matrixdel.out");
int v[105][105],marcatlinie[105],marcatcoloana[105];
int main()
{
    int l,c,i,j,P,Q,x,y;
    cin>>l>>c;
    for(i=1;i<=l;i++)
    {
        for(j=1;j<=c;j++)
        {
            cin>>v[i][j];
        }
    }
    cin>>P;
    for(i=1;i<=P;i++)
    {
        cin>>x;
        marcatlinie[x]=1;
    }
    cin>>Q;
    for(i=1;i<=Q;i++)
    {
        cin>>y;
        marcatcoloana[y]=1;
    }
    for(i=1;i<=l;i++)
    {
        if(marcatlinie[i]!=1)
        {
            for(j=1;j<=c;j++)
            {
                if(marcatcoloana[j]!=1)
                {
                    cout<<v[i][j]<<" ";
                }
            }
            cout<<'\n';
        }
    }

    return 0;
}
