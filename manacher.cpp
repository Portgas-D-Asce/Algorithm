#include <iostream>
#include <string>
#include <vector>
using namespace std;


// start != end && start, end not in s
template<typename T, typename U = typename T::value_type>
pair<size_t, size_t> manacher(const T& s, U start, U end) {
    T t(2, start);
    for(auto ch : s) {
        t.push_back(ch);
        t.push_back(start);
    }
    t.push_back(end);

    size_t c = 0, r = 0, m = t.size();
    vector<size_t> p(m);
    for(size_t i = 2, id = 0, mx = 0; i < m - 2; ++i) {
        // 延伸内部存在可用信息
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;

        // 延伸外部不存在可用信息，需逐一比较
        while(t[i + p[i]] == t[i - p[i]]) {
            ++p[i];
        }

        // 更新延伸
        if(mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }

        // 记录 t 最长回文子串的半径及中心
        if(p[i] > r) {
            r = p[i];
            c = i;
        }
    }

    // 还原得到 s 的最长回文子串, 起始位置 + 长度
    return {(c - r) / 2, r - 1};
}


int main() {
    string s = "aabcdacdcadc";
    auto [idx, sz] = manacher(s, '#', '$');
    cout << s.substr(idx, sz) << endl;

    vector<int> nums = {1, 2, 2, 3, 3, 2, 5};
    auto [idx1, sz1] = manacher(nums, -1, -2);
    cout << idx1 << endl;
    cout << sz1 << endl;
    return 0;
}