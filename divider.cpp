#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
ifstream in("divider.in");
ofstream out("divider.out");
int a,b,n;
long long i,v[10000],j,k;
int main()
{
    in>>a>>b>>n;
    if(a!=b)
        for(i=0;i<=n;i++)
            for(j=0;j<=n;j++)
            {
                v[k]=pow(double(a),double(i))*pow(double(b),double(j));
                ++k;
            }
    else
        for(i=0;i<=2*n;i++)
        {
            v[k]=pow(double(a),double(i));
            ++k;
        }
    sort(v,v+k);
    for(i=0;i<k;i++)
        out<<v[i]<<" ";
    return 0;
}
