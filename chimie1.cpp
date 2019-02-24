#include <cstdio>
using namespace std;
FILE *f=fopen("chimie1.in","r");
FILE *g=fopen("chimie1.out","w");
int v1[105][301],v2[105][301];
int main()
{int i,j,n,p;
fscanf(f,"%d %d",&n,&p);
v1[1][300]=2;
v2[1][300]=n-2;
for (i=2;i<=p;i++) {for (j=1;j<=300;j++) v1[i][j]=v1[i-1][j]+v2[i-1][j]*2;
                    for (j=300;j>=2;j--) if (v1[i][j]>=10) {v1[i][j-1]+=v1[i][j]/10;
                                                            v1[i][j]%=10;
                                                            }

                    for (j=1;j<=300;j++) v2[i][j]=(n-2)*(v1[i-1][j]+v2[i-1][j]);
                    for (j=300;j>=2;j--) if (v2[i][j]>=10) {v2[i][j-1]+=v2[i][j]/10;
                                                            v2[i][j]%=10;
                                                            }
                    }
for (i=1;i<=300;i++) v1[p][i]+=v2[p][i];
for (i=300;i>=2;i--) if (v1[p][i]>=10) {v1[p][i-1]+=v1[p][i]/10;
                                        v1[p][i]%=10;
                                        }
i=1;
while (v1[p][i]==0) i++;
for (j=i;j<=300;j++) fprintf(g,"%d",v1[p][j]);
return 0;
}
