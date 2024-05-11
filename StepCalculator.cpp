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
    pri[0] = INF;
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

struct StringRead {
    string s;
    size_t cur = 0;
    bool empty(){
    	return s.size()==0;
	}
    void refresh() {
        cur = 0;
    }
    void read() {
        cin >> s;
        refresh();
    }
    char nextChar() {
        if (cur == s.size())
            return 0;
        else
            return s[cur++];
    }
} s;

list<ll> dfs() {
    list<ll> re;
    stack<char> op;
    char c;
    while (c = s.nextChar()) {
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
            while (c = s.nextChar()) {
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

inline void show2(const list<ll>& a) {  // 展示中缀表达式
    list<list<ll> > re;
    for (ll i : a) {
        if (i > INF) {
            i -= INF;
            list<ll> b = move(re.back());
            re.pop_back();
            list<ll>& a = re.back();
            if (pri[a.front()] < pri[i]) {
                a.front() = '(' + INF;
                a.push_front(i);
                a.push_back(')' + INF);
            }
            else a.front() = i;
            if (pri[b.front()] <= pri[i]) {
                b.front() = '(' + INF;
                b.push_front(i + INF);
                b.push_back(')' + INF);
            }
            else b.front() = i + INF;
            a.splice(a.end(), b);
        }
        else {
            re.emplace_back(list<ll>{0, i});
        }
    }
    list<ll>& ans = re.back();
    ans.pop_front();
    for (const ll& i : ans) {
        if (i > INF) cout << char(i - INF);
        else cout << i;
    }
    cout << '\n';
}

inline void show3(const list<ll>& a) {  // 展示后缀表达式（逆波兰式）
    for (const ll& i : a) {
        if (i > INF) cout << char(i - INF) << ' ';
        else cout << i << ' ';
    }
    cout << '\n';
}

inline void work(list<ll>& a) {
    cout << "步骤\t结果\n";
    cout << "0\t";
    show2(a);
    int cnt = 0;
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (*it < INF) continue;
        char op = char(*it - INF);
        ll p = *prev(prev(it)), q = *prev(it);
        *it = cal(p, q, op);
        a.erase(prev(it));
        a.erase(prev(it));
        cout << ++cnt << '\t';
        show2(a);
    }
}

signed main() {
    init();
    while (true) {
    	s.read();
    	list<ll> a = dfs();
    	work(a);
    	cout << '\n';
	}

    return 0;
}

/*

((5+6)*2^3)^4-1*10/(3-1)

1+(2*3+4^9/2)+5*6*56/9-2^3*(1+2+12-114514/1919810)*((2024-2022)^(5-4)+3*(0-9))-3^9-68

*/

