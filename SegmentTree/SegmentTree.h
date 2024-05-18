template<typename Tp>
class Accumulate {
public:
    Tp operator()(const Tp& val, const Tp& x) const {
        return val;
    }
};

template<typename Tp>
class Accumulate<plus<Tp>> {
public:
    Tp operator()(const Tp& val, const Tp& x) const {
        return val * x;
    }
};

template<typename Tp>
class Accumulate<bit_xor<Tp>> {
public:
    Tp operator()(const Tp& val, const Tp& x) const {
        return (x & 1) ? val : 0;
    }
};

template<typename Tp>
class Accumulate<multiplies<Tp>> {
public:
    Tp operator()(const Tp& val, const Tp& x) const {
        //return qpow(val, x);
    }
};


template<typename Tp, typename Sequence = vector<Tp>,
    typename Calculate = plus<typename Sequence::value_type>,
    typename Accumulate = Accumulate<Calculate>>
class SegmentTree {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type size_type;
    typedef Sequence container_type;
    typedef Calculate value_calculate;
private:
    const value_type init_val;
    //懒标记
    container_type tag;
    //线段树
    container_type seg;
    Calculate cal;
    Accumulate acc;
public:
    explicit SegmentTree(size_type n, const_reference val = value_type())
        : init_val(val), tag(n << 2, val), seg(n << 2, val) {}

    explicit SegmentTree(const Sequence& s, const_reference val = value_type())
        : init_val(val), tag(s.size() << 2, val), seg(s.size() << 2, val) {
        size_type n = s.size();
        for(size_type i = 1; i <= n; ++i) {
            update(i, i, s[i]);
        }
    }

    template<typename InputIterator>
    explicit SegmentTree(InputIterator first, InputIterator last, const_reference val = value_type())
        : init_val(val), tag(distance(first, last) << 2, val),
          seg(distance(first, last) << 2, val) {
        for(size_type i = 1; first != last; ++i, ++first) {
            update(i, i, *first);
        }
    }

    // x, y is 1-indexed
    void update(size_type p, size_type r, const_reference val) {
        int n = seg.size() >> 2;
        if(p > r || r <= 0) return;
        update(1, 0, n - 1, p - 1, r - 1, val);
    }

    // x, y is 1-indexed
    value_type query(size_type p, size_type r) {
        int n = seg.size() >> 2;
        if(p > r || r <= 0) return init_val;
        return query(1, 0, n - 1, p - 1, r - 1);
    }
private:
    size_type left(size_type idx) { return idx << 1; }
    size_type right(size_type idx) { return idx << 1 | 1; }
    size_type mid(size_type p, size_type r) { return (p + r) >> 1; }
    // idx 线段树节点下标
    void update(size_type idx) {
        seg[idx] = cal(seg[left(idx)], seg[right(idx)]);
    }

    // 懒标记下沉, idx 线段树节点下标 [p, r] 维护区间 0-indexed
    void down(size_type idx, size_type p, size_type r) {
        if(tag[idx] == init_val) return;

        int q = mid(p, r);
        // 左维护区间下沉
        seg[left(idx)] = cal(seg[left(idx)], acc(q - p + 1, tag[idx]));
        tag[left(idx)] = cal(tag[left(idx)], tag[idx]);

        // 右维护区间下沉
        seg[right(idx)] = cal(seg[right(idx)], acc(r - q, tag[idx]));
        tag[right(idx)] = cal(tag[right(idx)], tag[idx]);

        tag[idx] = init_val;
    }

    //idx 线段树节点下标 [p, r] 维护区间, [x, y] 更新区间 0-indexed z 增量
    void update(size_type idx, size_type p, size_type r, size_type x, size_type y, const_reference val) {
        // 节点维护区间在更新区间范围内
        if(x <= p && r <= y) {
            seg[idx] = cal(seg[idx], acc(r - p + 1, val));
            tag[idx] = cal(tag[idx], val);
            return;
        }

        // 懒标记下沉
        down(idx, p, r);

        int q = mid(p, r);
        if(x <= q) {
            // 更新区间和左半维护区间存在交集
            update(left(idx), p, q, x, y, val);
        }

        if(y > q) {
            // 更新区间和右半维护区间存在交集
            update(right(idx), q + 1, r, x, y, val);
        }
        // 回溯
        update(idx);
    }

    value_type query(size_type idx, size_type p, size_type r, size_type x, size_type y) {
        // 节点维护区间在查询区间范围内
        if(x <= p && r <= y) return seg[idx];

        // 懒标记下沉
        down(idx, p, r);

        size_type q = mid(p, r);
        value_type res = init_val;
        if(x <= q) {
            // 查询区间和左半维护区间存在交集
            res = cal(res, query(left(idx), p, q, x, y));
        }

        if(y > q) {
            // 查询区间和右半维护区间存在交集
            res = cal(res, query(right(idx), q + 1, r, x, y));
        }
        return res;
    }
};
