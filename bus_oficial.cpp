#include <cstdlib>
#include <fstream>
using namespace std;

#define MAX_SIZE 100001
#define INFINITE 2000000001

typedef struct {int x, y;} Point;

int cmpLess(const void *a, const void *b)
{
	Point p1 = *((Point*)a);
	Point p2 = *((Point*)b);
	return (p1.x != p2.x) ? (p1.x - p2.x) : (p1.y - p2.y);
}


int main()
{
	fstream 	f, g;
	int 		a, b, N, len, maxPoints;
	int 		best[MAX_SIZE];
	Point		point[MAX_SIZE];

	f.open("bus.in",  ios::in);
	g.open("bus.out", ios::out);

	f >> a >> b >> N;
	for (int i = 0; i < N; i++)
		f >> point[i].x >> point[i].y;

	qsort(point, N, sizeof(Point), cmpLess);
	best[0] = INFINITE;
	for (int i = 1; i < N; best[i++] = -INFINITE);

	maxPoints = 0;
	for (int i = N-1; i >= 0; i--)
	{
		int lo = 0, hi = N - 1, mid, len = 0;

		while (lo <= hi)
		{
			mid = (lo + hi) / 2;
			if (point[i].y <= best[mid])
			{
				len = mid;
				lo 	= mid + 1;
			}
			else hi = mid - 1;
		}

		maxPoints = max(maxPoints, ++len);
		best[len] = max(best[len], point[i].y);
	}

	g << maxPoints << endl;

	f.close();
	g.close();

	return 0;
}

