### [数值积分](https://sim.csp.thusaac.com/contest/37/problem/0)

按题意模拟即可

### [机器人饲养指南](https://sim.csp.thusaac.com/contest/37/problem/1)

因为没有限制天数，所以是裸的完全背包问题

```c++
#include <bits/stdc++.h>
using namespace std;
int dp[110][10010], n, m, w[110], v[110];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> v[i];
        w[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j >= w[i]) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i]] + v[i]);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[m][n];
}
```

### [模板展开](https://sim.csp.thusaac.com/contest/37/problem/2)

讨厌的大模拟

语句分为三种：直接赋值、间接赋值、输出

开头为`$`的是变量，直接赋值只需要在赋值时计算一次，间接赋值需要在每次后续使用时重新计算，为了防止间接赋值暴力`dfs`导致超时，需要记忆化

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007;
struct info{
    bool typ;
    int ans;
    string s, name;
}var[1010];
int opt, cnt;
unordered_map<string, int> mp;	// 记录变量的索引
unordered_set<string> st;	// 用于记忆化
int var_to_int(info&);
int str_to_int(string&);
void check_var(string& s) {	// 分配新变量
    if (mp.find(s) == mp.end()) {
        var[cnt].typ = true;
        var[cnt].ans = 0;
        var[cnt].name = s;
        mp.emplace(s, cnt++);
    }
}
int var_to_int(info& v) {	// 若是第1种或是搜索过的第2种变量, 直接返回, 否则递归计算
    if (v.typ || st.find(v.name) != st.end()) {
        return v.ans;
    }
	else {
        st.insert(v.name);
        return v.ans = str_to_int(v.s);
    }
}
int str_to_int(string& s) {
    string tmp;
	int l = 0, n = s.size(), r, ans = 0;
    while (l <= n) {
        for (r = l; r < n && s[r] != ' '; ++r);
        if (s[l] == '$') {
            tmp = s.substr(l + 1, r - l - 1);
            check_var(tmp);
            ans = (ans + var_to_int(var[mp[tmp]])) % mod;
        }
        else {
            ans = (ans + r - l) % mod;
        }
        l = r + 1;
    }
    return ans;
}
int main() {
    int _;
    cin >> _;
    string s, expr;
    while (_--) {
        cin >> opt >> s;
        check_var(s);
        if (opt == 1) {
			getline(cin, expr);
            expr.erase(expr.begin());
            var[mp[s]].ans = str_to_int(expr);
            var[mp[s]].typ = true;
        }
        else if (opt == 2) {
            getline(cin, expr);
            expr.erase(expr.begin());
            var[mp[s]].s = expr;
            var[mp[s]].typ = false;
        }
        else {
            cout << var_to_int(var[mp[s]]) << '\n';
        }
        st.clear();
    }
}
```

### [集体锻炼](https://sim.csp.thusaac.com/contest/37/problem/3)

很典的`ST`表加二分，考虑对所有以$l$起始的区间，由于$\gcd([l,r])$随$r$的增大呈**单调不增**，且不同的$\gcd$值最多有$\log(a_{l})$个，考虑进行二分

具体来说，对每个$\gcd$值$g$（初始时为$a_{l}$）进行二分，并用一个变量$last$记录上一次二分的结果（初始为$l-1$），在$[last,n]$内二分到一个**最右**的位置$r$，使得$\gcd[l,r]==g$，那么对答案的贡献就是$\begin{align}l\cross\frac{(r-last)(r+last+1)}2\cross g\end{align}$

不断进行这个操作并使$g\leftarrow\gcd([l,r+1]),last\leftarrow r$，直到$last==n$

一个以$l$起始的区间的计算是$O(\log n\times\log a_l)$的，遍历每一个$l$，最终复杂度为$O(n\log^2n)$

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
int st[1000010][22], n;
ll tmp, ans;
int query(int l, int r) {	// O(1)查区间gcd
    int x = __lg(r - l + 1);
    return __gcd(st[l][x], st[r - (1 << x) + 1][x]);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> st[i][0];
    }
    for (int j = 1; j <= 21; ++j) {	// 预处理ST表
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
    for (int i = 1; i <= n; ++i) {	// 遍历所有以i起始的区间
        int l = i, r, md, last = i, g;
        while (last <= n) {	// 此处的last为上文的last+1, 为了方便平移一个index
            g = query(i, l);
            r = n;
            while (l <= r) {
                md = l + r >> 1;
                if (query(i, md) == g) {
                    l = md + 1;
                }
                else {
                    r = md - 1;
                }
            }
            tmp = 1LL * (l - last) * (l + last - 1) >> 1;
            ans = (ans + (i * tmp % mod * g % mod)) % mod;
            last = l;
        }
    }
    cout << ans;
}