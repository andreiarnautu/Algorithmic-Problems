#include <fstream>
using namespace std;
ifstream in("alun.in");
ofstream out("alun.out");
int n1,n2,x,k,y;
void cerinta1()
{
    int nr=0;
    nr+=(x/4)*(n1+n2);
    if(x%4>=2)
        nr+=n1;
    nr-=x/k;
    out<<nr<<endl;
}

void cerinta2()
{
    int pert,drumuri=0,rest=0;
    pert=y/(n1+n2);
    drumuri+=pert*4;
    rest=y%(n1+n2);
    if(0<rest && rest<=n1)
        drumuri+=2;
    if(rest>n1)
        drumuri+=4;
    out<<drumuri;
}
int main()
{
    in>>n1>>n2>>x>>k>>y;
    cerinta1();
    cerinta2();
    return 0;
}
