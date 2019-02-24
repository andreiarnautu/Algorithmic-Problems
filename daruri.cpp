#include <fstream>
using namespace std;
ifstream in("daruri.in");
ofstream out("daruri.out");
int t,l;
int main()
{
    int r,tt,ll;
    in>>t>>l;
    tt=t;
    ll=l;
    r=t%l;
    while(r)
    {
        t=l;
        l=r;
        r=t%l;
    }
    if(l<2)
    {
        out<<"0"<<'\n'<<"0 0";
    }
    else
    {
        out<<l<<'\n';
        out<<tt/l<<" "<<ll/l;
    }
    return 0;
}
