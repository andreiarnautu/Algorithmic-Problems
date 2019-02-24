#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("film.in");
ofstream out("film.out");
int b,i,f,k,g;
int main()
{
    in>>f>>b;
    k=abs(f-b);
    if(f>b)
        g=1;
    if(k==0)
        for(i=1;i<=b;i++)
            out<<"bf";
    else
    {
        if(g)
        {
            for(i=1;i<=k;i++)
                out<<"fbf";
            for(i=1;i<=b-k;i++)
                out<<"bf";
        }
        else
        {
            for(i=1;i<=k;i++)
                out<<"bfb";
            for(i=1;i<=f-k;i++)
                out<<"fb";
        }
    }
    return 0;
}
