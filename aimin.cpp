/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("aimin.in", "r", stdin);
FILE *fout = freopen("aimin.out", "w", stdout);

std::vector<int > ReadInput() {
    int N; scanf("%d", &N);
    std::vector<int > lengths; lengths.resize(N);
    for(auto& length : lengths) {
        scanf("%d", &length);
    }
    return lengths;
}

int GetMinHeight(const std::vector<int >& lengths) {
    int N = lengths.size(), cursor = 0;
    std::vector<int > height(N, 0);

    for(auto& length : lengths) {
        if(height[0] == 0) {
            height[0] = length;
        } else {
            while(cursor > 0) {
                height[cursor - 1] = std::max(height[cursor - 1], height[cursor] + 1);
                if(height[cursor - 1] >= 2 + std::max(height[cursor], length)) {
                    height[cursor] ++;
                    height[++ cursor] = length;
                    break;
                } else {
                    height[cursor --] = 0;
                }
            }
            if(cursor == 0) {
                height[0] = std::max(height[0] + 1, length + 1);
                height[++ cursor] = length;
            }
        }
    }

    while(cursor > 0) {
        height[cursor - 1] = std::max(height[cursor - 1], height[cursor] + 1);
        cursor --;
    }

    return height[0];
}

int main() {
    printf("%d\n", GetMinHeight(ReadInput()));
    return 0;
}
