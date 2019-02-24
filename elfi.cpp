#include <fstream>
using namespace std;
ifstream in("elfi.in");
ofstream out("elfi.out");
int v[14400],n;
void restul()
{
    int i,x1,x2,nr,j,lmax=0,k;
    for(i=1;i<=n;i++)
    {
        in>>x1>>x2;
        nr=x1*2+x2;
        k=0;
        for(j=nr;j+k<=14400;j+=nr)
        {
            ++v[j+k];
            if(v[j+k]>lmax)
                {lmax=v[j+k];}
            ++k;
        }
    }
    out<<lmax;
}
int main()
{
    in>>n;
    restul();
    return 0;
}
