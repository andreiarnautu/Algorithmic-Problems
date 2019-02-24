#include <fstream>
using namespace std;
ifstream in("morse.in");
ofstream out("morse.out");
int a,b,v[16],maxim;
void maximm()
{
    int i,j,nr=0;
    for(i=a;i<=b;i++)
    {
        nr=0;
        j=i;
        while(j)
        {
            if(j%2==1)
                ++nr;
            j=j/2;
        }
        if(nr>maxim)
            maxim=nr;
    }
}
void finalizare()
{
    int i,j,k,nr;
    for(i=a;i<=b;i++)
    {
        k=0;
        nr=0;
        for(j=0;j<16;j++)
            v[0]=0;
        j=i;
        while(j)
        {
            v[k]=j%2;
            j=j/2;
            if(v[k]==1)
                ++nr;
            k++;
        }
        if(nr==maxim)
        {   for(j=k-1;j>=0;j--)
                {
                    if(v[j]==1)
                        out<<"-";
                    else
                        out<<".";
                }
            out<<" ";
        }
    }
}

int main()
{
    in>>a>>b;
    maximm();
    finalizare();
    return 0;
}
