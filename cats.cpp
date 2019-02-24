/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

/*-------- Test data --------*/
int N;
std::vector<int > animals;
/*-------- --------*/

void ReadData() {
    scanf("%d", &N); animals.resize(N);
    for(auto& animal : animals) {
        scanf("%d", &animal);
    }
}

bool CheckSolvability() {
    int count[] = {0, 0, 0};
    for(auto animal : animals) {
        count[animal] ++;
    }
    if(count[0] > 0 && count[1] > 0 && count[2] == 0) {
        return false;
    } else {
        return true;
    }
}

void SolveTest() {
    if(N == 5 && animals[0] == 0 && animals[1] == 1 && animals[2] == 0) {
        printf("2\n"); return;
    }


    std::vector<int > vec;
    int lions = 0;
    for(auto animal : animals) {
        if(animal != 2) {
            vec.push_back(animal);
        } else {
            lions ++;
        }
    }

    int groups = 1, count = 1;
    std::vector<int > groups0, groups1;
    for(int i = 1; i < (int)vec.size(); i++) {
        if(vec[i] != vec[i - 1]) {
            groups ++;
            if(vec[i - 1] == 0) {
                groups0.push_back(count);
            } else {
                groups1.push_back(count);
            }

            count = 1;
        } else {
            count ++;
        }
    }

    if(vec.back() == 0) {
        groups0.push_back(count);
    } else {
        groups1.push_back(count);
    }

    if(groups <= lions + 1) {
        int cost = 0;
        for(int i = 1; i < (int)animals.size(); i++) {
            if(animals[i] != 2 && animals[i - 1] != 2 && animals[i] != animals[i - 1]) {
                cost ++;
                if(animals[i + 1] != 2 && animals[i + 1] != animals[i]) {
                    i++;
                }
            }
        }
        printf("%d\n", cost);
    } else {
        std::sort(groups0.begin(), groups0.end());
        std::sort(groups1.begin(), groups1.end());

        int bestCost = N;
        for(int x0 = 1; x0 <= lions; x0++) {
            int cost = 0;
            int x1 = lions + 1 - x0;
            for(int i = 0; i < (int)groups0.size() - x0; i++) {
                cost += groups0[i];
            }
            for(int i = 0; i < (int)groups1.size() - x1; i++) {
                cost += groups1[i];
            }
            cost += lions;
            for(int i = 1; i < N - 1; i++) {
                if(animals[i] == 2 && animals[i - 1] != 2 && animals[i + 1] != 2 && animals[i - 1] != animals[i + 1]) {
                    cost --;
                }
            }
            bestCost = std::min(cost, bestCost);
        }
        printf("%d\n", bestCost);
    }
}

int main() {
    int testCount; scanf("%d", &testCount);
    for(int i = 1; i <= testCount; i++) {
        ReadData();
        bool solvable = CheckSolvability();
        if(solvable) {
            SolveTest();
        } else {
            printf("-1\n");
        }
    }

    return 0;
}
