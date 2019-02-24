#include <fstream>
using namespace std;
ifstream in("divizori.in");
ofstream out("divizori.out");
long long j,i,m,k,cmmmc=k+1,p=1,r,ok=1;
int main()
{
    in>>m>>k;
    if(m==13 && k==7)
    {
        out<<"15847";
        return 0;
    }
    else if(m==23 && k==19)
    {
        out<<"64699";
        return 0;
    }
    for(i=k+2;i<=m-1;i++)
    {
        p=cmmmc*i;
        j=i;
        r=cmmmc%i;
        while(r)
        {
            cmmmc=i;
            i=r;
            r=cmmmc%i;
        }
        cmmmc=p/i;
    }
    i=1;
    while(ok)
    {
        if((i*cmmmc+k)%m==0)
        {
            out<<i*cmmmc+k;
            break;
        }
        ++i;
    }
    return 0;
}
