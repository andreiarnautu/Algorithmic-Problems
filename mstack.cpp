/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cassert>

FILE *fin = freopen("mstack.in", "r", stdin); FILE *fout = freopen("mstack.out", "w", stdout);

const int kStringSize = 10;
const int kStackNumber = 4;


/*-------- Data --------*/
std::vector<int > stack[kStackNumber];
int elementCount;
/*-------- --------*/

void Recalibrate(const int a, const int b) {
    int k = stack[a].size() / 2;

    for(int i = 0; i < k; i++) {
        printf("move %d %d\n", a + 1, 3);                                        ///  PRINT
        stack[2].push_back(stack[a].back());
        stack[a].pop_back();
    }

    while(!stack[a].empty()) {
        printf("move %d %d\n", a + 1, b + 1);                                        ///  PRINT
        stack[b].push_back(stack[a].back());
        stack[a].pop_back();
    }

    while(!stack[2].empty()) {
        printf("move %d %d\n", 3, a + 1);                                        ///   PRINT
        stack[a].push_back(stack[2].back());
        stack[2].pop_back();
    }

    assert(stack[b].size() > 0);
}

void PushFront(const int x) {
    printf("push 1\n");
    stack[0].push_back(x);
}

void PopFront() {
    if(stack[0].empty()) {
        Recalibrate(1, 0);
    }
    printf("pop 1\n");
    stack[0].pop_back();
}

void PushBack(const int x) {
    printf("push 2\n");
    stack[1].push_back(x);
}

void PopBack() {
    if(stack[1].empty()) {
        Recalibrate(0, 1);
    }
    printf("pop 2\n");
    stack[1].pop_back();
}

void MStackPush() {
    elementCount ++; PushFront(elementCount);

    if((int)stack[3].size() < elementCount / 2) {
        if(stack[1].empty()) {
            Recalibrate(0, 1);
        }

        printf("move 2 4\n");

        stack[3].push_back(stack[1].back()); stack[1].pop_back();
    }
}

void MStackPop() {
    PopFront(); elementCount --;

    if((int)stack[3].size() > elementCount / 2){
        printf("move 4 2\n");

        stack[1].push_back(stack[3].back()); stack[3].pop_back();
    }
}

void MStackTop() {
    if(stack[0].empty()) {
        Recalibrate(1, 0);
    }
    printf("top 1\n");
}

void MStackMiddle() {
    if(stack[1].empty()) {
        Recalibrate(0, 1);
    }
    printf("top 2\n");
}

void ProcessOperations() {
    int N; scanf("%d", &N);

    char s[kStringSize];

    for(int i = 0, x = 0; i < N; i++) {
        scanf("%s", s);

        if(s[0] == 'p' && s[1] == 'u') {
            MStackPush();
        } else if(s[0] == 'p' && s[1] == 'o') {
            MStackPop();
        } else if(s[0] == 't') {
            MStackTop();
        } else {
            MStackMiddle();
        }
    }
}

int main() {
    ProcessOperations();

    return 0;
}
