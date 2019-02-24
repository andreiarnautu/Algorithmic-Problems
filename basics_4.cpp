// Divide et Impera -> cmmdc
#include <iostream>
using namespace std;
int a[50],n;
void citire()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
}
int euclid(int x, int y)
{
    int r;
    while(y)
    {
        r=x%y;
        x=y;
        y=r;
    }
    return x;
}
int cmmdc(int x, int y)
{
    if(y-x<2)
        return euclid(a[x],a[y]);
    int m;
    m=(x+y)/2;
    return euclid(cmmdc(x,m),cmmdc(m+1,y));
}
int main()
{
    citire();
    cout<<"Cmmdc="<<cmmdc(0,n-1)<<endl;
    return 0;
}
