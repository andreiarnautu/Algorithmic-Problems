#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("cladiri2.in");
ofstream out("cladiri2.out");
int n,v[9];
long x;
void cerinte()
{
    int i,j,k,hmax=0,nr,c2=0,ok,c3=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<10;j++)
            v[j]=0;
        in>>x;
        k=0;
        ok=1;
        while(x)
        {
            v[k]=x%10;
            x=x/10;
            if(v[k]==hmax && ok)
             {
                nr++;
               // out<<i<<" ";
                ok=0;
             }
            else if(v[k]>hmax)
            {
                nr=1;
                hmax=v[k];
                ok=0;
            }
            ++k;
        }
        ok=1;
        for(j=0;j<k;j++)
            if(v[j]!=v[k-j-1])
            {
                ok=0;
                break;
            }
        if(ok==1)
            ++c2;
        else
        {
            for(j=0;j<k;j++)
            {
                if(v[j]!=v[k-j-1])
                {
                    c3+=abs(v[j]-v[k-j-1]);
                    //out<<abs(v[j]-v[k-j-1])<<" ";
                    v[j]=v[k-j-1];
                }
            }
        }
    }
    out<<hmax<<" "<<nr<<endl<<c2<<endl<<c3;
}
int main()
{
    in>>n;
    cerinte();
    return 0;
}
