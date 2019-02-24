#include <fstream>
using namespace std;
ifstream in("magicmatrix.in");
ofstream out("magicmatrix.out");
short t,g;
int n,k,ok;
long long m[500][500],v[501],s1,s=-1000000001,viz[501];
void permuta(long long top)
{
    long long i;
    s1=0;
    if(top==n+1 && g!=0)
    {
        for(i=1;i<=n;i++)
            s1+=m[i-1][v[i]-1];
        if(s==-1000000001)
            s=s1;
        else if(s!=s1)
        {
            g=0;
            //out<<"NO"<<'\n';
        }
        //out<<s1<<endl;
    }
    else if(g!=0)
        for(i=1;i<=n;i++)
            if(!viz[i])
            {
                viz[i]=1;
                v[top]=i;
                permuta(top+1);
                viz[i]=0;
            }
}
int main()
{
    //clock_t timpInitial, timpFinal ;
    int i,i1,i2;
    //timpInitial = clock() ;
    in>>t;
    for(i=1;i<=t;i++)
    {
        in>>n;
        s=-1000000001;
        g=1;
        for(i1=0;i1<n;i1++)
            for(i2=0;i2<n;i2++)
                in>>m[i1][i2];
        for(i1=1;i1<=500;i1++)
        {
            v[i1]=0;
            viz[i1]=0;
        }
        permuta(1);
        if(g==0)
            out<<"NO"<<'\n';
        else
            out<<"YES"<<'\n';
    }
   // timpFinal = clock() ;
   // out<< (double)(timpFinal - timpInitial)/ CLOCKS_PER_SEC ;
    return 0;
}
