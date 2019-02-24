#include<cstdio>
using namespace std;
FILE *f=freopen("cuburi4.in","r",stdin);
FILE *g=freopen("cuburi4.out","w",stdout);
void transf(long x,long &y)
{
	int cifre[11],i,j,p,cmin,im,u,v,aux;
	j=1;
	while(x>0)
	{
		cifre[j]=x%10;
		x=x/10;
		j++;
	}
	j--;
	u=1;v=j;
	while(u<v)
	{
		aux=cifre[u];
		cifre[u]=cifre[v];
		cifre[v]=aux;
		u++; v--;
	}
	im=1; cmin=cifre[1];
	for(i=2;i<=4;i++)
		if(cifre[i]>0 && cmin>cifre[i])
		{
			cmin=cifre[i];
			im=i;
		}
	y=cmin;
	for(p=2;p<=j-3; p++)
	{
		i=im+1;;
		cmin=10;
		while(i<=p+3)
		{
			if(cifre[i]<cmin)
			{
				cmin=cifre[i];
				im=i;
			}
			i++;
		}
		y=y*10+cmin;
	}
}

int main()
{
	long z[100000]={0},w,u,k,x,y;
	long n,m,i,j,nrp,nrc,p,v;
	j=u=0;
	fscanf(f,"%d %d",&n,&k);
	m=k*(k+1)*(2*k+1);
	for(i=1;i<=m;i++)
	{
		    fscanf(f,"%ld",&x);
			transf(x,y);
			z[i]=y;
	}

	nrp=0;
	v=0;
	p=0;
	do{
		p++;
		w=6*p*p;
		if(v+w<=n)
		{
			nrp++;
			v=v+w;
		}
		else break;
	}while(v<=n);

	fprintf(g,"%d\n",nrp);

	for(i=1;i<m;i++)
		fprintf(g,"%ld ",z[i]);

	fprintf(g,"%ld\n",z[m]);

	return 0;
}
