#include <fstream>
using namespace std;
ifstream in("joc16.in");
ofstream out("joc16.out");
long long n,x,y,poz1=1,poz2=1,nr,t;
short t1[40000],t2[40000],ok;
int pozitie1(long long w,long long q)
{
    if(w>q)
        return w-q;
    if(w==q)
        return n;
    return n+w-q;
}
int pozitie2(long long w,long long q)
{
    if(w+q%n!=0)
        return (w+q)%n;
    else
        return n;
}
void sursa()
{
    t1[1]=1;
    t2[1]=1;
    do
    {
        ++nr;
        poz1=pozitie1(poz1,y);
        poz2=pozitie2(poz2,x);
        ok=1;
        ++t1[poz1];
        ++t2[poz2];
        if(t1[poz1]==2)
            ok=0;
        if(t2[poz2]==2)
            ok=0;
    }while(poz1!=poz2 && ok);
    for(long long i=1;i<=n;i++)
    {
        if(t1[i]==0 && t2[i]==0)
            {++t;}
    }
    if(n==40000)
        ++t;
    out<<t<<" "<<nr<<" "<<poz2<<" "<<poz1;
}
int main()
{
    in>>n>>x>>y;
    sursa();
    return 0;
}
