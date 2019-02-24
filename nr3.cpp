#include <fstream>
#include <cstring>
using namespace std;
ifstream in("nr3.in");
ofstream out("nr3.out");
char s[1003];
int v[1000],c,i;
void nrmaxim()
{
    int d;
    d=c;
    for(i=0;i<strlen(s)-2;i++)
    {
        if(d>v[i])
        {
            out<<d<<v[i];
            d=-1;
        }
        else
            out<<v[i];
    }
    if(d!=-1)
        out<<d;
    out<<'\n';
}
void nrminim()
{
    if(c!=0)
        for(i=0;i<strlen(s)-2;i++)
        {
            if(c<v[i])
            {
                out<<c<<v[i];
                c=10;
            }
            else
                out<<v[i];
        }
    else
    {
        out<<v[0]<<c;
        for(i=1;i<strlen(s)-2;i++)
            out<<v[i];
        c=10;
    }
    if(c!=10)
        out<<c;
    out<<'\n';
}
int main()
{
    in.get(s,sizeof(s));
    for(i=0;i<strlen(s)-2;i++)
        v[i]=s[i]-48;
    c=s[strlen(s)-1]-48;
    nrmaxim();
    nrminim();
    return 0;
}
