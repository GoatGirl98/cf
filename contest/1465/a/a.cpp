#include <bits/stdc++.h>
#define watch(x) std::cout << (#x) << " is " << (x) << std::endl
using LL = long long;

int main() {
	//freopen("in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int cas = 1;
	std::cin >> cas;
	while (cas--) {
		int n;
		std::string s;
		std::cin >> n >> s;
		int nn = n - 1;
		while (nn >= 0 && s[nn] == ')') --nn;
		std::cout << ((nn + 1) * 2 < n ? "Yes" : "No") << std::endl;
	}
	return 0;
}