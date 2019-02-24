#include <fstream>
using namespace std;
ifstream in("anagramabil.in");
ofstream out("anagramabil.out");

int v1[10],cifre[10],v2[10];

int main()
{
    long n,nn;
    int k=0,ok,f=0,j,i;
    in>>n;
    nn=n;
    while(n)
    {
        ++v1[n%10];
        n=n/10;
    }
    n=nn;
    for(i=2;i<=9;i++)
    {
        //out<<i<<endl;
        ok=0;
        n=nn*i;
        //out<<"n egal cu "<<n<<endl;
        while(n)
        {
            v2[n%10]++;
            n=n/10;
        }
        //for(j=0;j<10;j++)
          //  out<<v2[j]<<" ";
        for(j=0;j<10;j++)
            if(v1[j]!=v2[j])
                {
                    ok=1;
            //        out<<v1[j]<<"*"<<v2[j]<<endl;
                }
        if(ok==0)
            {
                ++f;
            }
        //out<<"pt i="<<i<<" avem ok="<<ok<<endl;
        if(ok==0 && f==1)
            {
                out<<"DA"<<endl;
                out<<i;
            }
        else if(ok==0 && f!=1)
            out<<i;
        for(j=0;j<10;j++)
            v2[j]=0;

    }
    if(f==0)
        out<<"NU";
    return 0;
}
