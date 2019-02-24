#include <fstream>
using namespace std;
ifstream in("patrate2.in");
ofstream out("patrate2.out");
int n,h;
long long maxim,c[1000],p[1000],v[10000],k=0,af1,af2,nrc;
int main()
{
    long long i,j,nr;
    in>>n>>h;
    for(i=1;i<=n;i++)
    {
        in>>c[i]>>p[i];
        if(c[i]+p[i]>maxim)
            maxim=c[i]+p[i];
    }
    for(i=1;i<=maxim;i++)
    {
        nr=0;
        for(j=1;j<=n;j++)
            if(c[j]<=i && c[j]+p[j]>i)
                ++nr;
      //  out<<nr<<endl;
        if(nr>=h)
        {
            v[k]=i;
            k++;
        }
    }
    nrc=1;
    af1=v[1];
    af2=1;
  //  out<<k<<endl;
    for(i=1;i<k;i++)
    {
        if(v[i]==v[i+1]-1)
            ++nrc;
        else
        {
            if(nrc>af2)
            {
                af2=nrc;
                af1=v[i]-nrc+1;
            }
            nrc=1;
        }
    }
    out<<af1<<" "<<af2;
    return 0;

}
