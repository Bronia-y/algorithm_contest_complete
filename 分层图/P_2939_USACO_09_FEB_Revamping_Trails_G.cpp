#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int N = 1e5 + 10;

struct nd {
    int d, x, cnt;
    bool operator<(const nd& r)const { return d > r.d; };
};

int n, m, k;

vector<PII> e[N];

int dist[N][25];
bool st[N][25];

void dj() {
    memset(dist, 0x3f, sizeof dist); dist[1][0] = 0;
    priority_queue<nd> q; q.emplace(0, 1, 0);
    while (q.size()) {
        auto[_, x, cnt] = q.top(); q.pop();
        if (st[x][cnt]) continue; st[x][cnt] = true;

        for (auto [w, y] : e[x]) {
            if (dist[x][cnt] + w < dist[y][cnt]) 
                dist[y][cnt] = dist[x][cnt] + w,
                q.emplace(dist[y][cnt], y, cnt);
            if (cnt + 1 <= k && dist[x][cnt] < dist[y][cnt + 1])
                dist[y][cnt + 1] = dist[x][cnt],
                q.emplace(dist[y][cnt + 1], y, cnt + 1);
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

    int ret = 1e9;
    for (int i = 0; i <= k; ++i) ret = min(ret, dist[n][i]);
    cout << ret << endl;
    return 0;
}