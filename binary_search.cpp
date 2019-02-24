#include <iostream>
using namespace std;
int n, v[100], x;
void cauta(int a, int b)
{
    int m;
    m=(a+b)/2;
    if(v[m]==x)
        cout<<"Gasit pe pozitia "<<m+1<<endl;
    else if(a<b)
    {
        if(x<v[m])
            cauta(a,m);
        else
            cauta(m,b);
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>v[i];
    cin>>x;
    cauta(0,n);
    return 0;
}
