#include <fstream>
using namespace std;
ifstream in("joc13.in");
ofstream out("joc13.out");
int x,n;
long long nr,a,b,p1,p2;
short v[110];
bool ok=1;
void j1()
{
    in>>x;
    p1=(p1+x)%n;
    if(p1==p2)
    {
        if(p1==0)
        {
            ok=0;
            ++a;
            return;
        }
        p1=0;
        a=0;
        return;
    }
    if(p1==0 && a!=0)
    {
        a+=v[p1];
        ok=0;
        return;
    }
    if(v[p1]==0)
    {
        ++a;
        p1=0;
        a=0;
        return;
    }
    else if(v[p1]==1)
        a++;
    else if(v[p1]==10)
        a+=10;
    if(p1==0 && a!=0)
    {
        ++a;
        ok=0;
    }
}
void j2()
{
    in>>x;
    p2=(p2+x)%n;
    if(p1==p2)
    {
        if(p2==0)
           {
                ++b;
                ok=0;
                return;
           }
        p2=0;
        b=0;
        return;
    }
    if(p2==0 && b!=0)
    {
        b+=v[p2];
        ok=0;
        return;
    }
    if(v[p2]==0)
    {
        p2=0;
        b=0;
        return;
    }
    else if(v[p2]==1)
        b++;
    else if(v[p2]==10)
        b+=10;
}
int main()
{
    long long i;
    in>>n;
    for(i=0;i<n;i++)
        in>>v[i];
    in>>nr;
    for(i=1;i<=nr;i++)
    {
        if(i%2==1)
            j1();
        else
            j2();
        if(ok==0)
        {
            if(p1==0 && a!=0)
            {
                out<<"1"<<'\n';
                out<<p1+1<<" "<<a<<'\n';
                out<<p2+1<<" "<<b<<'\n';
                return 0;
            }
            else
            {
                out<<"2"<<'\n';
                out<<p1+1<<" "<<a<<'\n';
                out<<p2+1<<" "<<b<<'\n';
                return 0;
            }
        }
    }
    if(a>b)
    {
        out<<"1"<<'\n';
        out<<p1+1<<" "<<a<<'\n';
        out<<p2+1<<" "<<b<<'\n';
    }
    else if(b>a)
    {
        out<<"2"<<'\n';
        out<<p1+1<<" "<<a<<'\n';
        out<<p2+1<<" "<<b<<'\n';
    }
    else
    {
        if(p1>p2)
        {
                out<<"1"<<'\n';
                out<<p1+1<<" "<<a<<'\n';
                out<<p2+1<<" "<<b<<'\n';
        }
        else
        {
                out<<"2"<<'\n';
                out<<p1+1<<" "<<a<<'\n';
                out<<p2+1<<" "<<b<<'\n';
        }
    }
    return 0;
}
