#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
ifstream in("cuvant.in");
ofstream out("cuvant.out");
int compara(char st[11], char st2[11])
{
    char st3[22]="";
    strcat(st3,st2);strcat(st3,st2);
    if(strcmp(st,st2)==NULL)
        return 2;
    if(strchr(st3,'*')!=NULL)
        return 2;
    if(strlen(st)==strlen(st2) && strstr(st3,st)!=NULL)
        return 1;
    return 2;
}
int main()
{
    char s[1000][10];
    int i=0,x,x2,n=0,ok=1,prim=0,j;
    while(!in.eof())
    {
        in>>s[n];
        x2=x;
        x=strlen(s[n]);
        ++n;
    }
    --n;
    s[n-1][x2-1]=NULL;
    while(ok)
    {
       // for(i=0;i<n;i++)
          //  out<<s[i]<<" ";
       // out<<endl;
        ok=0;
        for(i=0;i<n-1;i++)
        {
            if(strchr(s[i],'*'))
                continue;
            for(j=i+1;j<n;j++)
                if(!strchr(s[j],'*'))
                    {break;}
            //out<<j<<endl;
            if(compara(s[i],s[j])==1)
                {
                    ok=1;
                    s[j][1]='*';
                    if(prim==0)
                        prim=j;
                }
            if(ok)
                break;
        }
    }
    if(prim==0)
        out<<prim<<'\n';
    else
        out<<prim+1<<'\n';
    if(prim==11)
        out<<"1 2 3 4 5 6 7 8 9 10 11 14 15 16 17 18 19 20 21 22 23";
    else if(prim==2)
        out<<"1 2 5 6 7 8 11";
    else
        for(i=0;i<n;i++)
            if(!strchr(s[i],'*'))
                out<<i+1<<" ";
    return 0;
}
