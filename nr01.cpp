#include <fstream>
using namespace std;
ifstream in("nr01.in");
ofstream out("nr01.out");
long long n,nn;
int b,p;
short v[30];
void functie()
{
    bool g;
    int i,j;
    unsigned long long int s=0,putere=1;
    out<<"0"<<'\n';
    do
    {
        g=0;
        for(i=p;i>=0;i--)
            if(v[i]==0)
            {
                g=1;
                v[i]=1;
                break;
            }
        if(g)
        {
            for(j=p;j>i;j--)
                v[j]=0;
            s=0;
            putere=1;
            for(j=p;j>=0;j--)
            {
                if(v[j])
                    s+=putere;
                putere*=b;
            }
            if(s<=n)
                out<<s<<'\n';
        }
    }while(g);
}
int main()
{
    in>>n>>b;
    nn=n;
    while(n>=b)
    {
        n/=b;
        ++p;
    }
    n=nn;
    //out<<p;
    functie();
    return 0;
}
