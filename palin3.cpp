#include <fstream>
#include <cstring>
using namespace std;
ifstream in("palin3.in");
ofstream out("palin3.out");
int t,ok,l;
char s[100];
int verifica(int x)
{
    if(s[x+1]==s[x+2])
        return 1;
    return 0;
}
int main()
{
    int i,j;
    in>>t;
    in.get();
    for(i=1; i<=t; i++)
    {
        in.get(s,sizeof(s));
        in.get();
        if(strlen(s)%3!=0)
        {
            out<<"NU"<<'\n';
            continue;
        }
        ok=1;
        while(ok)
        {
            ok=0;
            for(j=0; j<=strlen(s)-3; j++)
            {
                if(s[j]==s[j+2])
                {
                    ok=1;
                    strcpy(s+j,s+j+3);
                    break;
                }
            }
        }
        //  out<<s<<endl;
        if(strlen(s)==0)
            out<<"DA"<<'\n';
        else if(strlen(s)==3 && s[0]==s[2])
            out<<"DA"<<'\n';
        else
            out<<"NU"<<'\n';
    }
    return 0;
}
