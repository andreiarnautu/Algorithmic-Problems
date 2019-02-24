/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <cassert>

#define x first
#define y second

typedef std::pair<double, double > Point;

FILE *fin = freopen("cascaval.in", "r", stdin);
FILE *fout = freopen("cascaval.out", "w", stdout);

const int kMaxN = 100000 + 1;
double kMaxInf = 1e14;

/*-------- Structures --------*/
struct Line {
    long long a, b, c;
    Line() {}
    Line(const long long _a, const long long _b, const long long _c) {
        a = _a; b = _b; c = _c;
    }
};

struct StackElement {
    double left, right;
    Line line;

    StackElement(double _left, double _right, Line _line) {
        left = _left; right = _right; line = _line;
    }
};
/*-------- Input data --------*/
int N;
long long F[kMaxN], C[kMaxN], S[kMaxN], D[kMaxN];
/*-------- Partial sums --------*/
long long sumD[kMaxN], sumS[kMaxN], sumT[kMaxN];
/*-------- DP --------*/
long long dp[kMaxN];
std::vector<StackElement > stack;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%lld%lld%lld%lld", &F[i], &C[i], &S[i], &D[i]);
    }
}

void ComputePartialSums() {
    for(int i = 1; i <= N; i++) {
        sumD[i] = sumD[i - 1] + D[i];
        sumS[i] = sumS[i - 1] + S[i];
        sumT[i] = sumT[i - 1] + S[i] * sumD[i];
    }
}

Point GetIntersectionPoint(Line d1, Line d2) {
    double num = d1.b * d2.a - d1.a * d2.b;
    double x = -(d2.c * d1.b - d1.c * d2.b) / num;
    double y = (d2.c * d1.a - d1.c * d2.a) / num;
    return {x, y};
}

void Insert(const Line insertLine) {
    while(!stack.empty()) {
        Point P = GetIntersectionPoint(insertLine, stack.back().line);
        if(stack.back().left < P.x) {
            stack.back().right = P.x;
            stack.push_back({P.x, kMaxInf, insertLine});
            break;
        } else {
            stack.pop_back();
            if(!stack.empty()) {
                stack.back().right = kMaxInf;
            }
        }
    }
    if(stack.empty()) {
        stack.push_back({-kMaxInf, +kMaxInf, insertLine});
    }
}

Line Query(double value) {
    int left = 0, right = (int)stack.size() - 1;
    while(left <= right) {
        int mid = (left + right) >> 1;

        if(stack[mid].left <= value && value <= stack[mid].right) {
            return stack[mid].line;
        } else if(value < stack[mid].left) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%.5f %.5f %.5f", stack[0].left, stack.back().right, value);
    assert(0 > 1);
}

long long RunDP() {
    Insert({sumD[N], -1, sumD[N] * sumS[N] - sumT[N]});

    for(int i = N; i > 0; i--) {
        Line queryLine = Query(C[i] - sumS[i - 1]);
        dp[i] = queryLine.a * (C[i] - sumS[i - 1]) + queryLine.c + (sumT[i - 1] + F[i] - C[i] * sumD[i - 1]);
        Insert({sumD[i - 1], -1, dp[i] + sumD[i - 1] * sumS[i - 1] - sumT[i - 1]});
    }

    return dp[1];
}

int main() {
    ReadInput();
    ComputePartialSums();
    printf("%lld\n", RunDP());
    return 0;
}
