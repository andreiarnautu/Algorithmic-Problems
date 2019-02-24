#include <fstream>
using namespace std;
ifstream in("control1.in");
ofstream out("control1.out");
long long i,a,b,x;
short c;
int main()
{
    in>>a>>b>>c;
    for(i=a;i<=a+8;i++)
    {
        if(c!=9 && c==i%9)
        {
            x=i;
            break;
        }
        else if(c==9 && i%9==0)
        {
            x=i;
            break;
        }
        if(i==b)
            break;
    }
    if(x==0)
        out<<"0";
    else
        out<<(b-x)/9+1;
    return 0;
}
