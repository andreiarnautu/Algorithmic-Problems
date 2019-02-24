#include <fstream>
using namespace std;
ifstream in("combinari.in");
ofstream out("combinari.out");
int a[10000];
void gen_combinari(int n, int p, int k)
{
    int x,i;
    if(k>p)
    {
        for(i=1;i<=p;i++)
            out<<a[i]<<" ";
        out<<'\n';
    }
    else
        for(x=a[k-1]+1;x<=n-p+k;++x)
        {
            a[k]=x;
            gen_combinari(n,p,k+1);
        }

}
int main()
{
    int n,p;
    in>>n>>p;
    for(int i=1;i<=n;i++)
        in>>a[i];
    gen_combinari(n,p,1);
    return 0;
}
