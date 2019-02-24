#include <fstream>
using namespace std;
ifstream in("consiliu.in");
ofstream out("consiliu.out");
int n,x,y,z,t,h1,h2,k,i,v[1440],j;
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>x>>y>>z>>t;
      //  out<<x<<y<<z<<t<<endl;
        h1=x*60+y;
        h2=z*60+t;
        if(h2<=h1)
            h2+=60*24;
       // out<<h1<<" "<<h2<<" ";
        for(j=h1;j<h2;j++)
        {
            if(j>=1440)
                ++v[j-1440];
            else
                ++v[j];
        }
    }
    for(i=0;i<=1440;i++)
        if(v[i]==n)
            ++k;
    out<<k;
    return 0;
}
