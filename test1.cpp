#include <bits/stdc++.h>
using namespace std;


signed main(){
	list<list<int>> l{list<int>{1,2,3},list<int>{2,3,4}};
	list<int> a=move(l.back());
	a.back()=-1;
	cout<<l.back().size();
//	cout<<"\na: ";
//	for (int& i:a) cout<<i<<' ';
	
	return 0;
}
