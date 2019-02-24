// Mai exista si varianta next_permutation din STL
#include <fstream>
using namespace std;
ifstream in("permutari.in");
ofstream out("permutari.out");
int a[10000];
void gen_permutari(int n,int k)
{
    int x,i,g;
    if(k>n)
    {
        for(i=1;i<=n;i++)
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
                gen_permutari(n,k+1);
            }
        }
    }
}
int main()
{
    int n,i;
    in>>n;
    for(i=1;i<=n;i++)
        in>>a[i];
    gen_permutari(n,1);
    return 0;
}
