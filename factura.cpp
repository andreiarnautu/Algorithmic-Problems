#include <fstream>
#include <cstring>
using namespace std;
ifstream in("factura.in");
ofstream out("factura.out");
int n,c;
char s[10];
void suma()
{
    int t1=0,t2=0,i,k;
    t1=600*(s[0]-48)+60*(s[1]-48)+10*(s[3]-48)+s[4]-48;
    t2=t1+(s[6]-48)*10+s[7]-48;
   // out<<t1<<" "<<t2<<endl;
    for(i=t1;i<t2;i++)
    {
        k=i;
        if(i>=24*60)
            k-=24*60;
        if(k>=7*60 && k<19*60)
            c+=10;
        else
            c+=5;
    }
   // out<<c<<endl;
}
int main()
{
    int i;
    in>>n;
    in.get();
    for(i=1;i<=n;i++)
    {
        in.get(s,sizeof(s));in.get();
        suma();
    }
    out<<c;
    return 0;
}
