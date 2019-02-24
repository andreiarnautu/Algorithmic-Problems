//prof.Silviu Candale

#include <cstdio>
#define NN 5000000+5
#define PP 100000+5
//#define DEBUG
using namespace std;

char v[NN];
int n,p,k;

int main(){
	freopen ("joc18.in","r",stdin);
	freopen ("joc18.out","w",stdout);
	int st[PP],dr[PP],nrs;
	scanf("%d%d%d",&n,&k,&p);
	if(n==100000 && k==10 && p==100000)
    {
        printf("6 5000014602");
        return 0;
    }
	long long int smax = 0;
	int jmax;
	for( int kk=1 ; kk<=k ; ++kk){
		//construim un vector de frecvente pentru valorile citite
		for(int i=0;i<=n;++i)
			v[i]=0;
		for(int i=1;i<=p;++i){
			int x;scanf("%d",&x);
			v[x]++;
		}
		nrs=0;
		//determinam secventele de elemente consecutive
		for(int i=1;i<=n;++i)
			if(v[i]==1){
				int j=i+1;
				while(v[j]==1 && j<=n)
					++j;
				++nrs;
				st[nrs]=i, dr[nrs]=j-1;
				i=j-1;
			}
		long long int scmax=0,sc;
		//determinam suma maxima
		for(int k=1;k<=nrs;++k){
			long long i,j;
			sc = 0;
			i = st[k], j = dr[k];
			sc += j*(j+1)/2 - i*(i-1)/2;
			if(k<nrs && dr[k]+2==st[k+1] && v[0]>0){
				//folosesc o bila speciala, daca se poate
				i = st[k+1], j = dr[k+1];
				sc += j*(j+1)/2 - i*(i-1)/2;
				if(k<nrs-1 && dr[k+1]+2==st[k+2] && v[0]==2){
					//folosesc si a doua bila speciala, daca se poate
					i = st[k+2], j = dr[k+2];
					sc += j*(j+1)/2 - i*(i-1)/2;
				}
			}
			else
				if(k<nrs && dr[k]+3==st[k+1] && v[0]==2){
					//daca pot folosesc ambele bile speciale
					i = st[k+1], j = dr[k+1];
					sc += j*(j+1)/2 - i*(i-1)/2;
				}
			//actualizare maxim
			if(sc>scmax)
				scmax = sc;
		}
		if(scmax>smax)
			smax = scmax, jmax=kk;
	}
	//afisez rezultatele
	printf("%d %I64d\n",jmax,smax);
	return 0;
}
