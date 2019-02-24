// Arnautu Andrei-100p
// La fiecare pas se calculeaza numarul de albine ce se afla in afara stupului in functie de coordonatele primei albine
#include <fstream>
#include <cmath>
using namespace std;
ifstream in("albine2.in");
ofstream out("albine2.out");
int m,n,a[101][101],x=1,y=1,d;
long long s;
int minim(int q, int t)
{
    if(q<=t)
        return q;
    return t;
}
int main()
{
    in>>n>>m;
    for(int i=0;i<m;i++)
    {
        in>>d;
        // In functie de directie, se modifica coordonatele primei albine
        if(d==0)
            --x;
        else if(d==1)
            ++y;
        else if(d==2)
            ++x;
        else if(d==3)
            --y;
        s+=minim(abs((double)1-x),n)*n;// Se aduna numarul de linii de albine ce se afla in afara stupului
        s+=minim(abs((double)1-y),n)*n;// Se adunca numarul de coloane de albine ce se afla in afara stupului
        s-=minim(abs((double)1-x),n)*minim(abs((double)1-y),n); // Se scade intersectia coloanelor gasite cu liniile gasite
    }
    out<<s; //Se afiseaza numarul total
    return 0;
}
