#include <fstream>
using namespace std;
ifstream in("palindrom.in");
ofstream out("palindrom.out");
int n,v[10001],l[10],c,a,ok=0;
int main()
{
    int j,i,maxim=0;
    in>>n;
    for(i=0;i<n;i++)
    {
        in>>v[i];
        ++l[v[i]];
    }
    for(i=9;i>=0;i--)
    {
        if(l[i]%2==1 && l[i]>a)
        {
            a=l[i];
            c=i;
        }
    }
    for(i=1;i<=9;i++)
        if(l[i]>maxim)
            maxim=l[i];
    if(maxim<2)
    {
        for(i=9;i>0;i--)
            if(l[i])
            {
                out<<i;
                break;
            }
        return 0;
    }
    for(i=9;i>=0;i--)
        if(l[i]%2==0 || (l[i]%2==1 && c==i))
            for(j=0;j<l[i]/2;j++)
                out<<i;
    out<<c;
    for(i=0;i<10;i++)
        if(l[i]%2==0 || (l[i]%2==1 && c==i))
            for(j=0;j<l[i]/2;j++)
                out<<i;
    return 0;
}
