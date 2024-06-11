#include <iostream>
#include <vector>
#include <functional>
using namespace std;


template<typename T>
class Max {
public:
    T operator()(const T& a, const T& b) const {
        return std::max(a, b);
    }
};

template<typename T>
class Min {
public:
    T operator()(const T& a, const T& b) const {
        return std::min(a, b);
    }
};

template<typename Tp, typename Sequence = vector<Tp>,
    typename Calculate = plus<typename Sequence::value_type>>
class FenwickTree {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type size_type;
    typedef Sequence container_type;
    typedef Calculate value_calculate;
protected:
    const value_type _init_val;
    container_type _raw, _ft;
    value_calculate _cal;
public:
    explicit FenwickTree(size_type n, const_reference init = value_type())
        : _init_val(init), _raw(n, init), _ft(n + 1, init) {}

    explicit FenwickTree(const container_type& s, const_reference init = value_type())
        : _init_val(init), _raw(s), _ft(s.size() + 1, init) {
        size_type n = _raw.size();
        for(size_type i = 1; i <= n; ++i) {
            _ft[i] = _cal(_ft[i], _raw[i - 1]);
            size_type idx = i + lowbit(i);
            if(idx <= n) {
                _ft[idx] = _cal(_ft[idx], _ft[i]);
            }
        }
    }

    void update(size_type idx, const_reference val) {
        _raw[idx] = _cal(_raw[idx], val);
        idx++;
        while(idx < _ft.size()) {
            _ft[idx] = _cal(_ft[idx], val);
            idx += lowbit(idx);
        }
    }

    value_type query(size_type idx) const {
        idx++;
        value_type res = _init_val;
        while(idx) {
            res = _cal(res, _ft[idx]);
            idx -= lowbit(idx);
        }
        return res;
    }

    value_type query(size_type p, size_type r) const {
        p++, r++;
        value_type res = _init_val;
        while(p <= r) {
            if(p <= r - lowbit(r)) {
                res = _cal(res, _ft[r]);
                r -= lowbit(r);
            } else {
                res = _cal(res, _raw[r - 1]);
                r--;
            }
        }
        return res;
    }

private:
    static inline size_t lowbit(size_t x) {
        return x & (-x);
    }
};


int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    FenwickTree<int> ft(nums, 0);
    cout << ft.query(0, 2) << endl;
    cout << ft.query(2) << endl;
    cout << ft.query(3, 6) << endl;
    ft.update(4, 20);
    cout << ft.query(3, 6) << endl << endl;

    FenwickTree<int, vector<int>, Max<int>> ftm(nums, INT_MIN);
    cout << ftm.query(0, 2) << endl;
    cout << ftm.query(2) << endl;
    cout << ftm.query(3, 6) << endl;
    ftm.update(4, 20);
    cout << ftm.query(3, 6) << endl << endl;

    FenwickTree<int, vector<int>, Min<int>> ftn(nums, INT_MAX);
    cout << ftn.query(0, 2) << endl;
    cout << ftn.query(2) << endl;
    cout << ftn.query(3, 6) << endl;
    ftn.update(4, -1);
    cout << ftn.query(3, 6) << endl << endl;


    FenwickTree<int, vector<int>, bit_xor<int>> ft_xor(nums, 0);
    cout << ft_xor.query(0, 2) << endl;
    cout << ft_xor.query(2) << endl;
    cout << ft_xor.query(3, 6) << endl;
    ft_xor.update(4, 7);
    cout << ft_xor.query(3, 6) << endl << endl;

    FenwickTree<int, vector<int>, bit_and<int>> ft_and(nums, -1);
    cout << ft_and.query(0, 2) << endl;
    cout << ft_and.query(2) << endl;
    cout << ft_and.query(3, 6) << endl;
    ft_and.update(4, 7);
    cout << ft_and.query(3, 6) << endl << endl;

    FenwickTree<int, vector<int>, bit_or<int>> ft_or(nums, 0);
    cout << ft_or.query(0, 2) << endl;
    cout << ft_or.query(2) << endl;
    cout << ft_or.query(3, 6) << endl;
    ft_or.update(4, 7);
    cout << ft_or.query(3, 6) << endl << endl;

    FenwickTree<int, vector<int>, multiplies<int>> ft_mul(nums, 1);
    cout << ft_mul.query(0, 2) << endl;
    cout << ft_mul.query(2) << endl;
    cout << ft_mul.query(3, 6) << endl;
    ft_mul.update(4, 7);
    cout << ft_mul.query(3, 6) << endl << endl;
    return 0;
}