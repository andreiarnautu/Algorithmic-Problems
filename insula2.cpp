#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
ifstream cin ("insula2.in");
ofstream cout ("insula2.out");

const int inf = 1000000000;
const int NMAX = 400;

vector <pair<double, double> > v;

double st[NMAX], st_a[NMAX], st_b[NMAX], st_c[NMAX], x, y, d[NMAX][NMAX], ms[NMAX][NMAX];
int  n, k;
int lvl;

int trig (int i, int j, int k)
{
    double a, b, c, r;
    a = v[i].first - v[j].first;
    b = v[j].second - v[i].second;
    c = -(a * v[i].second + b * v[i].first);
    r = a * v[k].second + b * v[k].first + c;
    if (r > 0)
        return 1;
    if (r < 0)
        return -1;
    return 0;
}

int main ()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y;
        v.push_back(make_pair(y, x));
    }
    v.push_back(make_pair(0, 0));
    sort(v.begin(), v.end());
    lvl = 1;
    st[lvl] = 1;
    for (int i = 2; i < v.size(); i++)
    {

        while (lvl >= 1 && trig (st[lvl - 1], st[lvl], i) < 0)
            lvl --;
        lvl ++;
        st[lvl] = i;
    }
    for (int i = 1; i <= lvl; i++)
    {
        st_a[i] = v[st[i - 1]].first - v[st[i]].first;
        st_b[i] = v[st[i]].second - v[st[i - 1]].second;
        st_c[i] = -(st_a[i] * v[st[i]].second + st_b[i] * v[st[i]].first);

    }
    if (k > lvl)
        k = lvl + 1;

    d[0][0] = 0.0;
    for (int i = 1; i <= k; i++)
        d[0][i] = inf;
    for (int i = 1; i <= lvl; i++)
    {
        for (int j = 0; j < i; j++)
            ms[i][j] = -1.0;

    }
    double xq = 0.0, xi = 0.0;
    for (int i = 1; i <= lvl; i++)
    {

        d[i][0] = inf;
        for (int j = 1; j <= k; j++)
        {
            d[i][j] = inf;
            if ((j == k && v[st[i]].second >= v[st[i - 1]].second) || (j > i))
                continue;
            for (int p = i - 1; p >= 0; p--)
            {
                double sum = 0.0;
                if (ms[i][p] < 0.0)
                {
                    for (int r = st[p] + 1; r < st[i]; r++)
                    {

                        if (p == 0)
                            xq = inf;
                        else
                            xq = -(st_b[p] * v[r].first + st_c[p])* 1.0 / st_a[p];
                        xi = -(st_b[i] * v[r].first + st_c[i])* 1.0  / st_a[i];
                        sum += 1.0 * min(xi, xq) - 1.0 * v[r].second;
                    }
                    ms[i][p] = sum;
                }
                else
                    sum = ms[i][p];

                sum += d[p][j - 1];
                d[i][j] = min(d[i][j], sum);
            }
        }
    }

    double maxi;
    for (int i = 0; i <= lvl; i++) {
        maxi = 0.0;
        for (int j = st[i] + 1; j < v.size(); j++)
            maxi = max(maxi, v[j].second);

        double sum_k = 0.0, sum_k2 = 0.0;
        for (int j = st[i] + 1; j < v.size(); j++) {
            double x;
            if (i)
                x = -(st_b[i] * v[j].first + st_c[i]) / st_a[i];
            else
                x = inf;
            sum_k += x - v[j].second;
            sum_k2 += min(x, maxi) - v[j].second;
        }
        d[i][k] += sum_k;
        d[i][k - 1] += sum_k2;
    }
    double sol = inf;
    for (int i = 0; i <= lvl; i++)
    {

        sol = min (sol, min(d[i][k], d[i][k - 1]));
    }

    cout << fixed << setprecision(4) <<  sol;
    return 0;

}
