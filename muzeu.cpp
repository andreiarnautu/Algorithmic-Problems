#include <fstream>
using namespace std;
ifstream in("muzeu.in");
ofstream out("muzeu.out");
int n,x,y,k;
int main()
{
    int ai,bi,i;
    in>>n>>x;
    k=x;
    for(i=0;i<n;i++)
    {
        in>>ai>>bi;
        if(bi>=y)
        {
            x=k-bi;
            y=bi;
        }
        else
        {
            if(y-bi<ai)
            {
                y=bi;
                x=k-y;
            }
            else
            {
                y-=ai;
                x=k-y;
            }
        }
    }
    out<<x;
    return 0;
}
