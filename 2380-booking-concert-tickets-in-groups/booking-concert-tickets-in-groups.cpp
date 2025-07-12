#include <bits/stdc++.h>
using namespace std;
// random for Treap priorities
static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Treap for free-intervals in one row ---
struct TNode {
    int key, r;            // interval [key..r]
    int priority;
    TNode *left, *right;
    int maxLen;            // max interval length in subtree
    long long sumLen;      // total free seats in subtree
    TNode(int l, int rr)
      : key(l), r(rr),
        priority((int)(rng() & 0x7fffffff)),
        left(nullptr), right(nullptr)
    {
        maxLen = r - key + 1;
        sumLen = maxLen;
    }
};
inline int getMaxLen(TNode* t)    { return t ? t->maxLen  : 0; }
inline long long getSumLen(TNode* t){ return t ? t->sumLen : 0; }
static void treapUpdate(TNode* t) {
    if (!t) return;
    t->maxLen = t->r - t->key + 1;
    t->sumLen = t->maxLen;
    if (t->left) {
        t->maxLen = max(t->maxLen, t->left->maxLen);
        t->sumLen += t->left->sumLen;
    }
    if (t->right) {
        t->maxLen = max(t->maxLen, t->right->maxLen);
        t->sumLen += t->right->sumLen;
    }
}
static void treapSplit(TNode* t, int key, TNode*& l, TNode*& r) {
    if (!t) { l = r = nullptr; return; }
    if (t->key <= key) {
        treapSplit(t->right, key, t->right, r);
        l = t;
    } else {
        treapSplit(t->left,  key, l, t->left);
        r = t;
    }
    treapUpdate(t);
}
static TNode* treapMerge(TNode* a, TNode* b) {
    if (!a || !b) return a ? a : b;
    if (a->priority > b->priority) {
        a->right = treapMerge(a->right, b);
        treapUpdate(a);
        return a;
    } else {
        b->left  = treapMerge(a, b->left);
        treapUpdate(b);
        return b;
    }
}
static TNode* treapInsert(TNode* root, TNode* node) {
    if (!root) return node;
    if (node->priority > root->priority) {
        treapSplit(root, node->key, node->left, node->right);
        treapUpdate(node);
        return node;
    }
    if (node->key < root->key)
        root->left  = treapInsert(root->left,  node);
    else
        root->right = treapInsert(root->right, node);
    treapUpdate(root);
    return root;
}
static TNode* treapErase(TNode* root, int key) {
    if (!root) return nullptr;
    if (root->key == key) {
        TNode* t = treapMerge(root->left, root->right);
        delete root;
        return t;
    }
    if (key < root->key)
        root->left  = treapErase(root->left,  key);
    else
        root->right = treapErase(root->right, key);
    treapUpdate(root);
    return root;
}
// find the leftmost interval with length >= k
static TNode* treapFindFirstWithLen(TNode* root, int k) {
    if (!root || root->maxLen < k) return nullptr;
    if (root->left && root->left->maxLen >= k)
        return treapFindFirstWithLen(root->left, k);
    if (root->r - root->key + 1 >= k)
        return root;
    return treapFindFirstWithLen(root->right, k);
}
// get the leftmost interval (smallest key)
static TNode* treapGetMin(TNode* root) {
    TNode* cur = root;
    while (cur && cur->left) cur = cur->left;
    return cur;
}

// --- Segment Tree over rows ---
struct SegmentTree {
    int n;
    vector<int>        maxSeg;  // max consecutive free seats in this node's range
    vector<long long>  sumFree; // total free seats in this node's range
    SegmentTree(int _n, long long m): n(_n) {
        maxSeg.assign(4*n, 0);
        sumFree.assign(4*n,0);
        build(1, 0, n-1, m);
    }
    void build(int v, int l, int r, long long m) {
        if (l == r) {
            maxSeg[v] = (int)m;
            sumFree[v]= m;
        } else {
            int mid = (l+r)/2;
            build(v<<1, l,   mid, m);
            build(v<<1|1,mid+1,r,   m);
            pull(v);
        }
    }
    inline void pull(int v) {
        maxSeg[v]  = max(maxSeg[v<<1],    maxSeg[v<<1|1]);
        sumFree[v] = sumFree[v<<1] + sumFree[v<<1|1];
    }
    // point update row i
    void update(int v, int l, int r, int i, int mx, long long sm) {
        if (l==r) {
            maxSeg[v]=mx;
            sumFree[v]=sm;
        } else {
            int mid=(l+r)/2;
            if (i<=mid) update(v<<1,  l,   mid, i, mx, sm);
            else        update(v<<1|1, mid+1,r,   i, mx, sm);
            pull(v);
        }
    }
    void update(int i, int mx, long long sm){
        update(1,0,n-1,i,mx,sm);
    }
    // range max
    int queryMax(int v,int l,int r,int ql,int qr){
        if (qr<l||r<ql) return 0;
        if (ql<=l&&r<=qr) return maxSeg[v];
        int mid=(l+r)/2;
        return max(queryMax(v<<1, l,   mid,ql,qr),
                   queryMax(v<<1|1,mid+1,r,  ql,qr));
    }
    int queryMax(int l,int r){ return queryMax(1,0,n-1,l,r); }
    // range sum
    long long querySum(int v,int l,int r,int ql,int qr){
        if (qr<l||r<ql) return 0;
        if (ql<=l&&r<=qr) return sumFree[v];
        int mid=(l+r)/2;
        return querySum(v<<1, l,   mid,ql,qr)
             + querySum(v<<1|1,mid+1,r,  ql,qr);
    }
    long long querySum(int l,int r){ return querySum(1,0,n-1,l,r); }
    // find first row in [ql..qr] with maxSeg >= k
    int findGatherRow(int v,int l,int r,int ql,int qr,int k){
        if (qr<l||r<ql|| maxSeg[v]<k) return -1;
        if (l==r) return l;
        int mid=(l+r)/2;
        int res = findGatherRow(v<<1, l,   mid,ql,qr,k);
        if (res!=-1) return res;
        return findGatherRow(v<<1|1,mid+1,r, ql,qr,k);
    }
    int findGatherRow(int ql,int qr,int k){
        return findGatherRow(1,0,n-1,ql,qr,k);
    }
};

// --- Main Class ---
class BookMyShow {
    int n;
    long long m;
    vector<TNode*> rows;   // per-row Treap of free intervals
    SegmentTree st;
    int scatterRow;        // pointer to first row with any free seats
public:
    BookMyShow(int _n, int _m)
      : n(_n), m(_m),
        rows(_n,nullptr),
        st(_n, _m),
        scatterRow(0)
    {
        // initialize each row with one big free segment [0..m-1]
        for(int i=0;i<n;++i)
            rows[i] = new TNode(0, _m-1);
    }

    // allocate k consecutive seats in some row ≤ maxRow
    vector<int> gather(int k, int maxRow) {
        if (st.queryMax(0, maxRow) < k)
            return {};
        int r = st.findGatherRow(0, maxRow, k);
        // find the segment in row r
        TNode* seg = treapFindFirstWithLen(rows[r], k);
        int c = seg->key;
        int L = seg->key, R = seg->r;
        // remove that segment
        rows[r] = treapErase(rows[r], L);
        // put back any leftovers
        if (L < c)
            rows[r] = treapInsert(rows[r], new TNode(L, c-1));
        if (c + k <= R)
            rows[r] = treapInsert(rows[r], new TNode(c+k, R));
        // update segment tree
        st.update(r, getMaxLen(rows[r]), getSumLen(rows[r]));
        return {r, c};
    }

    // allocate any k seats (not necessarily consecutive) in rows [0..maxRow]
    bool scatter(int k, int maxRow) {
        if (st.querySum(0, maxRow) < k)
            return false;
        // advance scatterRow to next non-empty
        while (scatterRow < n && getSumLen(rows[scatterRow]) == 0)
            scatterRow++;
        int r = scatterRow;
        long long need = k;
        while (need > 0 && r <= maxRow) {
            long long avail = getSumLen(rows[r]);
            if (avail == 0) {
                r++;
                continue;
            }
            // take from the leftmost segment
            TNode* seg = treapGetMin(rows[r]);
            int L = seg->key, R = seg->r;
            long long len = R - L + 1;
            long long take = min(need, len);
            // erase it
            rows[r] = treapErase(rows[r], L);
            // if leftover on the right
            if (L + take <= R)
                rows[r] = treapInsert(rows[r], new TNode(L + take, R));
            // update ST
            st.update(r, getMaxLen(rows[r]), getSumLen(rows[r]));
            need -= take;
            if (getSumLen(rows[r]) == 0)
                r++;
        }
        scatterRow = r;
        return true;
    }
};
