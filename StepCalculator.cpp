#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
// #define int long long

int pri[128];
inline void init() {
    pri['('] = pri[')'] = -1;
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
    bool empty() {
        return s.size() == 0;
    }
    void refresh() {
        cur = 0;
    }
    void read() {
        do {
            getline(cin, s);
        } while (s.empty());
        refresh();
    }
    char nextChar() {
        if (cur == s.size())
            return 0;
        else
            return s[cur++];
    }
    int rest() {
        return s.size() - cur;
    }
    void preWork() {  // 初始格式化字符串
        string t;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ' || s[i] == '+' && (i == 0 || s[i - 1] == '(')) continue;
            if (!isdigit(s[i]) && pri[s[i]] == 0) return s = "", void();
            if (s[i] == '-' && (i == 0 || s[i - 1] == '(')) t.push_back('0');
            t.push_back(s[i]);
        }
        s = t;
    }
} s;

list<ll> dfs() {
    list<ll> re;
    stack<char> op;
    char c;
    while (c = s.nextChar()) {
    begin:
        if (c == '(')
            re.splice(re.end(), dfs());
        else if (c == ')')
            break;
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

inline string getShow2(const list<ll>& a) {  //  返回中缀表达式
    list<list<ll> > lists;
    for (ll i : a) {
        if (i > INF) {
            i -= INF;
            if (lists.empty()) return "";  // 异常返回
            list<ll> b = move(lists.back());
            lists.pop_back();
            if (lists.empty()) return "";  // 异常返回
            list<ll>& a = lists.back();
            if (pri[a.front()] < pri[i]) {
                a.front() = '(' + INF;
                a.push_front(i);
                a.push_back(')' + INF);
            }
            else
                a.front() = i;
            if (pri[b.front()] <= pri[i]) {
                b.front() = '(' + INF;
                b.push_front(i + INF);
                b.push_back(')' + INF);
            }
            else
                b.front() = i + INF;
            a.splice(a.end(), b);
        }
        else {
            lists.emplace_back(list<ll>{0, i});
        }
    }
    if (lists.size() != 1) return "";
    list<ll>& ans = lists.back();
    ans.pop_front();
    string re;
    for (auto it = ans.begin(); it != ans.end(); ++it) {
        ll i = *it;
        if (i > INF)
            re.push_back(char(i - INF));
        else if (i == 0 && (it == ans.begin() || *prev(it) == '(' + INF) && next(it) != ans.end() && *next(it) == '-' + INF)
            continue;
        else if (i < 0 && it != ans.begin() && *prev(it) != '(' + INF && ans.size() != 1) {
            re.push_back('(');
            re += to_string(i);
            re.push_back(')');
        }
        else
            re += to_string(i);
    }
    return re;
}

int cnt = 0;
string s0 = "";
inline void show2(const list<ll>& a) {  // 展示中缀表达式
    string s = getShow2(a);
    if (s != s0) {
        cout << cnt++ << '\t';
        cout << s << '\n';
        s0 = s;
    }
}

inline void show3(const list<ll>& a) {  // 展示后缀表达式（逆波兰式）
    for (const ll& i : a) {
        if (i > INF)
            cout << char(i - INF) << ' ';
        else
            cout << i << ' ';
    }
    cout << '\n';
}

inline void work() {
    s.read();
    s.preWork();
    if (s.empty()) {
        cout << "输入异常\n\n";
        return;
    }
    list<ll> a = dfs();
    cout << "逆波兰式：";
    show3(a);
    if (s.rest() != 0 || getShow2(a) == "") {
        cout << "输入异常\n\n";
        return;
    }
    cout << "步骤\t结果\n";
    cnt = 0;
    s0 = "";
    show2(a);
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (*it < INF) continue;
        char op = char(*it - INF);
        ll p = *prev(prev(it)), q = *prev(it);
        if (q == 0 && op == '/') {
            cout << "计算错误\n\n";
            return;
        }
        *it = cal(p, q, op);
        a.erase(prev(it));
        a.erase(prev(it));
        show2(a);
    }
}

signed main() {
    init();
    while (true) {
        work();
        cout << '\n';
    }

    return 0;
}

/*

((5+6)*2^3)^4-1*10/(3-1)

-1+(-2*3+4^9/2)+5*6*56/9-2^3*(1+2+12-114514/1919810)*((2024-2022)^(5-4)-(-3)*(-9))-3^9+(-3)^3*2

-1-(-2)*(-3/4-5)+(-3)+9

-1-(-(+(-1)))-(-1)*(-1)/(-1-1)

*/

