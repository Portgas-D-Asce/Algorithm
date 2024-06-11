#include <iostream>
using namespace std;


string pre_palindrome(const string &s) {
    if(s.empty()) return s;
    // "0", "1" 的时候会得到空字符串
    if(s == "0" || s == "1") return "0";

    string t = s;
    ssize_t n = t.size();
    for(ssize_t i = 0, j = n - 1; i < j; ++i, --j) {
        t[j] = t[i];
    }
    // 可以通过 “将右半边变为左半边” 的方式得到
    // 这里仅仅把等号去掉
    if(t < s) return t;

    // 否则 “先将左半边减 1，然后赋给右半边”
    for(ssize_t i = (n - 1) / 2; i >= 0; --i) {
        if(t[i] != '0') {
            t[n - 1 - i] = --t[i];
            break;
        }
        t[i] = t[n - 1 - i] = '9';
    }
    // “减一导致了位数变化” 10000 这种情况
    if(t[0] == '0') {
        t[0] = '9';
        t.pop_back();
    }
    return t;
}


string next_palindrome(const string &s) {
    if(s.empty()) return s;
    string t = s;
    ssize_t n = t.size();
    for(ssize_t i = 0, j = n - 1; i < j; ++i, --j) {
        t[j] = t[i];
    }
    // 可以通过 “将右半边变为左半边” 的方式得到
    // 这里仅仅把等号去掉
    if(s < t) return t;

    // 否则 “先将左半边加一，然后赋给右半边”
    for(ssize_t i = (n - 1) / 2; i >= 0; --i) {
        if(t[i] != '9') {
            t[n - 1 - i] = ++t[i];
            break;
        }
        t[i] = t[n - 1 - i] = '0';
    }
    // “加一导致了位数变化” 9999 这种情况
    if(t[0] == '0') {
        t[0] = '1';
        t.push_back('1');
    }
    return t;
}


int main() {
    cout << pre_palindrome("0") << endl;
    cout << pre_palindrome("1") << endl;
    cout << pre_palindrome("9") << endl;
    cout << pre_palindrome("10") << endl;
    cout << pre_palindrome("100000") << endl;
    cout << pre_palindrome("100000001") << endl;
    cout << pre_palindrome("2147483647") << endl;

    cout << next_palindrome("0") << endl;
    cout << next_palindrome("1") << endl;
    cout << next_palindrome("9") << endl;
    cout << next_palindrome("10") << endl;
    cout << next_palindrome("99999") << endl;
    cout << next_palindrome("999998") << endl;
    cout << next_palindrome("2147483647") << endl;
    return 0;
}