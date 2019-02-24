#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#define NMAX 1003
#define DB 0
using namespace std;
int n;
double d[NMAX], sol;
struct str
{
    int x, y, d;

};
str v[NMAX];
int prod(str p1, str p2, str p3) {
    return p2.x*p3.y - p2.x*p1.y - p1.x*p3.y + p1.x*p1.y - p3.x*p2.y + p3.x*p1.y + p1.x*p2.y - p1.x*p1.y;
}

int cmp(str a, str b) {
    if((a.x-v[1].x)*(b.y-v[1].y)!=(b.x-v[1].x)*(a.y-v[1].y)) {
         return (a.x-v[1].x)*(b.y-v[1].y) > (b.x-v[1].x)*(a.y-v[1].y);
    }
    else if(v[1].y==a.y && v[1].y==b.y) {
         return (a.x-v[1].x)*(a.x-v[1].x) + (a.y-v[1].y)*(a.y-v[1].y) <
                (b.x-v[1].x)*(a.x-v[1].x) + (b.y-v[1].y)*(b.y-v[1].y);
    }
    else if(!prod(a, b, v[1])) {
          return a.x<b.x;
          }
}
double dist (int p)
{
    int p1 = p - 1, p2 = p + 1;
    if (p1 == 0)
        p1 = n;
    if (p2 == n + 1)
        p2 = 1;
    double x = (v[p1].x - v[p2].x) * (v[p1].x - v[p2].x) * 1.0;
    double y = (v[p1].y - v[p2].y) * (v[p1].y - v[p2].y) * 1.0;
    if (DB && p == 1)
        cout << p1 << " " << p2 << " " << x<< " " << y << " " << v[p1].x << " " << v[p2].x << "\n";
    return (double) sqrt ((double)x + y) * 1.0 * v[p].d * 0.5;
}
int main()
{
    ifstream cin ("mosia.in");
    ofstream cout ("mosia.out");
    cin >> n;
    int poz = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i].x >> v[i].y >> v[i].d;
        if (poz == 0)
            poz = i;
        else if (v[poz].y == v[i].y){
            if( v[i].x < v[poz].x)
                poz = i;
        }
        else if (v[poz].y > v[i].y)
            poz = i;

    }
    swap (v[1], v[poz]);
    sort (v + 2, v + 1 + n, cmp);

    if (DB)
    {

        for (int i = 1;i <=n; i++)
            cout << v[i].x << " "<< v[i].y << "\n";
    }

    if(DB)
    for (int i = 1; i <= n; i++)
        cout << dist(i) <<" "<< v[i].d  << "\n";
    for (int i = 1; i < n; i ++)
    {
        d[i] = max (d[i - 1], d[max (0 ,i - 2)] + dist(i));

    }
    sol = d[n - 1];
    memset (d, 0, sizeof(d));
    for (int i = 2; i <= n; i++)
    {
        d[i] = max (d[i - 1], d[max(0, i - 2)] + dist(i));
    }
    sol = max (sol, d[n]);

    cout << fixed << setprecision(4) << sol;

    return 0;
}
