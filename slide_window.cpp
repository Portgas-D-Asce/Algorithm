#include <iostream>
#include <vector>
using namespace std;

// min win 伪代码
/*template<typename T>
T slide_win(const vector<T> &nums) {
    // 窗口初始位置及长度
    int idx = -1, len = INT_MAX;
    for(int i = 0, j = 0; i < n; ++i) {
        // 将第 i 个元素加入窗口
        c[s[i] - 'A']++;

        // 新元素加入可能会导致窗口性质成立，但当前不一定是最小窗口
        while(check(c)) {
            // 更新最小窗口
            if(i - j + 1 < len) {
                len = i - j + 1;
                idx = j;
            }
            // 不断地从窗口左侧移出元素，直到性质不成立
            c[s[j++] - 'A']--;
        }
    }
    return len;
}*/

// max win 伪代码
/*template<typename T>
T slide_win(const vector<T>& nums) {
    // 窗口初始位置及长度
    size_t idx = 0, len = 0, n = nums.size();
    for(size_t i = 0, j = 0; i < n; ++i) {
        // 将第 i 个元素添加到窗口里面
        c[s[i] - 'A']++;

        // 添加新元素到窗口后可能会使窗口性质遭到破坏
        while(!check(c)){
            // 不断地从窗口左侧移出元素，直至窗口性质成立
            c[s[j++] - 'A']--;
        }

        // 更新最大窗口
        if(i - j + 1 > len) {
            len = i - j + 1;
            idx = j;
        }
    }
    return len
}*/


int main() {

    return 0;
}

