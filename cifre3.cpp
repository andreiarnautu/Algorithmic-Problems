#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("cifre3.in");
ofstream out("cifre3.out");
int va[10],vb[10],v[20],k;

void cifre(int a,int b)
{
    while(a)
    {
        ++va[a%10];
        v[k]=a%10;
        ++k;
        a=a/10;
    }
    while(b)
    {
        ++vb[b%10];
        ++v[k]=b%10;
        ++k;
        b=b/10;
    }
    sort(v,v+k);
}

void cerinta1()
{
    int ok=0,i;
    for(i=0;i<10;i++)
    {
        if(vb[i]>0 && va[i]>0)
        {
            out<<i<<" ";
            ok=1;
        }
    }
   // if(ok==0)
     //   out<<"-1";
    out<<endl;
}

void cerinta2()
{
    for(int i=k-1;i>=0;i--)
        out<<v[i];
}
int main()
{
    int a,b;
    in>>a>>b;
    cifre(a,b);
    cerinta1();
    cerinta2();
    return 0;
}
