#include <fstream>
#include <cstring>
using namespace std;
ifstream in("mare.in");
ofstream out("mare.out");
int n;
char s[100][10],s2[900]="";
void palindrom(char str[900])
{
    int i,ok=1,m=0;
    for(i=0;i<strlen(str);i++)
        if(str[i]!=str[strlen(str)-1-i])
        {
            ok=0;
            break;
        }
    if(ok)
    {
        m=0;
        ok=1;
        if(strlen(str)<strlen(s2))
            ok=0;
        if(strlen(str)>strlen(s2))
            {ok=0;m=1;strcpy(s2,str);}
        if(strlen(str)==strlen(s2) && !m)
        {
            for(i=0;i<strlen(s2);i++)
                if(s2[i]>str[i])
                {
                    ok=0;
                    break;
                }
        }
        if(ok && !m)
            {;strcpy(s2,str);}
    }
}
void operatie(int x)
{
    char s3[900]="";
    int j;
    strcat(s3,s[x]);
    palindrom(s3);
    for(j=x+1;j<=n;j++)
    {
        strcat(s3,s[j]);
        palindrom(s3);
    }
}
int main()
{
    int i;
    in>>n;in.get();
    for(i=1;i<=n;i++)
        in>>s[i];
    for(i=1;i<=n;i++)
        operatie(i);
    out<<s2;
    return 0;
}
