#include <fstream>
using namespace std;
ifstream in("creioane.in");
ofstream out("creioane.out");
long n,v1[9000],v2[9000],h[9000],maxim;
int main()
{
    int i,ok=1;

    in>>n;
    for(i=1;i<=n;i++)
        in>>v1[i]>>v2[i];
    h[0]=1;
    while(ok)
    {
        ok=0;
        for(i=1;i<=n;i++)
            if(h[i]!=h[v1[i]]+1)
            {
                ok=1;
                h[i]=h[v1[i]]+1;
            }
    }
    //out<<h[5]<<" "<<h[5]<<" "<<h[5];
 //   out<<endl;
    for(i=1;i<=n;i++)
        if(maxim<h[i])
            maxim=h[i];
    out<<maxim-1;
    return 0;
}
