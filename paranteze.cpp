#include <fstream>
using namespace std;
ifstream in("paranteze.in");
ofstream out("paranteze.out");
int v[500],n0=0,n1=0,n2=0,n3=0;
int verifica(int l)
{
    int i;
    n0=0;n1=0; n2=0; n3=0;
    for(i=0;i<l;i++)
    {
        in>>v[i];
        if(v[i]==0)
            ++n0;
        else if(v[i]==1)
            ++n1;
        else if(v[i]==2)
            ++n2;
        else if(v[i]==3)
            ++n3;
    }
    //out<<n0<<" "<<n1<<" "<<n2<<" "<<n3<<endl;
    if(n0!=n1)
        return 0;
    if(n2!=n3)
        return 0;
    n0=0; n1=0; n2=0; n3=0;
    for(i=0;i<l;i++)
    {
        if(v[i]==0 && v[i+1]==3)
            return 0;
        if(v[i]==2 && v[i+1]==1)
            return 0;
        if(v[i]==0)
            ++n0;
        else if(v[i]==1)
            ++n1;
        else if(v[i]==2)
            ++n2;
        else if(v[i]==3)
            ++n3;
        if(n0>0 && n1>0)
        {
            if(n0>=n1)
            {n0-=n1; n1=0;}
            else
            return 0;//n0=0;n1=n1-n0;}
        }
        if(n2>0 && n3>0)
        {
            if(n2>=n3)
            {n2-=n3; n3=0;}
            else
            return 0;//n3=n3-n2;}
        }
        if(n1>0 && n0==0)
            return 0;
        if(n3>0 && n2==0)
            return 0;
        if(n0<0 || n2<0)
            return 0;
        if(n0>0 && n3>0)
            {return 0;}
        if(n1>0 && n2>0)
            {return 0;}
    }
    return 1;
}

int main()
{
    int n,l,j;
    in>>n;
    for(int i=0;i<n;i++)
    {
        in>>l;
        out<<verifica(l);
        out<<endl;
    }
    return 0;
}
