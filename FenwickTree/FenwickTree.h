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
    const value_type init_val;
    Sequence raw;
    Sequence ft;
    Calculate cal;
public:
    explicit FenwickTree(size_type n, const_reference init = value_type())
        : init_val(init), raw(n, init), ft(n + 1, init) {}

    explicit FenwickTree(const Sequence& s, const_reference init = value_type())
        : init_val(init), raw(s), ft(s.size() + 1, init) {
        _make_ft();
    }

    explicit FenwickTree(Sequence&& s, const_reference init = value_type())
        : init_val(init), raw(move(s)), ft(s.size() + 1, init) {
        _make_ft();
    }

    template<typename InputIterator>
    FenwickTree(InputIterator first, InputIterator last, const_reference init = value_type())
        : init_val(init), raw(first, last), ft(distance(first, last) + 1, init) {
        _make_ft();
    }

    // 1-indexed idx
    void update(size_type idx, const_reference val) {
        raw[idx - 1] = cal(raw[idx - 1], val);
        while(idx < ft.size()) {
            ft[idx] = cal(ft[idx], val);
            idx += lowbit(idx);
        }
    }

    // 1-indexed idx
    value_type query(size_type idx) const {
        value_type res = init_val;
        while(idx) {
            res = cal(res, ft[idx]);
            idx -= lowbit(idx);
        }
        return res;
    }

    // 1-indexed [p, r]
    value_type query(size_type p, size_type r) const {
        value_type res = init_val;
        while(p <= r) {
            if(p <= r - lowbit(r)) {
                res = cal(res, ft[r]);
                r -= lowbit(r);
            } else {
                res = cal(res, raw[r - 1]);
                r--;
            }
        }
        return res;
    }

private:
    static int lowbit(int x) {
        return x & (-x);
    }

    void _make_ft() {
        size_type n = raw.size();
        for(size_type i = 1; i <= n; ++i) {
            ft[i] = cal(ft[i], raw[i - 1]);
            size_type idx = i + lowbit(i);
            if(idx <= n) {
                ft[idx] = cal(ft[idx], ft[i]);
            }
        }
    }
};