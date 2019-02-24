# include <bits/stdc++.h>
# define NR 30005
# define N 500005
using namespace std;
ifstream f("demolish.in");
ofstream g("demolish.out");
struct elem {
    int x, y, x2, y2, cost;
}a[NR], a2[NR];
bool cmpx (elem x, elem y) {
    return x.x < y.x;
}
bool cmpx2 (elem x, elem y) {
    return x.x2 < y.x2;
}
struct elem2 {
    long long minn;
    int y;
}ARB[4*N];
// in ARB[i] tin minte costul minim pentru a segmentul de lungime OY
// care incepe in punctul i pana la i+OY-1
int i,j,n,m,X,Y,VVx,VVx2,DX,DY,F,CS;
long long lazy[4*N], minn;
void init (int nod, int ci, int cs) {
    if (ci==cs) ARB[nod].y=ci;
    else {
        int mij=(ci+cs)/2;
        if (ci<=mij) init (2*nod, ci, mij);
        if (mij<cs) init (2*nod+1, mij+1, cs);

        ARB[nod].y=min(ARB[2*nod].y, ARB[2*nod+1].y);
    }
}
void update (int nod, int ci, int cs, int CI, int CS, int cost) {
    if (CI > CS) return;

    if(lazy[nod] != 0) {
        /* daca trebuie updatat intervalul curent */
        ARB[nod].minn += lazy[nod];
        if(ci != cs) {
            lazy[nod * 2] += lazy[nod];
            lazy[nod * 2 + 1] += lazy[nod];
        }
        lazy[nod] = 0;
    }

    if (CI<=ci && cs<=CS) {
        ARB[nod].minn+=cost;
        if(ci != cs) {
            lazy[nod * 2] += cost;
            lazy[nod * 2 + 1] += cost;
        }
    }
    else {
        int mij=(ci + cs)/2;
        if (CI<=mij) update (2*nod, ci, mij, CI, CS, cost);
        if (mij<CS) update (2*nod+1, mij+1, cs, CI, CS, cost);

        if (ARB[2*nod].minn + lazy[2*nod] <= ARB[2*nod+1].minn + lazy[2 * nod + 1]) {ARB[nod].minn = ARB[2*nod].minn + lazy[2*nod];}
                                             else { ARB[nod].minn = ARB[2*nod+1].minn + lazy[2 * nod + 1]; }
    }
}
void query (int x) {
    if (ARB[1].minn < minn) minn=ARB[1].minn, X=x, Y=ARB[1].y;
}
int main ()
{
    f>>m>>n>>F>>DX>>DY;

    /*if (DY==1 || DX==1) {
        g<<"0\n0 0"<<DX-1<<" "<<DY<<"\n";
        return 0;
    }*/

    for (i=1; i<=F; ++i) {
        f>>a[i].x>>a[i].y>>a[i].x2>>a[i].y2>>a[i].cost;
        a2[i]=a[i];
    }
    sort (a+1, a+F+1, cmpx);
    sort (a2+1, a2+F+1, cmpx2);

    CS=n - DY; init (1, 0, CS);

    VVx=0; VVx2=0; minn=1LL<<60;

    for (i=DX; i<m; ++i) { //dreapta de baleiere este in dreapta
        //bagam noile dreptunghiuri care intra in planul meu
        while (a[VVx+1].x <i && VVx<F) {
            ++VVx;
            update (1, 0, CS, max(a[VVx].y-DY+1, 0), min(a[VVx].y2-1, CS), a[VVx].cost);
        }
        //scoatem dreptunghiurile care avem muchie din dr pe i
        while (a[VVx2+1].x2 <= i-DX && VVx2<F) {
            ++VVx2;
            update (1, 0, CS, max(a[VVx2].y-DY+1, 0), min(a[VVx2].y2-1, CS), -a[VVx2].cost);
        }
        query (i);
    }
    g<<minn<<"\n"<<X-DX<<" "<<Y<<" "<<X<<" "<<Y+DY<<"\n";
    return 0;
}
