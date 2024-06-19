#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T>
vector<int> z_func(const T& s) {
    int n = s.size();
    // z[i] 初始值均为 0，z[0] 全匹配初始值为 n
    vector<int> z(n);
    z[0] = n;

    // [p, r] 是一个前缀，且是 r 延伸得最远的那个
    for(int i = 1, p = 0, r = 0; i < n; ++i) {
        // [p, r] 范围内存在额外信息可用
        if(i <= r) {
            // [p, r] 是一个前缀，即 [p, r] == [0, r - p]
            // 环境一样，z[i] == z[i - p]，但是 i + z[i] 不能超过 r
            z[i] = min(z[i - p], r - i + 1);
        }

        // [p, r] 范围外无额外信息可用，只能老老实实比
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }

        // z[i] 表示后缀 i 与 s 的公共前缀长度为 z[i]
        // 那么后缀 i 与 s 的公共前缀当然延伸到了 i + z[i] - 1
        // 如果可以延伸得更远，则更新
        if(i + z[i] - 1 > r) {
            p = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}


int main() {
    string s = "aabcaabxaaaz";
    auto zs = z_func(s);
    for(int x : zs) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> nums = {1, 3, 5, 1, 3, 5, 1, 1, 3, 2, 4};
    auto zi = z_func(nums);
    for(int x : zi) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
