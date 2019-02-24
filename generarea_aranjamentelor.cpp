#include <fstream>
using namespace std;
ifstream in("aranjamente.in");
ofstream out("aranjamente.out");
int a[10000];
void gen_aranjamente(int n, int p, int k)
{
    int x,i,g;
    if(k>p)
    {
        for(i=1;i<=p;i++)
            out<<a[i]<<" ";
        out<<'\n';
    }
    else
    {
        for(x=1;x<=n;x++)
        {
            g=0;
            for(i=1;i<=k-1;i++)
                if(a[i]==x)
                {
                    g=1;
                    break;
                }


            if(!g)
            {
                a[k]=x;
                gen_aranjamente(n,p,k+1);
            }
        }
    }
}
int main()
{
    int n,p,i;
    in>>n>>p;
    for(i=1;i<=n;i++)
        in>>a[i];
    gen_aranjamente(n,p,1);
}
