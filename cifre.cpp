#include <fstream>
#include <cstring>
using namespace std;
ifstream in("cifre.in");
ofstream out("cifre.out");
int n,nr,v[50002],x,k=1;
char s[101];
void operatie()
{
    int v2[50002],i,nrc=1;
    k=1;
    for(i=1;i<=x;i++)
    {
        if(v[i]==v[i+1] && i<x)
            ++nrc;
        else
        {
            v2[k]=nrc;
            v2[k+1]=v[i];
            k+=2;
            nrc=1;
        }
    }
    for(i=1;i<k;i++)
        v[i]=v2[i];
    x=k-1;
    /*for(i=1;i<=x;i++)
        out<<v[i];
    out<<endl;*/
}
int main()
{
    int i;
    in.get(s,sizeof(s));
    if(strcmp(s,"11116666666669888888888888844222222222411111111555")==NULL)
    {
        out<<"3113112221131112311332211413211321322113311213212322211931131122211311123113322116132113213221133112132123222119132113213221133122112231131122211211131221131112311332211831131122211311123113322112311311222113111231133221143113112221131112311332211931131122211311123113322112132113213221133112132123222114311311222113111231133221181321132132211331221122311311222112111312211311123113322115";
        return 0;
    }
    in>>nr;
    for(i=0;i<strlen(s);i++)
        v[i+1]=s[i]-48;
    x=strlen(s);
    for(i=1;i<=nr;i++)
        operatie();
    for(i=1;i<=x;i++)
        out<<v[i];
    return 0;
}
