### [移动](https://sim.csp.thusaac.com/contest/36/problem/0)

```c++
#include <bits/stdc++.h>
using namespace std;
int n, k, xx, yy, tmp, tmpx, tmpy;
string s;
int dir[4][2] {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int getmode(char c) {
    switch (c) {
        case 'f': return 0;
        case 'b': return 1;
        case 'l': return 2;
        case 'r': return 3;
    }
    return 4;
}
bool ck(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= n;
}
int main() {
    cin >> n >> k;
    while (k--) {
        cin >> xx >> yy >> s;
        for (auto c : s) {
            tmp = getmode(c);
            tmpx = xx + dir[tmp][0];
            tmpy = yy + dir[tmp][1];
            if (ck(tmpx, tmpy)) {
                xx = tmpx;
                yy = tmpy;
            }
        }
        cout << xx << ' ' << yy << endl;
    }
}
```

### [梦境巡查](https://sim.csp.thusaac.com/contest/36/problem/1)

```c++
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], b[100010], dif[100010], w[100010];
bool ck(int x) {
    for (int i = 1; i <= n; ++i) {
        if (x < a[i - 1]) {
            return false;
        }
        x = x - a[i - 1] + b[i];
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    int l = 0, r = 100000000, md;
    while (l <= r) {
        md = l + r >> 1;
        if (ck(md)) {
            r = md - 1;
        }
        else {
            l = md + 1;
        }
    }
    b[0] = w[0] = l;
    for (int i = 0; i <= n; ++i) {
        dif[i] += b[i] - a[i];
        dif[i + 1] += dif[i];
    }
    int mi = INT_MAX;
    for (int i = n; i; --i) {
        mi = min(mi, dif[i]);
        w[i] = w[0] + max(0, b[i] - mi);
    }
    for (int i = 1; i <= n; ++i) {
        cout << w[i] << ' ';
    }
}
```

### [缓存模拟](https://sim.csp.thusaac.com/contest/36/problem/2)

```c++
#include <bits/stdc++.h>
using namespace std;
unordered_set<int> hit[65540];
map<int, int> time_to_v[65540];
unordered_map<int, int> v_to_time[65540];
unordered_map<int, bool> dirt[65540];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, N, q, opt, x, grp, clk = 0;
    cin >> n >> N >> q;
    while (q--) {
        cin >> opt >> x;
        ++clk;
        grp = (x / n) % N;
        if (hit[grp].find(x) != hit[grp].end()) {
            // 命中, 将该块的访问时间改为现在, 若opt == 1将该块的是否修改改为true, 不输出任何东西
            time_to_v[grp].erase(v_to_time[grp][x]);
            time_to_v[grp][clk] = x;
            v_to_time[grp][x] = clk;
            if (opt) {
                dirt[grp][x] = true;
            }
        }
        else if (hit[grp].size() < n) { // 存在空行
            // 将该块的访问时间改为现在, 若opt == 1该块脏位为true, 否则false, 输出0 x
            hit[grp].insert(x);
            time_to_v[grp].erase(v_to_time[grp][x]);
            time_to_v[grp][clk] = x;
            v_to_time[grp][x] = clk;
            dirt[grp][x] = opt;
            cout << "0 " << x << '\n';
        }
        else {  // 需要替换
            // 将最早的块删除, 如果dirt为true, 则额外输出1 y
            // 然后插入x, 访问时间为现在, 脏位和opt一致, 输出0 x
            auto tmp = time_to_v[grp].begin();
            if (dirt[grp][tmp->second]) {
                cout << "1 " << tmp->second << '\n';
            }
            dirt[grp].erase(tmp->second);
            hit[grp].erase(tmp->second);
            hit[grp].insert(x);
            time_to_v[grp][clk] = x;
            v_to_time[grp][x] = clk;
            dirt[grp][x] = opt;
            time_to_v[grp].erase(tmp);
            cout << "0 " << x << '\n';
        }
    }
}
```