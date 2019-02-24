#include <fstream>
#include <cstring>
using namespace std;
ifstream in("palc.in");
ofstream out("palc.out");
char s[500];
int main()
{
    int i,minim=11111,ok=1,k,j;
    in.get(s,sizeof(s));
    k=strlen(s);
    for(i=k;i<2*k;i++)
        s[i]=s[i-k];
   // out<<s;
    for(i=0;i<strlen(s);i++)
    {
        ok=1;
        for(j=i;j<k+i;j++)
            if(s[j]!=s[k+i-1-j+i])
            {
                ok=0;
                break;
            }
        if(ok==1)
        {
            //out<<i<<endl;
            if(i<minim && k-i>i)
                minim=i;
            else if(k-i<=i && k-i<minim)
                minim=k-i;
        }
    }
    if(minim!=11111)
        out<<minim;
    else
        out<<"-1";
    return 0;
}
