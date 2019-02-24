#include <fstream>
using namespace std;
ifstream in("flori.in");
ofstream out("flori.out");
short m[151][10];
int v[10],n,k,f[151];
void main_body()
{
    int i,j,l;
    bool ok=0,g;
    do
    {
        ok=0;
        for(i=0;i<n;i++)
        {
            if(f[i])
                continue;
            //out<<i+1<<" ";
            ok=1;
            f[i]=1;
            for(j=0;j<10;j++)
                v[j]=m[i][j];
            for(j=i+1;j<n;j++)
            {
                g=0;
                for(l=0;l<10;l++)
                    if(v[l] && m[j][l])
                    {
                        g=1;
                        break;
                    }
                if(g && !f[j])
                {
                    f[j]=1;
                    out<<j+1<<" ";
                    for(l=0;l<10;l++)
                        v[l]+=m[j][l];
                }
            }
            out<<'\n';
        }
    }while(ok);
}
int main()
{
    int i,j,x;
    in>>n>>k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<k;j++)
        {
            in>>x;
            if(m[i][x]==0)
                m[i][x]=1;
        }
    }
    main_body();
    return 0;
}
