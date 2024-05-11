#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
// #define int long long

int pri[128];
inline void init() {
    pri['+'] = pri['-'] = 1;
    pri['*'] = pri['/'] = 2;
    pri['^'] = 3;
}

inline ll qpow(ll a, ll n) {
    ll re = 1;
    while (n) {
        if (n & 1) re *= a;
        a *= a;
        n >>= 1;
    }
    return re;
}

inline ll cal(ll a, ll b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return qpow(a, b);
    }
    return 0;
}

list<ll> dfs(int pre = 0) { // pre代表在最前面添加"("的个数
    list<ll> re;
    if (pre > 0) re.splice(re.end(), dfs(pre - 1));
    stack<char> op;
    char c;
    while (cin >> c) {
    begin:
        if (c == '(') re.splice(re.end(), dfs());
        else if (c == ')') break;
        else if (pri[c]) {
            while (!op.empty() && pri[op.top()] >= pri[c]) {
                re.push_back(op.top() + INF);
                op.pop();
            }
            op.push(c);
        }
        else {
            ll a = c - '0';
            while (cin >> c) {
                if (!isdigit(c)) {
                    re.push_back(a);
                    goto begin;
                }
                a = a * 10 + c - '0';
            }
            re.push_back(a);
        }
    }
    while (!op.empty()) {
        re.push_back(op.top() + INF);
        op.pop();
    }
    return re;
}

inline void show(list<ll>& a) {
    for (ll& i : a) {
        if (i > INF) cout << char(i - INF) << ' ';
        else cout << i << ' ';
    }
    cout << '\n';
}

inline void work(list<ll>& a) {
    // show(a);
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (*it < INF) continue;
        char op = char(*it - INF);
        ll p = *prev(prev(it)), q = *prev(it);
        *it = cal(p, q, op);
        a.erase(prev(it));
        a.erase(prev(it));
        // show(a);
    }
}

signed main() {
    init();
    list<ll> a = dfs(30);
    //	show(a);
    work(a);
    if (a.empty()) cout << 0;
    else show(a);

    return 0;
}

/*

5+6)*7^8)

*/

