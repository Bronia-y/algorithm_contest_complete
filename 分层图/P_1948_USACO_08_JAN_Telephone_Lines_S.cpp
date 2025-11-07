#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10, INF = 0x3f3f3f3f;

struct nd {
    int d, x, c;
    bool operator<(const nd r) const { return d > r.d; }
};

int n, m, k;
vector<PII> e[N];

int d[N][N];
bool st[N][N];

void dj() {
    memset(d, 0x3f, sizeof d); d[1][0] = 0;
    priority_queue<nd> q; q.emplace(0, 1, 0);
    while (q.size()) {
        auto [_, x, c]  = q.top(); q.pop();
        if (st[x][c]) continue; st[x][c] = true;

        for (auto& [w, y] : e[x]) {
            if (max(d[x][c], w) < d[y][c])
                d[y][c] = max(d[x][c], w),
                q.emplace(d[y][c], y, c);
            if (c + 1 < n && d[x][c] < d[y][c + 1])
                d[y][c + 1] = d[x][c],
                q.emplace(d[y][c + 1], y, c + 1);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        e[x].emplace_back(w, y);
        e[y].emplace_back(w, x);
    }

    dj();
    int ret = INF;
    for (int i = 0; i <= min(n - 1, k); ++i) ret = min(ret, d[n][i]);
    cout << (ret == INF ? -1 : ret) << endl;

    return 0;
}