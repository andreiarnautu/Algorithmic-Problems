#include <fstream>
using namespace std;
ifstream in("matriosca.in");
ofstream out("matriosca.out");
short n,i,m[2501][2501],nr[2501],j,l1,l2;
long long x,minim[2501],optim;
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>x;
        optim=2500;
        minim[2500]=1999999999;
        if(i!=1)
            for(l1=1;l1<=j;l1++)
            {
                if(x<minim[l1] && minim[l1]<minim[optim])
                    optim=l1;
                //out<<minim[l1]<<" ";
               // out<<endl;
            }

        if(optim==2500)
        {
            ++j;
            m[j][1]=i;
            minim[j]=x;
            nr[j]=1;
        }
        else
        {
            ++nr[optim];
            m[optim][nr[optim]]=i;
            minim[optim]=x;
        }
    }
    out<<j<<'\n';
    for(i=1;i<=j;i++)
    {
        out<<nr[i]<<" ";
        for(l1=1;l1<=nr[i];l1++)
            out<<m[i][l1]<<" ";
        out<<'\n';
    }
    return 0;
}
