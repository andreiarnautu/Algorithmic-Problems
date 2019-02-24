#include <iostream>
#include <cmath>
using namespace std;
long long nb_pairs(long long n){
    long long pow,prod=1,i,capat;
    //pastreaza valoarea initiala a lui n pentru a mentine constant
    //capatul sirului numerelor de testat
    for(i=2;i*i<=n;i++){  /// Aici e mai bine sa mergi pana la i*i <= n, fiindca tu pe n il mai scazi pe parcurs.
        pow=0;//puterea initiala a divizorului
        //daca exista un divizor, determina care este puterea lui
        while(n%i==0){
            pow++;
            n=n/i;
        }
        //daca este ex exponent nenul, inmulteste=l la produs
        if(pow!=0){
            prod*=(2*pow+1);
        }
    }
    //returneaza numarul de perechi
    if(n != 1) { /// Grija la cazul in care n este prim!!
        prod *= 3;
    }
    return prod;
}
int main(){
    int n,i,k;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>k;
        cout<<nb_pairs(k)<<" ";
    }

    return 0;
}
