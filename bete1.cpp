#include <fstream>
using namespace std;
ifstream in("bete1.in");
ofstream out("bete1.out");

int a[1000],b[1000];

void citire(int n)
{
    for(int i=0;i<n;i++)
        in>>a[i];
    for(int i=0;i<n;i++)
        in>>b[i];
}

void cerinta1(int n)
{
    int i,s=0;
    for(i=0;i<n;i++)
        s+=a[i]+b[i];
    out<<s/n<<endl;
}

void cerinta2si3(int n)
{
    int i,maxim1=0,maxim2=0,nr1=0,nr2=0;
    for(i=0;i<n;i++)
        if(a[i]>maxim1)
            maxim1=a[i];
    for(i=0;i<n;i++)
        if(b[i]>maxim2)
            maxim2=b[i];
    out<<maxim1+maxim2<<endl;
    for(i=0;i<n;i++)
    {
        if(a[i]==maxim1)
            ++nr1;
        if(b[i]==maxim2)
            ++nr2;
    }
    if(nr1<nr2)
        out<<nr1;
    else
        out<<nr2;
}

int main()
{
    int n;
    in>>n;
    citire(n);
    cerinta1(n);
    cerinta2si3(n);
    return 0;
}
