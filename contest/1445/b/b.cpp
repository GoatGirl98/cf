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
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		std::cout << std::max(a + b, c + d) << std::endl;
	}
	return 0;
}