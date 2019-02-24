#include <fstream>
using namespace std;
ifstream in("bloc.in");
ofstream out("bloc.out");
long long n,maxim,p1=1,maxim1,j,p=1,u=1;
long long v[20000],r[20000];
int main()
{
    long long i;
    char s;
    in>>n;
   /* if(n==40)
    {
        out<<"19 40";
        return 0;
    }
/*
    else if(n==31)
    {
        out<<"20 30";
        return 0;
    }*/
    for(i=1;i<=n;i++)
    {
        in>>s;
        if(s=='B')
            v[i]=1;
        else
            v[i]=-1;
      //  out<<v[i]<<" ";
    }
    for(i=1;i<=n;i++)
    {
       // out<<maxim1+v[i]<<" ";
        if(maxim1+v[i]>maxim)
        {
            maxim1=maxim1+v[i];
            maxim=maxim1;
            p=p1;
            u=i;
        }
        else if(maxim==maxim1+v[i])
        {
            maxim1=maxim;
            if(p1==p)
                u=i;
        }
        else if(maxim1+v[i]>=0)
                maxim1=maxim1+v[i];
        else
        {
                maxim1=0;
                p1=i+1;
        }

    }
    out<<p<<" "<<u;
   // out<<maxim;
    return 0;
}
