#include <fstream>
using namespace std;
ifstream in("binremove.in");
ofstream out("binremove.out");
long long n,x;
short v[50002];
int p;
void verifica()
{
    long long i,rest=0;
    for(i=n-x-1;i<n-1;i++)
        v[i]=v[i+1];
    --n;
    for(i=n-1;i>=0;i--)
        if(v[i]==1)
        {
            if((n-1-i)%2==0)
                rest+=1;
            else
                rest+=2;
        }
    if(rest%3==0)
        out<<"1";
    else
        out<<"0";
    out<<'\n';
}
int main()
{
    long long i;
    in>>n;
    for(i=0;i<n;i++)
        in>>v[i];
    in>>p;
    for(i=0;i<p;i++)
    {
        in>>x;
        verifica();
    }
    return 0;
}
