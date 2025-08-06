### [密码](https://sim.csp.thusaac.com/contest/35/problem/0)

```c++
#include <bits/stdc++.h>
using namespace std;
unordered_map<char, int> mp;
int main() {
    int n;
    string s;
    cin >> n;
    while (n--) {
        cin >> s;
        bool hasalp = false, hasdig = false, hasspe = false, cnt = true;
        for (auto c : s) {
            ++mp[c];
            if (isalpha(c)) {
                hasalp = true;
            }
            else if (isdigit(c)) {
                hasdig = true;
            }
            else {
                hasspe = true;
            }
            if (mp[c] > 2) {
                cnt = false;
            }
        }
        if (hasalp & hasdig & hasspe & cnt) {
            cout << 2 << '\n';
        }
        else if (hasalp & hasdig & hasspe & !cnt) {
            cout << 1 << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        mp.clear();
    }
}
```

### [字符串变换](https://sim.csp.thusaac.com/contest/35/problem/1)

```c++
#include <bits/stdc++.h>
using namespace std;
struct info {
    int cnt, len;
    string prelp, lp;
};
unordered_map<char, char> ff;
unordered_map<char, info> loop;
unordered_map<char, int> tmp;
string aa = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0), cout.tie(0);
    int n, m, k;
    string s, p;
    getline(cin, s);
    cin >> n;
    getchar();
    while (n--) {
        getline(cin, p);
        ff[p[1]] = p[2];
    }
    for (auto c : aa) {
        int cnt = 0;
        char cc = c;
        string lp;
        while (tmp.find(cc) == tmp.end()) {
            tmp.emplace(cc, cnt++);
            lp += cc;
            cc = ff.find(cc) == ff.end() ? cc : ff[cc];
        }
        loop[c] = {tmp[cc] - tmp[c], cnt - tmp[cc], lp.substr(0, lp.find(cc)), lp.substr(lp.find(cc))};
        tmp.clear();
    }
    cin >> m;
    while (m--) {
        cin >> k;
        string ans;
        ans += '#';
        for (int i = 1; i < s.size() - 1; ++i) {
            char c = s[i];
            auto tmp = loop[c];
            if (tmp.cnt > k) {
                ans += tmp.prelp[k];
            }
            else {
                ans += tmp.lp[(k - tmp.cnt) % tmp.len];
            }
        }
        ans += '#';
        cout << ans << '\n';
    }
}
```

### [补丁应用](https://sim.csp.thusaac.com/contest/35/problem/2)

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    bool flag, blk;
    int n, cnt = 0, NN, MM, nn, mm, nnmm = 0, i, cntold, cntnew, linecnt = 1, base = 0;
    string text, diff, oldblk, newblk, tmp, ans;
    cin >> n;
    getchar();
    while (n--) {
        getline(cin, tmp);
        text += tmp + '\n';
    }
    while (getline(cin, tmp)) {
        if (tmp[0] != '#')
            diff += tmp + '\n';
    }
    while (!diff.empty()) {
        blk = false;
        flag = true;
        tmp = diff.substr(0, diff.find('\n'));
        if (tmp[0] == '@' && tmp[1] == '@' && tmp[tmp.size() - 2] == '@' && tmp[tmp.size() - 1] == '@') {
            oldblk.clear();
            newblk.clear();
            cntold = cntnew = 0;
            ++cnt;
            blk = true;
            diff.erase(diff.begin(), diff.begin() + diff.find('\n') + 1);
            if (tmp[2] == ' ' && tmp[3] == '-' && tmp[4] >= '1' && tmp[4] <= '9') {
                NN = tmp[4] - '0';
                for (i = 5; isdigit(tmp[i]); ++i)
                    NN = NN * 10 + tmp[i] - '0';
                if (NN >= nnmm && tmp[i] == ',' && tmp[i + 1] >= '1' && tmp[i + 1] <= '9') {
                    MM = tmp[i + 1] - '0';
                    for (i = i + 2; isdigit(tmp[i]); ++i)
                        MM = MM * 10 + tmp[i] - '0';
                    if (tmp[i] == ' ' && tmp[i + 1] == '+' && tmp[i + 2] >= '1' && tmp[i + 2] <= '9') {
                        nn = tmp[i + 2] - '0';
                        for (i = i + 3; isdigit(tmp[i]); ++i)
                            nn = nn * 10 + tmp[i] - '0';
                        if (tmp[i] == ',' && tmp[i + 1] >= '1' && tmp[i + 1] <= '9') {
                            mm = tmp[i + 1] - '0';
                            for (i = i + 2; isdigit(i); ++i)
                                mm = mm * 10 + tmp[i] - '0';
                            tmp = diff.substr(0, diff.find('\n'));
                            while (!tmp.empty() && (tmp.size() < 4 || tmp[0] != '@' || tmp[1] != '@' || tmp[tmp.size() - 2] != '@' || tmp[tmp.size() - 1] != '@')) {
                                if (tmp[0] == '+') {
                                    ++cntnew;
                                    newblk += tmp.substr(1) + '\n';
                                } else if (tmp[0] == '-') {
                                    ++cntold;
                                    oldblk += tmp.substr(1) + '\n';
                                } else if (tmp[0] == ' ') {
                                    ++cntnew;
                                    ++cntold;
                                    newblk += tmp.substr(1) + '\n';
                                    oldblk += tmp.substr(1) + '\n';
                                } else {
                                    flag = false;
                                    break;
                                }
                                diff.erase(diff.begin(), diff.begin() + diff.find('\n') + 1);
                                tmp = diff.substr(0, diff.find('\n'));
                            }
                            if (flag && cntnew == mm && cntold == MM) {
                                int delta = text.find(oldblk, nnmm);
                                if (delta != -1) {
                                    while (base < delta) {
                                        ++linecnt;
                                        ans += text.substr(base, text.find('\n') + 1);
                                        base = text.find('\n', base) + 1;
                                    }
                                    if (abs(linecnt - NN) < MM) {
                                        nnmm = NN + MM;
                                        ans += newblk;
                                        for (int i = 0; i < MM; ++i) {
                                            ++linecnt;
                                            base = text.find('\n', base) + 1;
                                        }
                                    } else flag = false;
                                } else flag = false;
                            } else flag = false;
                        } else flag = false;
                    } else flag = false;
                } else flag = false;
            } else flag = false;
        }
        if (blk) {
            if (!flag)
                break;
        }
        else {
            diff.erase(diff.begin(), diff.begin() + diff.find('\n') + 1);
        }
    }
    if (!cnt || !flag) {
        cout << "Patch is damaged.\n";
    } else {
        while (base < text.size()) {
            ++linecnt;
            ans += text.substr(base, text.find('\n') + 1);
            base = text.find('\n', base) + 1;
        }
        cout << ans;
    }
}