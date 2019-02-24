#include <fstream>
using namespace std;
ifstream in("interviu.in");
ofstream out("interviu.out");
int n,x,maxim;
int main()
{
    int i;
    bool ok=0;
    in>>n;
    for(i=0;i<3;i++)
    {
        in>>x;
        if(x>maxim)
            maxim=x;
    }
    for(i=3;i<n;i++)
    {
        in>>x;
        if(x>maxim)
        {
            out<<i+1;
            ok=1;
            break;
        }
    }
    if(!ok)
        out<<n;
}
