/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("patrate5.in", "r", stdin);
FILE *fout = freopen("patrate5.out", "w", stdout);

const int MAX_N = 1 + 50000;

/*-------- Data structures --------*/
struct Point {
    int x, y;
    Point() {}
    Point(const int _x, const int _y) {x = _x; y = _y;}
};

struct Square {
    int x, y, length;
    Square() {}
    Square(const int _x, const int _y, const int _length) {x = _x; y = _y; length = _length;}
};
/*-------- Input data --------*/
int N;
Point points[MAX_N];
/*-------- Algorithm data --------*/
int first_line, last_line, first_col, last_col;

Square A, B, C;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
}

void GetRectangle() {
    first_col = first_line = MAX_N;
    last_col = last_line = -1;

    for(int i = 1; i <= N; i++) {
        first_line = std::min(first_line, points[i].x);
        last_line = std::max(last_line, points[i].x);
        first_col = std::min(first_col, points[i].y);
        last_col = std::max(last_col, points[i].y);
    }
}

bool IsInside(Square S, Point p) {
    return (S.x <= p.x && p.x <= S.x + S.length && S.y <= p.y && p.y <= S.y + S.length);
}

bool FinalCheck() {
    bool answer = true;

    for(int i = 1; i <= N; i++) {
        if(!IsInside(A, points[i]) && !IsInside(B, points[i]) && !IsInside(C, points[i])) {
            answer = false; break;
        }
    }

    return answer;
}

bool Continue() {
    bool answer = false;
    int crt_first_line = MAX_N, crt_last_line = -1, crt_first_col = MAX_N, crt_last_col = -1;

    for(int i = 1; i <= N; i++) {
        if(!IsInside(A, points[i])) {
            crt_first_line = std::min(crt_first_line, points[i].x);
            crt_last_line = std::max(crt_last_line, points[i].x);
            crt_first_col = std::min(crt_first_col, points[i].y);
            crt_last_col = std::max(crt_last_col, points[i].y);
        }
    }

    if(crt_first_line == MAX_N) {  //  Daca toate punctele sunt deja acoperite de primul patrat
        answer = true;
    } else {
        //  Avem doua posibilitati sa asezam cele doua patrate in functie de punctele ramase
        B.x = crt_first_line; B.y = crt_first_col;
        C.x = crt_last_line - C.length; C.y = crt_last_col - C.length;
        answer |= FinalCheck();

        B.x = crt_last_line - B.length; B.y = crt_first_col;
        C.x = crt_first_line; C.y = crt_last_col - C.length;
        answer |= FinalCheck();
    }

    return answer;
}

bool IsEnough(int length) {  //  Vrem sa vedem daca pentru o lungime data a laturii patratelor exista o posibilitate de a acoperi punctele
    A.length = B.length = C.length = length;
    bool enough = false;

    //  Fixam pe rand primul patrat in unul din colturi si apoi vedem ce se intampla
    A.x = first_line; A.y = first_col;
    enough |= Continue();
    if(enough) {return true;}

    A.x = first_line; A.y = last_col - A.length;
    enough |= Continue();
    if(enough) {return true;}

    A.x = last_line - A.length; A.y = first_col;
    enough |= Continue();
    if(enough) {return true;}

    A.x = last_line - A.length; A.y = last_col - A.length;
    enough |= Continue();

    return enough;
}

int BinarySearch() {  //  Cautam binar raspunsul
    int answer = 0, left = 1, right = 50001;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(IsEnough(mid)) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return answer;
}

int main() {
    ReadInput();
    if(N == 3) {  //  Daca sunt doar 3 puncte, e clar ca latura e 0
        printf("0\n");
    } else {
        GetRectangle();
        printf("%d\n", BinarySearch());
    }
    return 0;
}
