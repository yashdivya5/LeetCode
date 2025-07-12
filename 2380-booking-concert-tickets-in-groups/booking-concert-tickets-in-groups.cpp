#include <vector>
#include <algorithm>
using namespace std;

class BookMyShow {
    int n, m;
    vector<int> usedSeats;
    vector<long long> treeMax, treeSum;

    void build(int idx, int l, int r) {
        if (l == r) {
            treeMax[idx] = m;
            treeSum[idx] = m;
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        treeMax[idx] = m;
        treeSum[idx] = (long long)m * (r - l + 1);
    }

    void update(int idx, int l, int r, int row, int used) {
        if (l == r) {
            treeMax[idx] -= used;
            treeSum[idx] -= used;
            return;
        }
        int mid = (l + r) / 2;
        if (row <= mid)
            update(2 * idx, l, mid, row, used);
        else
            update(2 * idx + 1, mid + 1, r, row, used);
        treeMax[idx] = max(treeMax[2 * idx], treeMax[2 * idx + 1]);
        treeSum[idx] = treeSum[2 * idx] + treeSum[2 * idx + 1];
    }

    int queryGather(int idx, int l, int r, int maxRow, int k) {
        if (l > maxRow || treeMax[idx] < k) return -1;
        if (l == r) return l;
        int mid = (l + r) / 2;
        int res = queryGather(2 * idx, l, mid, maxRow, k);
        if (res != -1) return res;
        return queryGather(2 * idx + 1, mid + 1, r, maxRow, k);
    }

    long long querySum(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return treeSum[idx];
        int mid = (l + r) / 2;
        return querySum(2 * idx, l, mid, ql, qr) + querySum(2 * idx + 1, mid + 1, r, ql, qr);
    }

public:
    BookMyShow(int n, int m) : n(n), m(m), usedSeats(n, 0) {
        int size = 4 * n;
        treeMax.assign(size, 0);
        treeSum.assign(size, 0);
        build(1, 0, n - 1);
    }

    vector<int> gather(int k, int maxRow) {
        int row = queryGather(1, 0, n - 1, maxRow, k);
        if (row == -1) return {};
        int seat = usedSeats[row];
        usedSeats[row] += k;
        update(1, 0, n - 1, row, k);
        return {row, seat};
    }

    bool scatter(int k, int maxRow) {
        long long totalAvailable = querySum(1, 0, n - 1, 0, maxRow);
        if (totalAvailable < k) return false;

        for (int i = 0; i <= maxRow && k > 0; ++i) {
            int freeSeats = m - usedSeats[i];
            if (freeSeats == 0) continue;
            int toTake = min(k, freeSeats);
            usedSeats[i] += toTake;
            k -= toTake;
            update(1, 0, n - 1, i, toTake);
        }
        return true;
    }
};
