#include <fstream>
using namespace std;
ifstream in("expresie.in");
ofstream out("expresie.out");
int n;
long long v[10001];
long long s,smax,suma;
int main()
{
    long long i,j;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>v[i];
        suma+=v[i];
    }
    for(i=1;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            s=suma-v[i]-v[i+1];
            if(j==i+1)
            {
                s-=v[i+2];
                s+=v[i]*v[i+1]*v[i+2];
            }
            else
            {
                s=s-v[j]-v[j+1];
                s+=v[i]*v[i+1]+v[j]*v[j+1];
            }
            if(s>smax)
            {
                smax=s;
                //out<<i<<" "<<j;
            }
        }
    out<<smax;
    return 0;
}
