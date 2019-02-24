// Prof. Florentina Ungureanu Colegiul de Informatica Piatra Neamt
#include<fstream>
//#include<iostream>
#include<cstring>
using namespace std;
ifstream f("fractie1.in");
ofstream g("fractie1.out");
void norm(char *s, int &x, int&y, int&z)
{ char *p=s;
  x=0;
  if(s[0]!='0') while(*p!=',')x++,p++;
	  else strcpy(p,p+1);
  strcpy(p,p+1);
  y=x;
  while(*p!='(')y++,p++;
  strcpy(p,p+1);
  z=y;
  while(*p!=')')z++,p++;
  strcpy(p,p+1);
}
void elim(char s[])
{char *p,*q,*r,c;
 int x, i;
 p=strchr(s,'(')-1;
 q=strchr(s,')')-1;
 while(*p==*q){c=*p;*p=*(p+1);*(p+1)=c;strcpy(q, q+1);p--;q--;}
 p=strchr(s,'(')+1;
 q=strchr(s,')');
 x=q-p;
 for(i=1;i<=x/2;i++)
	 if (x%i==0)
		 {r=p+i;
		  while(!strncmp(p,r,i)) {r+=i;}
		  if(*r==')') {strcpy(p+i,r);i=x;}
		  }
}
int main()
{char s[81],*p,*q,*r,a[81];
 int x,y,z,i;
 f>>s;
  if(!(p=strchr(s,',')))
	 {g<<s<<'\n'<<1<<'\n';g.close();f.close();return 0;}
 while(s[strlen(s)-1]=='0') s[strlen(s)-1]=0;
if(!(q=strchr(s,'(')))
		 {if(s[strlen(s)-1]==',')
				 {s[strlen(s)-1]=0;g<<s<<'\n'<<1<<'\n';}
			 else
				 {strcpy(p,p+1);
				  r=s;while(*r=='0')r++;
				  g<<r<<'\n'<<1;
				  while(*p){g<<0;p++;}
				  g<<'\n';}
		  g.close();f.close();return 0;
		 }
	else {elim(s);
		 p=strchr(s,',');q=strchr(s,'(');
		 if(p+1==q&&s[0]=='0')
				 {s[strlen(s)-1]='\0';
				  g<<s+3<<'\n';
				  p+=2;
				  while(*p){g<<9;p++;}
				  g<<'\n';
				 }
			  else{norm(s,x,y,z);
				  strncpy(a,s,y);a[y]=0;
				  p=s+z-1;q=a+y-1;i=0;
				  while(q>a)
				    {if(*p<*q+i){*p=*p+'0'+10-*q-i;i=1;}
					  else {*p=*p+'0'-*q-i;i=0;}
				     p--;q--;
				    }
				  if(*p<*q+i){*p=*p+'0'+10-*q-i;i=1;}
					  else {*p=*p+'0'-*q-i;i=0;}
				  p--;
				  if(i)
					  {while(*p=='0')*p='9',p--;
					   (*p)--;
					  }
				  i=0;while(s[i]=='0')i++;
				  g<<s+i<<'\n';
				  z-=y;
				  for(i=0;i<z;i++)g<<9;
				  y-=x;
				  for(i=0;i<y;i++)g<<0;
				  g<<'\n';
				 }
		}
 f.close();
 g.close();
 return 0;
}
