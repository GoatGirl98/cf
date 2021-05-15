#pragma once
#include <bits/stdc++.h>
using LL = long long;

namespace int128 {
__int128 read(){
	__int128 x = 0;
	bool negetive = false;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') negetive = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return negetive ?  -x : x;
}

void printS(__int128 x){
	if (x > 9) printS(x / 10);
	putchar(x % 10 + '0');
}
void print(__int128 x){ 
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	printS(x);
}
} // namespace int128

int powMod(int x, int n, int p) {
	int r = 1;
	while (n) {
		if (n&1) r = 1LL * r * x % p;
		n >>= 1; x = 1LL * x * x % p;
	}
	return r;
}
// 求逆 0 < a < p and gcd(a,p) = 1，单次 p 为奇素数时，请使用 powMod(a, p - 2, p)
// 猜想复杂度为 $O(\log^2 p)$，已知上界 O(\sqrt{N})

int inv(int a, int p){
	return a == 1 ? 1 : 1LL * (p - p / a) * inv(p % a, p) % p;
}
// O(n) 预处理全部逆元
std::vector<int> initInv(int N, int M) {
	std::vector<int> inv(N);
	inv[1] = 1;
	for (int i = 2; i < N; ++i) inv[i] = 1LL * (M - M / i) * inv[M % i] % M;
	return inv;
}

// 快速计算 gcd，效率稍微比 std::gcd 快
LL gcd(LL a, LL b) {
	if (!a || !b) return a | b;
	unsigned shift = __builtin_ctzll(a | b);
	a >>= __builtin_ctzll(a);
	do {
		b >>= __builtin_ctzll(b);
		if (a > b) std::swap(a, b);
		b -= a;
	} while (b);
	return a << shift;
}
// 参考 https://cp-algorithms.com/algebra/euclid-algorithm.html

// ax + by = gcd(a,b)
template<typename T>
std::tuple<T, T, T> exGcd(T a, T b) {
	if (b == 0) return {a, 1, 0};
	auto [d, y, x] = exGcd(b, a % b);
	return {d, x, y - a / b * x};
}

// O(\log n) 计算 \displaystyle \sum_{i = 0}^{n - 1} \lfloor \frac{a \cdot i + b}{m} \rfloor
LL floorSum(int n, int m, int a, int b) {
	LL r = 0;
	if (a >= m) {
		r += 1LL * a / m * (n - 1) * n / 2;
		a %= m;
	}
	if (b >= m) {
		r += 1LL * b / m * n;
		b %= m;
	}
	int yMax = (1LL * a * n + b) / m;
	if (yMax == 0) return r;
	r += 1LL * (n - 1) * yMax;
	r -= floorSum(yMax, a, m, m - b - 1);
	return r;
}
// 模板例题：https://atcoder.jp/contests/practice2/tasks/practice2_c

// \sum_{\sum c_i x_i = m} \frac{(\sum x_i)!}{\prod (x_i !)}
int sumNum(const std::vector<int> &c, int m, int M) {
	std::vector<int> dp(m + 1);
	dp[0] = 1;
	for (int i = 1; i <= m; ++i) {
		for (auto x : c) if (x <= i) {
			dp[i] += dp[i - x];
			if (dp[i] >= M) dp[i] -= M;
		}
	}
	return dp[m];
}
// 解释：https://dna049.com/classicalCombination/

// 每次可选择 n 减一 或 m 加一，使得 m 是 n 的倍数的最小次数
int decInc(int n, int m) {
	if (n > m) return n - m;
	int ans = n - 1;
	// 让 n 变成 i，那么结果就是 n - i + (m % i ? i - m % i : 0) <= n - m % i
	// 注意到 m % i = m - m / i * i 因此可以用数论分块技术加速
	for (int i = 1; i <= n; i = m / (m / i) + 1) {
		ans = std::min(ans, n - m % i);
	}
	// 再特判一下 m % i == 0 的情况
	for (int i = 1; i <= n && i * i <= m; ++i) if (m % i == 0) {
		ans = std::min(ans, n - i);
		if (m / i <= n) ans = std::min(ans, n - m / i);
	}
	return ans;
}

// n 个集合中选 k 个，二进制为 1 的表示选择
void GospersHack(int n, int k) {
	int cur = (1 << k) - 1;
	while (!(cur >> n)) {
		// do something
		int lb = __builtin_ctz(cur);
		int r = cur + (1 << lb);
		cur = ((r ^ cur) >> 2 + lb) | r;
	}
}

void GospersHackS(int n, int k) {
	int cur = (1 << k) - 1;
	while (!(cur >> n)) {
		// do something
		int lb = cur & -cur;
		int r = cur + lb;
		cur = (((r ^ cur) >> 2) / lb) | r;
	}
}


// 一般情况下 N < 1e6, M 必须是一个小于 INT_MAX 的素数
namespace Binom {
int N = 0, M = 1e9 + 7;
std::vector<int> fac, ifac;
void setMod(int m) {
	M = m;
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1LL * fac[i - 1] * i % M;
	ifac[N - 1] = powMod(fac[N - 1], M - 2, M);
	for (int i = N - 1; i; --i) ifac[i - 1] = 1LL * ifac[i] * i % M;
}
// 请确保 n < m，否则无法保证后面的正确性
void init(int n, int m = M) {
	N = n;
	fac.resize(N);
	ifac.resize(N);
	setMod(m);
}
// 需要预处理小于 n 的所有值！
int binom(int n, int k) {
	if (n < 0 || n < k) return 0;
	return 1LL * fac[n] * ifac[k] % M * ifac[n - k] % M;
}
// 一般说来需要预处理出小于 M 的所有值，且 M 是素数！
int lucas(int n, int k) {
	int r = 1;
	while (n && k) {
		int np = n % M, kp = k % M;
		if (np < kp) return 0;
		r = 1LL * r * binom(np, kp) % M;
		n /= M; k /= M;
	}
	return r;
}
} // namespace Binom
// 模板例题：https://www.luogu.com.cn/problem/P3807

// 模固定数阶乘 O(M) 编译时间，$O(sqrt(\sqrt{M}))$ 单次操作

// 例题：https://vjudge.net/problem/LibreOJ-170

// 编译示例：g++ main.cpp -O2 -std=c++17 -fconstexpr-loop-limit=12345678 -fconstexpr-ops-limit=1234567890

// 任意模素数 min_25 求阶乘 $O(\sqrt{n} \log n)$

// 例题：https://www.luogu.com.cn/problem/solution/P5282

namespace Stirling {
const int N = 1e3 + 2, M = 1e9 + 7;
std::vector<std::vector<int>> S1(N), S2(N);
void init() {
	S1[0] = {1, 0};
	for (int i = 1; i < N; ++i) {
		S1[i].resize(i + 2);
		for (int j = 1; j <= i; ++j) {
			S1[i][j] = (1LL * S1[i - 1][j] * (i - 1) + S1[i - 1][j - 1]) % M;
		}
	}
	S2[0] = {1, 0};
	for (int i = 1; i < N; ++i) {
		S2[i].resize(i + 2);
		for (int j = 1; j <= i; ++j) {
			S2[i][j] = (1LL * S2[i - 1][j] * j + S2[i - 1][j - 1]) % M;
		}
	}
}
} // namespace Stirling
// 模板例题：https://www.luogu.com.cn/problem/P5408
// 模板例题：https://www.luogu.com.cn/problem/P5395


// 注意这里的 nthPrime 以 1 开始编号（其它地方以 0 开始）！即 p[1] = 2
namespace Prime {
// O(\sqrt{N}) 最基本的单次素数判断
bool isPrime(LL n) {
	if (n == 2) return true;
	if (n == 1 || n % 2 == 0) return false;
	for (LL i = 3; i * i <= n; i += 2){
		if (n % i == 0) return false;
	}
	return true;
}

// 预处理判断所有素数
const int N = 1e7 + 2;
bool isp[N];
// 此算法复杂度为 O(N \log \log N)，实测 N < 1e9 时是最快的
std::vector<int> initPrime() {
	std::vector<int> p{0, 2};
	isp[2] = true;
	for (int i = 3; i < N; i += 2) isp[i] = true;
	int sq = int(std::sqrt(N + 0.1)) | 1;
	for (int i = 3; i <= sq; i += 2) if (isp[i]) {
		p.emplace_back(i);
		for (int j = i * i; j < N; j += i << 1) isp[j] = false;
	}
	for (int i = sq + 2; i < N; i += 2) if (isp[i]) p.emplace_back(i);
	return p;
}
// 此算法是 $O(N)$ 的，但实测不如上面算法快。
std::vector<int> initPrimeS() { // 放在此处仅供记录。
	std::vector<int> p{0, 2};
	isp[2] = true;
	for (int i = 3; i < N; i += 2) isp[i] = true;
	for (int i = 3; i < N; i += 2) {
		if (isp[i]) p.emplace_back(i);
		for (int j = 2, t = (N - 1) / i + 1; j < p.size() && p[j] < t; ++j) { // 用除号是防止溢出
			isp[i * p[j]] = false;
			// 不要下面的一步的话，复杂度 O(nloglogn), 但是不用除法，常数小
			if (i % p[j] == 0) break;
		}
	}
	return p;
}

// 计算 pi(x)，理论：https://dna049.com/computationOfPiX
// 这里预处理 N = 1e7, M = 7 是最好的（预处理 200ms）。
// 如果 x 特别大，例 1e13 < x < 1e15，建议 N = 1e8, M = 8（预处理耗时很大，2s）
const int M = 7; // 请不要超过 8，M = 9 已经没有什么意义了。
int pi[N];
std::vector<int> p;
std::vector<std::vector<int>> phi(M + 1);
void init() {
	p = initPrime();
	pi[2] = 1;
	for (int i = 3; i < N; ++i) {
		pi[i] = pi[i - 1];
		if (isp[i]) ++pi[i];
	}
	std::vector<int> sz(M + 1, 1);
	for (int i = 1; i <= M; ++i) sz[i] = p[i] * sz[i - 1];
	phi[0] = {1}; // 注意这里 phi[0] 本质是无意义的
	// 对本质逻辑 phi[j][i] = phi[j][i - 1] - phi[j / p[i]][i - 1]; 的细节和空间优化
	for (int i = 1; i <= M; ++i) {
		phi[i].resize(sz[i]);
		for (int j = 0; j < p[i]; ++j) {
			for (int k = 0, jsz = j * sz[i - 1]; k < sz[i - 1]; ++k) {
				phi[i][jsz + k] = j * phi[i - 1].back() + phi[i - 1][k];
			}
		}
		for (int k = 0; k < sz[i - 1]; ++k) {
			for (int j = 0, kp = k * p[i]; j < p[i]; ++j) {
				phi[i][kp + j] -= phi[i - 1][k];
			}
		}
	}
}
LL primepi(LL x);
LL primephi(LL x, int s) {
	if (s <= M) return (x / phi[s].size()) * phi[s].back() + phi[s][x % phi[s].size()];
	if (x / p[s] <= p[s]) return primepi(x) - s + 1;
	if (x / p[s] / p[s] <= p[s] && x < N) {
		int s2x = pi[(int)(std::sqrt(x + 0.2))];
		LL ans = pi[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
		for (int i = s + 1; i <= s2x; ++i) {
			ans += pi[x / p[i]];
		}
		return ans;
	}
	return primephi(x, s - 1) - primephi(x / p[s], s - 1);
}
LL primepi(LL x) {
	if (x < N) return pi[x];
	int ps2x = primepi(int(std::sqrt(x + 0.2)));
	int ps3x = primepi(int(std::cbrt(x + 0.2)));
	LL ans = primephi(x, ps3x) + 1LL * (ps2x + ps3x - 2) * (ps2x - ps3x + 1) / 2;
	for (int i = ps3x + 1, ed = ps2x; i <= ed; ++i) {
		ans -= primepi(x / p[i]);
	}
	return ans;
}

// 动态规划版 O(\frac{n}{\log n}) 计算 pi(x)，x < 10^12
LL primepiS(LL n) {
	int rn = std::sqrt(n + 0.2);
	std::vector<LL> R(rn + 1);
	for (int i = 1; i <= rn; ++i) R[i] = n / i - 1;
	int ln = n / (rn + 1) + 1;
	std::vector<LL> L(ln + 1);
	for (int i = 1; i <= ln; ++i) L[i] = i - 1;
	for (int p = 2; p <= rn; ++p) {
		if (L[p] == L[p - 1]) continue;
		for (int i = 1, tn = std::min(n / p / p, LL(rn)); i <= tn; ++i) {
			R[i] -= (i <= rn / p ? R[i * p] : L[n / i / p]) - L[p - 1];
		}
		for (int i = ln; i / p >= p; --i) {
			L[i] -= L[i / p] - L[p - 1];
		}
	}
	return R[1];
}

// 查看 (s - n, s] (请保证区间较小）内每个数是否为素数，确保 p.back() * p.back() >= r
std::vector<int> seive(LL s, int n) { // O(N log s)
	std::vector<int> isP(n, 1); // isP[i] = 1 表示 s - i 是素数
	for (int i = 1; 1LL * p[i] * p[i] <= s; ++i) {
		for (int j = s % p[i]; j < n; j += p[i]) isP[j] = 0;
	}
	return isP;
}

// 使用前先初始化，返回第 n 个素数，从 1 开始标号
LL nthPrime(LL n) { // Newton 梯度法
	if (n < p.size()) return p[n];
	LL ans = n * log(n), err = log(n) / log(10);
	LL m = primepi(ans);
	while (m < n || m > n + err) {
		ans += (n - m) / (log(m) - 1) * log(m) * log(m);
		m = primepi(ans);
	}
	int sn = std::sqrt(N);
	while (1) {
		auto isP = seive(ans, sn);
		for (int i = 0; i < sn; ++i) if (isP[i]) {
			if (m-- == n) return ans - i;
		}
		ans -= sn;
	}
} // 原理：https://dna049.com/nthPrimeNumber/

} // namespace Prime

// 单次求 Euler 函数
LL getPhi(LL n) {
	if (n % 2 == 0) n /= 2;
	LL r = n;
	while (n % 2 == 0) n /= 2;
	for (LL i = 3; i * i <= n; i += 2) {
		if (n % i  == 0) {
			r = r / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) r = r / n * (n - 1);
	return r;
}

// O(N \log \log N) 预处理 Euler 函数（不推荐）
std::vector<int> initPhiS(int N) {
	std::vector<int> phi(N);
	for (int i = 1; i < N; i += 2) phi[i] = i;
	for (int i = 2; i < N; i += 2) phi[i] = i >> 1;
	for (int i = 3; i < N; i += 2) {
		if (phi[i] != i) continue;
		for (int j = i; j < N; j += i) phi[j] = phi[j] / i * (i - 1);
	}
	return phi;
}

// 函数 O(N) 预处理 Euler 函数
std::vector<int> initPhi(int N) {
	std::vector<int> phi(N), p{0, 2};
	for (int i = 1; i < N; i += 2) phi[i] = i;
	for (int i = 2; i < N; i += 2) phi[i] = i >> 1;
	for (int i = 3; i < N; i += 2) {
		if (phi[i] == i) p.emplace_back(i), --phi[i];
		for (int j = 2, t = (N - 1) / i + 1; j < p.size() && p[j] < t; ++j) {
			if (i % p[j] == 0) {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
			phi[i * p[j]] = phi[i] * (p[j] - 1);
		}
	}
	for (int i = 2; i < N; i += 4) phi[i] = phi[i >> 1];
	for (int i = 4; i < N; i += 4) phi[i] = phi[i >> 1] << 1;
	return phi;
}

// 单次求 Mobius 函数（完全类似于单次欧拉函数）。
int getMu(LL n){
	if (n % 4 == 0) return 0;
	int r = (n % 2 ? 1 : -1);
	if (n % 2 == 0) n /= 2;
	for (LL i = 3; i * i <= n; i += 2){
		if (n % i == 0) {
			n /= i;
			if (n % i == 0) return 0;
			r = -r;
		}
	}
	return n > 1 ? -r : r;
}

//  O(n log n) 预处理 Mobius 函数
std::vector<int> initMuS(int N) {
	std::vector<int> mu(N);
	mu[1] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = i * 2; j < N; j += i) {
			mu[j] -= mu[i];
		}
	}
	return mu;
}

// O(n) 预处理版本 Mobius 函数 
std::vector<int> initMu(int N) {
	std::vector<int> mu(N), p{0, 2};
	for (int i = 1; i < N; i += 2) mu[i] = i;
	for (int i = 3; i < N; i += 2) {
		if (mu[i] == i) mu[i] = -1, p.emplace_back(i);
		for (int j = 2, t = (N - 1) / i + 1; j < p.size() && p[j] < t; ++j) {
			if (i % p[j] == 0) {
				mu[i * p[j]] = 0;
				break;
			}
			mu[i * p[j]] = -mu[i];
		}
	}
	for (int i = 2; i < N; i += 4) mu[i] = -mu[i >> 1];
	return mu;
}

// min25 筛法 O(n^{\frac{2}{3}}) 求 Euler 函数前缀和 以及 Mobius 函数（绝对值）前缀和
namespace min25 {
const int N = 5e6 + 2;

// Euler 函数前缀和
std::vector<LL> sumPhi(N);
std::unordered_map<LL, LL> mpPhi;
void initSumPhi() {
	auto phi = initPhi(N);
	for (int i = 1; i < N; ++i) sumPhi[i] = sumPhi[i - 1] + phi[i];
}
LL getSumPhi(LL n) {
	if (n < N) return sumPhi[n];
	if (mpPhi.count(n)) return mpPhi[n];
	LL r = (n + 1) * n / 2;
	for (LL i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		r -= (j - i + 1) * getSumPhi(n / i);
	}
	return mpPhi[n] = r;
}

// Mobius 函数（绝对值）前缀和
std::vector<int> mu(N), sumMu(N);
std::unordered_map<LL, int> mpMu;
void initSumMu() {
	mu = initMu(N);
	for (int i = 1; i < N; ++i) sumMu[i] = sumMu[i - 1] + mu[i];
}
// 当答案超过 int 时，n 已经大到没法计算了，因此可认为返回值为 int。
int getSumMu(LL n) {
	if (n < N) return sumMu[n];
	if (mpMu.count(n)) return mpMu[n];
	LL r = 1;
	for (LL i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		r -= (j - i + 1) * getSumMu(n / i);	
	}
	return mpMu[n] = r;
}
//  Mobius 函数绝对值前缀和
LL getAbsSum(LL n) { // Q(n) = Q(n-1) + |mu(n)|
	LL r = 0;
	for (LL i = 1; i * i < n; ++i) {
		r += mu[i] * (n / i / i);
	}
	return r;
}
} // namespace min25
// 模板例题：https://www.luogu.com.cn/problem/P4213

// O(N) 预处理所有数的最小素因子
std::vector<int> spf(int N) {
	std::vector<int> sp(N), p{0, 2};
	for (int i = 2; i < N; i += 2) sp[i] = 2;
	for (int i = 1; i < N; i += 2) sp[i] = i;
	for (int i = 3; i < N; i += 2) {
		if (sp[i] == i) p.emplace_back(i);
		for (int j = 2; j < p.size() && p[j] <= sp[i] && i * p[j] < N; ++j) {
			sp[i * p[j]] = p[j]; // 注意到sp只被赋值一次
		}
	}
	return sp;
}

// O(N) 预处理所有数的(是否算重)素因子个数
std::pair<std::vector<int>, std::vector<int>> npf(int N) {
	std::vector<int> np(N, 1), nps(N, 1), p{0, 2};
	nps[0] = nps[1] = 0;
	np[0] = np[1] = 0;
	for (int i = 3; i < N; i += 2) {
		if (nps[i] == 1) p.emplace_back(i);
		for (int j = 2, t; j < p.size() && (t = i * p[j]) < N; ++j) {
			nps[t] = nps[i] + 1;
			np[t] = np[i];
			if (i % p[j] == 0) break;
			++np[t];
		}
	}
	for (int i = 2; i < N; i += 4) np[i] = np[i >> 1] + 1;
	for (int i = 4; i < N; i += 4) np[i] = np[i >> 1];
	for (int i = 2; i < N; i += 2) nps[i] = nps[i >> 1] + 1;
	return {np, nps};
}

// 获取全部不同素因子
std::vector<int> factor(int n, const std::vector<int> &sp) {
	std::vector<int> ans;
	while (n > 1) {
		int pn = sp[n];
		ans.emplace_back(pn);
		while (n % pn == 0) n /= pn;
	}
	return ans;
}
// 获取全部素因子
std::vector<std::pair<int, int>> Factor(int n, const std::vector<int> &sp) {
	std::vector<std::pair<int, int>> ans;
	while (n > 1) {
		int pn = sp[n], cnt = 0;
		while (n % pn == 0) n /= pn, ++cnt;
		ans.emplace_back(pn, cnt);
	}
	return ans;
}

// 返回最小原根，无的话返回 0
int primitiveRoot(int n, const std::vector<int> &sp) {
	if (n < 2) return 0;
	if (n == 2 || n == 4) return n - 1;
	if (n % 4 == 0) return 0;
	int n2 = n % 2 == 0 ? n / 2 : n;
	int pn = sp[n2];
	while (n2 % pn == 0) n2 /= pn;
	if (n2 != 1) return 0;
	auto fp = factor(pn - 1, sp);
	auto check = [&](int i) {
		for (auto x : fp) {
			if (powMod(i, (pn - 1) / x, pn) == 1) return false;
		}
		return true;
	};
	int ans = 2;
	while (!check(ans)) ++ans;
	n2 = n % 2 == 0 ? n / 2 : n;
	if (n2 != pn) {
		int m = n2 / pn * (pn - 1);
		auto fm = factor(m, sp);
		for (auto x : fp) {
			if (powMod(ans, m / x, m) == 1) {
				ans += pn;
				break;
			}
		}
	}
	if (n2 != n && (ans % 2 == 0)) ans += n2;
	return ans;
}
// 返回所有原根，若无返回空
std::vector<int> primitiveRootAllS(int n, const std::vector<int> &sp) {
	int g = primitiveRoot(n, sp);
	if (g == 0) return {};
	if (n == 2 || n == 4) return {n - 1};
	int n2 = n & 1 ? n : n / 2;
	int pn = sp[n2], m = n2 / pn * (pn - 1), now = g;
	std::vector<int> ans{g};
	for (int i = 2; i < m; ++i) {
		now = 1LL * now * g % n;
		if (std::gcd(i, m) == 1) ans.emplace_back(now);
	}
	std::sort(ans.begin(), ans.end());
	return ans;
}

// 返回所有原根，若无返回空
std::vector<int> primitiveRootAll(int n, const std::vector<int> &sp) {
	if (n < 2) return {};
	if (n == 2 || n == 4) return {n - 1};
	if (n % 4 == 0) return {};
	int n2 = n % 2 == 0 ? n / 2 : n, pn = sp[n2];
	while (n2 % pn == 0) n2 /= pn;
	if (n2 != 1) return {};
	int m = (n & 1 ? n : n / 2) / pn * (pn - 1);
	std::vector<int> vis(n, -1), ans;
	for (int i = 2; i < n; ++i) if (vis[i] == -1 && std::gcd(i, n) == 1) {
		bool flag = true;
		int now = 1;
		for (int j = 1; j < m; ++j) {
			now = 1LL * now * i % n;
			if (now == 1) {
				flag = false;
				break;
			}
			if (std::gcd(j, m) == 1) vis[now] = i;
			else vis[now] = 0;
		}
		if (flag) { // 此时 i 必然是最小原根
			for (int j = 0; j < n; ++j) if (vis[j] == i) {
				ans.emplace_back(j);
			}
			return ans;
		}
	}
	return {};
} // 模板例题：https://www.luogu.com.cn/problem/P6091

// 大素数 Miller-Rabin 概率判别法 和 大整数的最 大/小 因子分解
namespace PollardRho {
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
LL powModll(LL x, LL n, LL p) {
	LL r = 1;
	while (n) {
		if (n&1) r = __int128(r) * x % p;
		n >>= 1; x = __int128(x) * x % p;
	}
	return r;
}
// 1 < a < n，若 n 是素数，那么 a^(n - 1) = 1 mod n
// m - 1 = m * 2 ^ t，返回 false 表示判断失败
bool witness(LL a, LL n, LL m, int t) {
	LL x = powModll(a, m, n);
	if (x == 1 || x == n - 1) return false;
	while (t--) {
		x = __int128(x) * x %  n;
		if (x == n - 1) return false;
	}
	return true;
}
const int TIMES = 52;
bool rabin(LL n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	LL m = n - 1;
	int t = __builtin_ctzll(m);
	m >>= t;
	for (int cnt = 0; cnt < TIMES; ++cnt) {
		LL a = rnd() % (n - 1) + 1;
		if (witness(a, n, m, t)) return false;
	}
	return true;
}
LL pollardrho(LL n) {
	LL x = 0, y = 0, z = 1, i = 1, k = 2, c = rnd() % (n - 1) + 1;
	while (true) {
		x = (__int128(x) * x + c) % n;
		z = __int128(y - x + n) * z % n;
		// 累计 gcd 一次计算！太猛了啊 茶茶白
		if (++i == k) {
			LL d = std::__gcd(z, n);
			if (d > 1) return d;
			y = x;
			if (k > n) return n;
			k <<= 1;
		}
	}
}
LL spf(LL n) {
	if (rabin(n) || n == 1) return n;
	LL d = n;
	while (d == n) d = pollardrho(n);
	return std::min(spf(d), spf(n / d));
}
LL gpf(LL n, LL mxf = 1) {
	if (rabin(n)) return n;
	if (n <= mxf) return 1;
	LL d = n;
	while (d == n) d = pollardrho(n);
	LL res = gpf(d, mxf);
	return std::max(res, gpf(n / d, std::max(res, mxf)));
}
} // namespace PollardRho

// 中国剩余定理：x = ai mod mi, m_i > 0, 0 <= a_i < m_i
std::pair<LL, LL> crt2(LL a1, LL m1, LL a2, LL m2){
	auto [d, t1, t2] = exGcd(m1, m2);
	assert((a2 - a1) % d == 0);
	LL m = m1 / d * m2;
	LL ans = (a1 + (a2 - a1) / d * t1 % m2 * m1) % m;
	return std::make_pair(ans < 0 ? ans + m: ans, m);
}
std::pair<LL, LL> crt(const std::vector<std::pair<LL, LL>> &a){
	auto ans = a[0];
	for (int i = 1; i < a.size(); ++i) {
		ans = crt2(ans.first, ans.second, a[i].first, a[i].second);
	}
	return ans;
}
// 模板例题：https://www.luogu.com.cn/problem/P1495

// 离散对数：返回最小的 x 使得 a^x = b mod p，p 为素数，无解输出 -1。
int babyStepGiantStep(int a, int b, int p) {
	a %= p, b %= p;
	if (a == 0) return b % p ? -1 : 1;
	if (b == 1) return 0;
	int cnt = 0, t = 1;
	for (int g = std::gcd(a, p); g != 1; g = std::gcd(a, p)) {
		if (b % g) return -1;
		p /= g, b /= g, t = 1LL * t * (a / g) % p;
		++cnt;
		if (b == t) return cnt;
	}
	std::map<int, int> mp;
	int m = std::sqrt(p + 0.1) + 1;
	int base = b;
	for (int i = 0; i != m; ++i) {
		mp[base] = i;
		base = 1LL * base * a % p;
	}
	base = powMod(a, m, p);
	for (int i = 1; i <= m + 1; ++i) {
		t = 1ll * t * base % p;
		if (mp.count(t)) return (1LL * i * m - mp[t] + cnt) % p;
	}
	return -1;
}
// 模板例题：https://www.luogu.com.cn/problem/P3846

// 模开方：返回 x 使得 x^2 = a mod p, 无解输出 -1。复杂度 $O(\log^2 p)$
int sqrtModp(int a, int p) { // p 为素数，0 <= a < p < INT_MAX。
	if (a == 0 || p == 2) return a;
	auto pow = [p](int x, int n) {
		int r = 1;
		while (n) {
			if (n&1) r = 1LL * r * x % p;
			n >>= 1; x = 1LL * x * x % p;
		}
		return r;
	};
	int q = (p - 1) / 2;
	if (pow(a, q) != 1) return -1;
	if (q & 1) return pow(a, (q + 1) / 2);
	int b; // 寻找一个非二次剩余
	std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
	while (pow(b = rnd() % (p - 1) + 1, q) == 1);
	int c = __builtin_ctzll(q);
	q >>= c; // p - 1 = q << (c + 1)
	b = pow(b, q);
	int x = pow(a, (q + 1) / 2), t = pow(a, q);
	// 始终保持 x^2 = a t, t^{2^c} = 1, b^{2^c} = -1
	while (t != 1) {
		// 返回最小的 r 使得 u^{2^r} = -1 
		int cc = [p](int u) {
			int r = 0;
			while ((u = 1LL * u * u % p) != 1) ++r;
			return r;
		}(t);
		int d = pow(b, 1LL << (c - cc - 1)); // d^{2^{cc + 1}} = -1
		// (xd)^2 = a t d^2, (t d^2)^{2^{cc}} = 1, (d^2)^{2^cc} = -1
		x = 1LL * x * d % p;
		b = 1LL * d * d % p;
		t = 1LL * t * b % p;
		c = cc;
	}
	return x;
}
// 模板例题：https://www.luogu.com.cn/problem/P5491

class Matrix {
public:
	const static int N = 1003;
	int n, a[N][N], mod;
	Matrix() {}
	Matrix(int _n, int x = 0): n(_n) { // xIn
		all(0);
		for (int i = 0; i < n; ++i) {
			a[i][i] = x;
		}
	}
	void all(int x) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[i][j] = x;
			}
		}
	}
	Matrix operator + (const Matrix & A) const {
		Matrix R(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				R.a[i][j] = a[i][j] + A.a[i][j];
				if (R.a[i][j] >= mod) R.a[i][j] -= mod;
			}
		}
		return R;
	}
	Matrix operator * (const Matrix & A) const {
		Matrix R(n);
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < n; ++k) {
				for (int j = 0; j < n; ++j) {
					R.a[i][j] = (R.a[i][j] + 1LL * a[i][k] * A.a[k][j]) % mod;
				}
			}
		}
		return R;
	}
	void print() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cout << a[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}
};
Matrix pow(Matrix A, int n) {
	Matrix R(A.n, 1);
	while (n) {
		if (n&1) R = R * A;
		n >>= 1; A = A * A;
	}
	return R;
}

// Gauss 消元法 Ax = b 浮点数版
std::vector<double> Gauss(std::vector<std::vector<double>> A, std::vector<double> b) {
	int n = A.size(), m = A[0].size();
	std::vector<double> x(m);
	std::vector<int> p(m);
	std::iota(p.begin(), p.end(), 0);
	const double eps = 1e-12;
	auto findNonZero = [&](int i) { // 实际上找最大的比较好
		for (int row = i; row < n; ++row) if (fabs(A[row][i]) > eps) return row;
		return n;
	};
	auto triangleGauss = [&](int sz) { // A[i][i] = 1
		std::vector<double> x(sz);
		for (int i = sz - 1; i >=0; --i) {
			x[i] = b[i];
			for (int row = 0; row < i; ++row) b[row] -= A[row][i] * x[i];
		}
		x.resize(A[0].size());
		return x;
	};
	int sz = n;
	for (int i = 0, row; i < n; ++i) {
		while (i < m) {
			row = findNonZero(i);
			if (row != n) break;
			for (int j = 0; j < n; ++j) A[j][i] = A[j][m - 1];
			std::swap(p[i], p[--m]);
		}
		if (i == m) {
			for (int row = m; row < n; ++row) if (fabs(b[row])) {
				// std::cout << "\nNo answer\n";
				return std::vector<double>();
			}
			sz = i;
			break;
		}
		if (row != i) {
			std::swap(A[row], A[i]);
			std::swap(b[row], b[i]);
		}
		b[i] /= A[i][i];
		for (int j = m - 1; j >= i; --j) A[i][j] /= A[i][i];
		for (int row = i + 1; row < n; ++row) {
			b[row] -= A[row][i] * b[i];
			for (int j = m - 1; j >= i; --j) {
				A[row][j] -= A[row][i] * A[i][j];
			}
		}
	}
	// if (sz != A[0].size()) std::cout << "\nInfinite answer\n";
	auto xt = triangleGauss(sz);
	for (int t = 0; t < A[0].size(); ++t) x[p[t]] = xt[t];
	return x;
}

// 模 Gauss 消元法 Ax = b
std::vector<int> Gauss(std::vector<std::vector<int>> A, std::vector<int> b) {
	const int M = 998244353;
	int n = A.size(), m = A[0].size();
	std::vector<int> x(m), p(m);
	std::iota(p.begin(), p.end(), 0);
	auto sub = [](int &x, int y) {
		(x -= y) < 0 && (x += M);
	};
	auto triangleGauss = [&](int sz) { // A[i][i] = 1
		std::vector<int> x(sz);
		for (int i = sz - 1; i >=0; --i) {
			x[i] = b[i];
			if (x[i] < 0) x[i] += M;
			for (int row = 0; row < i; ++row) sub(b[row], 1LL * A[row][i] * x[i] % M);
		}
		x.resize(A[0].size());
		return x;
	};
	auto findNonZero = [&](int i) {
		for (int row = i; row < n; ++row) if (A[row][i]) return row;
		return n;
	};
	int sz = n;
	for (int i = 0, row; i < n; ++i) {
		while (i < m) {
			row = findNonZero(i);
			if (row != n) break;
			for (int j = 0; j < n; ++j) A[j][i] = A[j][m - 1];
			std::swap(p[i], p[--m]);
		}
		if (i == m) {
			for (int row = m; row < n; ++row) if (b[row]) {
				// std::cout << "\nNo answer\n";
				return {};
			}
			sz = i;
			break;
		}
		if (row != i) {
			std::swap(A[i], A[row]);
			std::swap(b[i], b[row]);
		}
		int inva = powMod(A[i][i], M - 2, M);
		b[i] = b[i] * inva % M;
		for (int j = m - 1; j >= i; --j) A[i][j] = 1LL * A[i][j] * inva % M;
		for (int row = i + 1; row < n; ++row) {
			sub(b[row], 1LL * A[row][i] * b[i] % M);
			for (int j = m - 1; j >= i; --j) {
				sub(A[row][j], 1LL * A[row][i] * A[i][j] % M);
			}
		}
	}
	// if (sz != A[0].size()) std::cout << "\nInfinite answer\n";
	auto xt = triangleGauss(sz);
	for (int t = 0; t < A[0].size(); ++t) x[p[t]] = xt[t];
	return x;
}

// 线性规划单纯形法
using VD = std::vector<double>;
const double eps = 1e-10;
const double inf = 1e10;
// make sure that A = (I, A') and b >= 0, compute max cx
VD simplexCore(VD c, std::vector<VD> A, VD b) {
	int n = A.size(), m = c.size();
	std::vector<int> p(m);
	std::iota(p.begin(), p.end(), 0);
	for (int i = 0; i < n; ++i) A[i].emplace_back(b[i]);
	c.emplace_back(0);
	A.emplace_back(c);
	for (int j = n; j <= m; ++j) {
		for (int i = 0; i < n; ++i) {
			A[n][j] -= A[n][i] * A[i][j];
		}
	}
	auto check = [&]() -> bool {
		for (int j = n; j < m; ++j) if (A[n][j] > eps) {
			bool flag = false;
			for (int i = 0; i < n; ++i) if (A[i][j] > eps) {
				flag = true;
				break;
			}
			if (!flag) return false;
		}
		return true;
	};
	while (1) {
		int ch = std::max_element(A[n].begin() + n, A[n].begin() + m) - A[n].begin(), hc;
		if (A[n][ch] < eps) break;	
		assert(check()); // otherwise unbounded, no max solution
		double theta = DBL_MAX;
		for (int i = 0; i < n; ++i) if (A[i][ch] > eps && A[i].back() / A[i][ch] < theta) {
			theta = A[i].back() / A[i][ch];
			hc = i;
		}
		std::swap(p[ch], p[hc]);
		double tmp = 1 / A[hc][ch];
		for (int j = n; j <= m; ++j) A[hc][j] *= tmp;
		for (int i = 0; i <= n; ++i) if (i != hc) {
			for (int j = n; j <= m; ++j) if (j != ch) {
				A[i][j] -= A[i][ch] * A[hc][j];
			}
		}
		for (int i = 0; i <= n; ++i) A[i][ch] *= -tmp;
		A[hc][ch] = tmp;
	}
	VD x(m);
	for (int i = 0; i < n; ++i) x[p[i]] = A[i].back();
	// watch(-A.back().back()); // max_val
	return x; // point Corresponds to max_val
}
// compute max cx, with Aqx = bq and Alq x <= blq, end of 0 can be ommit in A and Aq
VD simplex(VD c, std::vector<VD> Aq, VD bq, std::vector<VD> Alq, VD blq) {
	assert(Aq.size() == bq.size());
	assert(Alq.size() == blq.size());
	int n = Aq.size() + Alq.size();
	int m = c.size();
	for (int i = 0; i < bq.size(); ++i) if (bq[i] < -eps) {
		for (auto &x : Aq[i]) x = -x;
		bq[i] = -bq[i];
	}
	for (int i = 0; i < blq.size(); ++i) if (blq[i] < -eps) {
		for (auto &x : Alq[i]) x = -x;
		++m;
	}
	std::vector<VD> A(n, VD(n + m));
	VD f(n + m), b(n);
	int now = n + c.size();
	for (int i = 0; i < n; ++i) A[i][i] = 1;
	for (int i = 0; i < Aq.size(); ++i) {
		for (int j = 0; j < Aq[i].size(); ++j) A[i][n + j] = Aq[i][j];
		b[i] = bq[i];
		f[i] = -inf;
	}
	for (int i = 0; i < Alq.size(); ++i) {
		for (int j = 0; j < Alq[i].size(); ++j) A[i + Aq.size()][n + j] = Alq[i][j];
		if (blq[i] < -eps) {
			A[i + Aq.size()][now++] = -1;
			f[i + Aq.size()] = -inf;
		}
		b[i + Aq.size()] = fabs(blq[i]);
	}
	for (int i = 0; i < c.size(); ++i) f[n + i] = c[i];
	auto x = simplexCore(f, A, b);
	return VD(x.begin() + n, x.begin() + n + c.size());
}

// 计算在 f 处的 lagrange 函数在 m 点的取值（模 M），M 为素数，0 <= f[i] < M
int Lagrange(const std::vector<int> &f, int m, int M) {
	int n = f.size();
	if (m < n) return f[m];
	int nfac = 1;
	for (int i = 2; i < n; ++i) nfac = 1LL * nfac * i % M;
	std::vector<int> ifac(n), AP(n), BP(n);
	ifac[n - 1] = powMod(nfac, M - 2, M);
	for (int i = n - 1; i > 0; --i) ifac[i - 1] = 1LL * ifac[i] * i % M;
	AP[0] = BP[n - 1] = 1;
	for (int i = 1; i < n; ++i) AP[i] = 1LL * AP[i - 1] * (m + 1 - i) % M;
	for (int i = n - 2; ~i; --i) BP[i] = 1LL * BP[i + 1] * (m - 1 - i) % M;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int x = 1LL * f[i] * AP[i] % M * BP[i] % M * ifac[i] % M * ifac[n - 1 - i] % M;
		ans += (n - 1 - i) & 1 ? M - x : x;
		if (ans >= M) ans -= M;
	}
	return ans;
}
// 由 lagrange 插值定理 知f(x) =  \sum_{i = 0}^{n - 1} f_i \prod_{j \neq i} \frac{x - j}{i - j}
// 简化得 f(m) = \sum_{i = 0}^{n - 1} (-1)^{n - 1 - i} f_i \binom{m}{i} \binom{m - i - 1}{n - 1 - i}

// 基于 lagrange 插值 O(k) 计算自然数方幂和
int powSum(int n, int k, int M, const std::vector<int> &sp){
	if (k == 0) return n % M;
	std::vector<int> f(k + 2);
	f[1] = 1;
	for (int i = 2; i < f.size(); ++i) {
		if (sp[i] == i) f[i] = powMod(i, k, M);
		else f[i] = 1LL * f[sp[i]] * f[i / sp[i]] % M;
	}
	for (int i = 1; i < f.size(); ++i) {
		f[i] += f[i - 1];
		if (f[i] >= M) f[i] -= M;
	}
	return Lagrange(f, n, M);
}
//模板例题：https://codeforces.com/problemset/problem/622/F

// 任意模数多项式乘法 O(n^{\log_2 3})
using VL = std::vector<LL>;
VL Karatsuba(VL a, VL b, LL p) {
	if (a.size() < b.size()) std::swap(a, b);
	auto mulS = [&](VL a, VL b) {
		int n = a.size(), m = b.size(), sz = n + m - 1;
		std::vector<__int128> c(sz);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				c[i + j] += a[i] * b[j];
			}
		}
		VL r(sz);
		for (int i = 0; i < sz; ++i) r[i] = c[i] % p;
		return r;
	};
	const int N = 65;
	std::function<VL(VL, VL, int)> mul = [&](VL a, VL b, int n) -> VL {
		if (n < N) return mulS(a, b);
		int n2 = n / 2, n1 = n - 1;
		VL a2 = VL(a.begin() + n2, a.end());
		VL b2 = VL(b.begin() + n2, b.end());
		a.resize(n2); b.resize(n2);
		VL ap = a2, bp = b2;
		for (int i = 0; i < n2; ++i) if ((ap[i] += a[i]) >= p) ap[i] -= p;
		for (int i = 0; i < n2; ++i) if ((bp[i] += b[i]) >= p) bp[i] -= p;
		VL ab = mul(a, b, n2);
		VL a2b = mul(ap, bp, n2);
		VL a2b2 = mul(a2, b2, n2);
		for (int i = 0; i < n1; ++i) {
			if ((a2b[i] -= ab[i]) < 0) a2b[i] += p;
			if ((a2b[i] -= a2b2[i]) < 0) a2b[i] += p;
		}
		auto r = ab;
		r.emplace_back(0);
		r.insert(r.end(), a2b2.begin(), a2b2.end());
		for (int i = 0; i < n1; ++i) if ((r[i + n2] += a2b[i]) >= p) r[i + n2] -= p;
		return r;
	};
	int n = a.size(), m = b.size(), tot = n + m - 1, sz = 1;
	if (m < N || n / m * 2 > m) return mulS(a, b);
	while (sz < n) sz *= 2;
	a.resize(sz), b.resize(sz);
	auto r = mul(a, b, sz);
	r.resize(tot);
	return r;
} // 模板例题：https://www.luogu.com.cn/problem/P4245

// 任意模数多项式乘法 O(n^{\log_2 3}) 并行版（如果有无穷核心，那岂不是 $O(n \log n)$ 的）
using VL = std::vector<LL>;
VL KaratsubaParallel(VL a, VL b, LL p) {
	if (a.size() < b.size()) std::swap(a, b);
	auto mulS = [&](VL a, VL b) {
		int n = a.size(), m = b.size(), sz = n + m - 1;
		std::vector<__int128> c(sz);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				c[i + j] += a[i] * b[j];
			}
		}
		VL r(sz);
		for (int i = 0; i < sz; ++i) r[i] = c[i] % p;
		return r;
	};
	const int N = 65;
	std::function<VL(VL, VL, int)> mul = [&](VL a, VL b, int n) -> VL {
		if (n < N) return mulS(a, b);
		int n2 = n / 2, n1 = n - 1;
		VL a2 = VL(a.begin() + n2, a.end());
		VL b2 = VL(b.begin() + n2, b.end());
		a.resize(n2); b.resize(n2);
		VL ap = a2, bp = b2;
		for (int i = 0; i < n2; ++i) if ((ap[i] += a[i]) >= p) ap[i] -= p;
		for (int i = 0; i < n2; ++i) if ((bp[i] += b[i]) >= p) bp[i] -= p;
		std::future<VL> abThread = std::async(mul, a, b, n2);
		VL a2b = mul(ap, bp, n2);
		VL ab = abThread.get();
		VL a2b2 = mul(a2, b2, n2);
		for (int i = 0; i < n1; ++i) {
			if ((a2b[i] -= ab[i]) < 0) a2b[i] += p;
			if ((a2b[i] -= a2b2[i]) < 0) a2b[i] += p;
		}
		auto r = ab;
		r.emplace_back(0);
		r.insert(r.end(), a2b2.begin(), a2b2.end());
		for (int i = 0; i < n1; ++i) if ((r[i + n2] += a2b[i]) >= p) r[i + n2] -= p;
		return r;
	};
	int n = a.size(), m = b.size(), tot = n + m - 1, sz = 1;
	if (m < N || n / m * 8 > m) return mulS(a, b);
	while (sz < n) sz *= 2;
	a.resize(sz), b.resize(sz);
	auto r = mul(a, b, sz);
	r.resize(tot);
	return r;
} // 模板例题：https://www.luogu.com.cn/problem/P4245，无法提交，CE。


// 借鉴了 jiangly 的模板
namespace NFT {
const int M = 998244353, g = 3;
std::vector<int> rev, roots{0, 1};
int powMod(int x, int n) {
	int r(1);
	while (n) {
		if (n&1) r = 1LL * r * x % M;
		n >>= 1; x = 1LL * x * x % M;
	}
	return r;
}
void dft(std::vector<int> &a) {
	int n = a.size();
	if (rev.size() != n) {
		int k = __builtin_ctz(n) - 1;
		rev.resize(n);
		for (int i = 0; i < n; ++i) {
			rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
	}
	for (int i = 0; i < n; ++i) if (rev[i] < i) {
		std::swap(a[i], a[rev[i]]);
	}
	if (roots.size() < n) {
		int k = __builtin_ctz(roots.size());
		roots.resize(n);
		while ((1 << k) < n) {
			int e = powMod(g, (M - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); ++i) {
				roots[2 * i] = roots[i];
				roots[2 * i + 1] = 1LL * roots[i] * e % M;
			}
			++k;
		}
	}
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; ++j) {
				int u = a[i + j];
				int v = 1LL * a[i + j + k] * roots[k + j] % M;
				int x = u + v, y = u - v;
				if (x >= M) x -= M;
				if (y < 0) y += M;
				a[i + j] = x;
				a[i + j + k] = y;
			}
		}
	}
}
void idft(std::vector<int> &a) {
	int n = a.size();
	std::reverse(a.begin() + 1, a.end());
	dft(a);
	int inv = powMod(n, M - 2);
	for (int i = 0; i < n; ++i) {
		a[i] = 1LL * a[i] * inv % M;
	}
}
} //namespace NFT

// 如果需要换模 M，那么就把 M 当做全局变量提出来，NFT 中 g, rev, root 需要重新初始化。
// 如果只需要换模几个常数 M，可使用 template<LL M>（但是不是特别推荐）
class Poly {
	void standard() {
		while (!a.empty() && !a.back()) a.pop_back();
	}
	void reverse() {
		std::reverse(a.begin(), a.end());
		standard();
	}
public:
	inline const static int M = NFT::M;
	std::vector<int> a;
	Poly() {}
	Poly(int x) { if (x) a = {x};}
	Poly(const std::vector<int> _a) : a(_a) { standard();}
	int size() const { return a.size();}
	int operator[](int id) const {
		if (id < 0 || id > a.size()) return 0;
		return a[id];
	}
	Poly mulXn(int n) const {
		auto b = a;
		b.insert(b.begin(), n, 0);
		return Poly(b);
	}
	Poly modXn(int n) const {
		if (n > size()) return *this;
		return Poly({a.begin(), a.begin() + n});
	}
	Poly divXn(int n) const {
		if (size() <= n) return Poly();
		return Poly({a.begin() + n, a.end()});
	}
	Poly &operator+=(const Poly &A) {
		if (size() < A.size()) a.resize(A.size());
		for (int i = 0; i < A.size(); ++i) {
			if ((a[i] += A.a[i]) >= M) a[i] -= M;
		}
		standard();
		return *this;
	}
	Poly &operator-=(const Poly &rhs) {
		if (size() < rhs.size()) a.resize(rhs.size());
		for (int i = 0; i < rhs.size(); ++i) {
			if ((a[i] -= rhs.a[i]) < 0) a[i] += M;
		}
		standard();
		return *this;
	}
	Poly &operator*=(Poly rhs) {
		int n = size(), m = rhs.size(), tot = n + m - 1, sz = 1;
		while (sz < tot) sz *= 2;
		a.resize(sz);
		rhs.a.resize(sz);
		NFT::dft(a);
		NFT::dft(rhs.a);
		for (int i = 0; i < sz; ++i) {
			a[i] = 1LL * a[i] * rhs.a[i] % M;
		}
		NFT::idft(a);
		standard();
		return *this;
	}
	Poly &operator/=(Poly rhs) {
		int n = size(), m = rhs.size();
		if (n < m) return (*this) = Poly();
		reverse();
		rhs.reverse();
		(*this) *= rhs.inv(n - m + 1);
		a.resize(n - m + 1);
		reverse();
		return *this;
	}
	Poly &operator%=(Poly rhs) {
		return (*this) -= (*this) / rhs * rhs; 
	}
	Poly operator+(const Poly &rhs) const {
		return Poly(*this) += rhs;
	}
	Poly operator-(const Poly &rhs) const {
		return Poly(*this) -= rhs;
	}
	Poly operator*(Poly rhs) const {
		return Poly(*this) *= rhs;
	}
	Poly operator/(Poly rhs) const {
		return Poly(*this) /= rhs;
	}
	Poly operator%(Poly rhs) const {
		return Poly(*this) %= rhs;
	}
	Poly powMod(int n, Poly p) {
		Poly r(1), x(*this);
		while (n) {
			if (n&1) (r *= x) %= p;
			n >>= 1; (x *= x) %= p;
		}
		return r;
	}
	int inner(const Poly & rhs) {
		int r = 0, n = std::min(size(), rhs.size());
		for (int i = 0; i < n; ++i) {
			r = (r + 1LL * a[i] * rhs.a[i]) % M;
		}
		return r;
	}
	Poly derivation() const {
		if (a.empty()) return Poly();
		int n = size();
		std::vector<int> r(n - 1);
		for (int i = 1; i < n; ++i) r[i - 1] =  1LL * a[i] * i % M;
		return Poly(r);
	}
	Poly integral() const {
		if (a.empty()) return Poly();
		int n = size();
		std::vector<int> r(n + 1), inv(n + 1, 1);
		for (int i = 2; i <= n; ++i) inv[i] = 1LL * (M - M / i) * inv[M % i] % M;
		for (int i = 0; i < n; ++i) r[i + 1] = 1LL * a[i] * inv[i + 1] % M;
		return Poly(r);
	}
	Poly inv(int n) const {
		assert(a[0] != 0);
		Poly x(NFT::powMod(a[0], M - 2));
		int k = 1;
		while (k < n) {
			k *= 2;
			x *= (Poly(2) - modXn(k) * x).modXn(k);
		}
		return x.modXn(n);
	}
	// 需要保证首项为 1
	Poly log(int n) const {
		return (derivation() * inv(n)).integral().modXn(n);
	}
	// 需要保证首项为 0
	Poly exp(int n) const {
		Poly x(1);
		int k = 1;
		while (k < n) {
			k *= 2;
			x = (x * (Poly(1) - x.log(k) + modXn(k))).modXn(k);
		}
		return x.modXn(n);
	}
	// 需要保证首项为 1，开任意次方可以先 ln 再 exp 实现。
	Poly sqrt(int n) const {
		Poly x(1);
		int k = 1;
		int inv2 = (M + 1) / 2;
		while (k < n) {
			k *= 2;
			x += modXn(k) * x.inv(k);
			x = x.modXn(k) * inv2;
		}
		return x.modXn(n);
	}
	// 减法卷积，也称转置卷积 {\rm MULT}(F(x),G(x))=\sum_{i\ge0}(\sum_{j\ge 0}f_{i+j}g_j)x^i
	Poly mulT(Poly rhs) const {
		if (rhs.size() == 0) return Poly();
		int n = rhs.size();
		std::reverse(rhs.a.begin(), rhs.a.end());
		return ((*this) * rhs).divXn(n - 1);
	}
	int eval(int x) {
		int r = 0, t = 1;
		for (int i = 0, n = size(); i < n; ++i) {
			r = (r + 1LL * a[i] * t) % M;
			t = 1LL * t * x % M;
		}
		return r;
	}
	// 多点求值新科技：https://jkloverdcoi.github.io/2020/08/04/转置原理及其应用/
	std::vector<int> eval(std::vector<int> x) const {
		if (size() == 0) return std::vector<int>(x.size());
		int n = x.size();
		std::vector<int> ans(n);
		std::vector<Poly> g(4 * n);
		std::function<void(int, int, int)> build = [&](int l, int r, int p) {
			if (r - l == 1) {
				// g[p] = std::vector<int>{1, x[i] ? M - x[l] : 0};
				g[p] = Poly({1, x[l] ? M - x[l] : 0});
			} else {
				int m = (l + r) / 2;
				build(l, m, 2 * p);
				build(m, r, 2 * p + 1);
				g[p] = g[2 * p] * g[2 * p + 1];
			}
		};
		build(0, n, 1);
		std::function<void(int, int, int, const Poly &)> solve = [&](int l, int r, int p, const Poly &f) {
			if (r - l == 1) {
				ans[l] = f[0];
			} else {
				int m = (l + r) / 2;
				solve(l, m, 2 * p, f.mulT(g[2 * p + 1]).modXn(m - l));
				solve(m, r, 2 * p + 1, f.mulT(g[2 * p]).modXn(r - m));
			}
		};
		solve(0, n, 1, mulT(g[1].inv(size())).modXn(n));
		return ans;
	} // 模板例题：https://www.luogu.com.cn/problem/P5050
}; // Poly 全家桶测试：https://www.luogu.com.cn/training/3015#information
// 非 NFT-friendly 的模数可以看我的这份提交：https://codeforces.com/contest/1516/submission/113886543

// 计算 \sum_{i = 0}^{n - 1} a_i / (1 - b_i x)
std::vector<int> sumFraction(std::vector<int> a, std::vector<int> b, int N) {
	std::function<std::pair<Poly, Poly>(int, int)> solve = [&](int l, int r) -> std::pair<Poly, Poly> {
		if (r - l == 1) {
			return {Poly(a[l]), Poly({1, b[l] ? Poly::M - b[l] : 0})};
		}
		int m = (l + r) / 2;
		auto [pl, ql] = solve(l, m);
		auto [pr, qr] = solve(m, r);
		return {pl * qr + pr * ql, ql * qr};
	};
	auto [p, q] = solve(0, a.size());
	p *= q.inv(N);
	auto ans = p.a;
	ans.resize(N);
	return ans;
} // 模板例题：https://codeforces.com/gym/102978/problem/D

// $a_n = \sum_{i = 1}^{k} f_i a_{n - i}$，理论：https://oi-wiki.org/math/linear-recurrence/
// $O(k \log k \log n)$ 求 k 阶常系数递推公式的第 n 项
int linearRecursion(std::vector<int> a, std::vector<int> f, int n) {
	if (n < a.size()) return a[n];
	int m = f.size();
	std::reverse(f.begin(), f.end());
	std::vector<int> g(m);
	g.emplace_back(1);
	Poly A = Poly({0, 1}), p = Poly(g) - Poly(f);
	Poly R = A.powMod(n, p);
	return R.inner(a);
} // 模板: https://www.luogu.com.cn/problem/P4723

namespace FMT {
const int M = 998244353, inv2 = (M + 1) / 2;
auto add = [](int &x, int y) {
	(x += y) >= M && (x -= M);
};
auto sub = [](int &x, int y) {
	(x -= y) < 0 && (x += M);
};
auto extend = [](int n) {
	int r = std::log(n);
	while ((1 << r) < n) ++r;
	return r; 
};
auto FMTor = [](std::vector<int> &a, bool isRev) {
	int n = extend(a.size());
	a.resize(1 << n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < (1 << n); ++j) if ((j >> i) & 1) {
			if (isRev) sub(a[j], a[j ^ (1 << i)]);
			else add(a[j], a[j ^ (1 << i)]);
		}
	}
};
auto FMTand = [](std::vector<int> &a, bool isRev) {
	int n = extend(a.size());
	a.resize(1 << n);
	for (int i = 0; i < n; ++i) {
		for (int j = (1 << n) - 1; j >= 0; --j) if ((j >> i) & 1) {
			if (isRev) sub(a[j ^ (1 << i)], a[j]);
			else add(a[j ^ (1 << i)], a[j]);
		}
	}
};
auto FMTxor = [](std::vector<int> &a, bool isRev) {
	int n = extend(a.size());
	a.resize(1 << n);
	for (int i = 0; i < n; ++i) {
		for (int j = (1 << n) - 1; j >= 0; --j) if ((j >> i) & 1) {
			int u = a[j], v = a[j ^ (1 << i)];
			a[j] = (v - u + M) % M;
			a[j ^ (1 << i)] = (u + v) % M;
		}
		if (isRev) for (auto &x : a) x = 1LL * inv2 * x % M;
	}
};
auto fun = [](std::function<void(std::vector<int> &, bool)> f, std::vector<int> a, std::vector<int> b) {
	int n = extend(std::max(a.size(), b.size()));
	a.resize(1 << n); b.resize(1 << n);
	f(a, 0); f(b, 0);
	std::vector<int> c(1 << n);
	for (int i = 0; i < (1 << n); ++i) c[i] = 1LL * a[i] * b[i] % M;
	f(c, 1);
	return c;
};
auto Or = [](std::vector<int> a, std::vector<int> b) {
	return fun(FMTor, a, b);
};
auto And = [](std::vector<int> a, std::vector<int> b) {
	return fun(FMTand, a, b);
};
auto Xor = [](std::vector<int> a, std::vector<int> b) {
	return fun(FMTxor, a, b);
};
// i = j | k and j & k = 0
auto OrAnd = [](std::vector<int> a, std::vector<int> b) {
	int n = extend(std::max(a.size(), b.size()));
	a.resize(1 << n); b.resize(1 << n);
	std::vector<std::vector<int>> sa(n + 1, std::vector<int>(1 << n));
	auto sb = sa, sc = sa;
	for (int i = 0; i < (1 << n); ++i) sa[__builtin_popcount(i)][i] = a[i];
	for (int i = 0; i < (1 << n); ++i) sb[__builtin_popcount(i)][i] = b[i];
	for (int i = 0; i <= n; ++i) {
		FMTor(sa[i], 0);FMTor(sb[i], 0);
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k < (1 << n); ++k) {
				add(sc[i][k], 1LL * sa[j][k] * sb[i - j][k] % M);
			}
		}
		FMTor(sc[i], 1);
	}
	std::vector<int> c(1 << n);
	for (int i = 0; i < (1 << n); ++i) c[i] = sc[__builtin_popcount(i)][i];
	return c;
};
} // namespace FMT

// ans[i] = 1^i + 2^i + ... + (n - 1)^i, 0 < i < k
// 原理：https://dna049.com/fastPowSumOfNaturalNumber/
std::vector<int> powSum(int n, int k) {
	Poly Numerator = Poly({0, n}).exp(k + 1).divXn(1);
	Poly denominator  = Poly({0, 1}).exp(k + 1).divXn(1);
	auto f = (Numerator * denominator.inv(k)).modXn(k) - Poly(1);
	auto ans = f.a;
	ans.resize(k);
	int now = 1;
	for (int i = 2; i < k; ++i) {
		now = 1LL * now * i % Poly::M;
		ans[i] = 1LL * ans[i] * now % Poly::M;
	}
	return ans;
}

// 计算集合 S 中所有数与 x 异或后的 MEX 值。
class MEX {
	// 具体数值要对应修改。
	inline static const int B = 20;
	std::array<std::map<int, int>, B> mp;
	std::map<int, int> S;
public:
	void insert(int x) {
		if (S[x]++) return;
		int mask = 0;
		for (int i = B - 1; i >= 0; --i) {
			mask |= 1 << i;
			++mp[i][x & mask];
		}
	}
	void erase(int x) {
		if (--S[x]) return;
		S.erase(x);
		int mask = 0;
		for (int i = B - 1; i >= 0; --i) {
			mask |= 1 << i;
			--mp[i][x & mask];
		}
	}
	// find mex(a_i ^ x)
	int solve(int x = 0) {
		int mask = 0, r = 0;
		for (int i = B - 1; i >= 0; --i) {
			mask |= x & (1 << i);
			if (mp[i][mask] == (1 << i)) {
				mask ^= 1 << i;
				r |= 1 << i;
			}
		}
		return r;
	}
};

namespace Geomerty {
using Point = std::pair<double, double>;
using Point = std::pair<double, double>;
bool crossLeft(const Point &op, const Point &sp, const Point &ep) {
	return (sp.first - op.first) * (ep.second - op.second) 
	<= (sp.second - op.second) * (ep.first - op.first);
}
double cross(const Point &op, const Point &sp, const Point &ep) {
	return (sp.first - op.first) * (ep.second - op.second) 
	- (sp.second - op.second) * (ep.first - op.first);	
}
double dist2(const Point &p, const Point &q) {
	double x = q.first - p.first, y = q.second - p.second;
	return x * x + y * y;
};

std::vector<Point> convexHull(std::vector<Point> p) {
	std::sort(p.begin(), p.end());
	p.erase(std::unique(p.begin(), p.end()), p.end());
	int n = p.size();
	std::vector<Point> q(n + 1);
	int top = 0;
	for (int i = 0; i < n; ++i) {
		while (top > 1 && crossLeft(q[top - 1], p[i], q[top - 2])) --top;
		q[top++] = p[i];
	}
	int len = top;
	for (int i = n - 2; i >= 0; --i) {
		while (top > len && crossLeft(q[top - 1], p[i], q[top - 2])) --top;
		q[top++] = p[i];
	}
	top -= n > 1;
	q.resize(top);
	return q;
}

double diameter(std::vector<Point> p) {
	auto q = convexHull(p);
	if (q.size() < 2) return 0;
	if (q.size() == 2) return dist2(q[0], q[1]);
	int n = q.size();
	q.emplace_back(q[0]);
	double ans = 0;
	for (int i = 0, j = 2; i < n; ++i) {
		while (cross(q[i], q[i + 1], q[j]) < cross(q[i], q[i + 1], q[j + 1])) j = (j + 1) % n;
		ans = std::max({ans, dist2(q[i], q[j]), dist2(q[i + 1], q[j])});
	}
	return std::sqrt(ans);
} // 浮点数版例题：https://www.luogu.com.cn/problem/P6247
// 整数版例题：https://www.luogu.com.cn/problem/P1452

// 这里不要用 dist2，否则很多比较的地方都要平方，反而不优雅了。
double dist (const Point& p, const Point &q) {
	double x = q.first - p.first, y = q.second - p.second;
	return std::sqrt(x * x + y * y);
};
double minDist(std::vector<Point> a) {
	double d = DBL_MAX;
	int n = a.size();
	if (n <= 1) return d;
	std::sort(a.begin(), a.end());
	std::function<void(int, int)> merge = [&](int l, int r) {
		if (r - l <= 1) return;
		if (r - l == 2) {
			d = std::min(d, dist(a[l], a[l + 1]));
			return;
		}
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		std::vector<Point> p;
		for (int i = m - 1; i >= l && a[m].first - a[i].first < d; --i) {
			p.emplace_back(a[i].second, a[i].first);
		}
		for (int i = m; i < r && a[i].first - a[m].first < d; ++i) {
			p.emplace_back(a[i].second, a[i].first);
		}
		std::sort(p.begin(), p.end());
		for (int i = 0; i < p.size(); ++i) {
			for (int j = i + 1; j < p.size() && p[j].first - p[i].first < d; ++j) {
				d = std::min(d, dist(p[i], p[j]));
			}
		}
	};
	merge(0, n);
	return d;
} // https://www.luogu.com.cn/problem/P1429
} // namespace Geomerty

// a 是 k * n 矩阵表示 n 个 k 维向量，满足序关系的对的个数。
std::vector<int> partialOrder(std::vector<std::vector<int>> &a) {
// 直接暴力不太行，所以需要时间换空间，具体说就是分块。
	int k = a.size(), n = a[0].size();
	using Node = std::vector<std::pair<int, int>>;
	std::vector<Node> f(k, Node(n));
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < n; ++j) f[i][j] = {a[i][j], j};
		std::sort(f[i].begin(), f[i].end());
	}
	int sn = std::sqrt(n);
	const int N = 4e4 + 2;
	using Data = std::vector<std::bitset<N>>;
	std::vector<Data> bs(k, Data(n / sn + 1));;
	for (int i = 0; i < k; ++i) {
		std::bitset<N> now;
		for (int j = 0; j < n; ++j) {
			if (j % sn == 0) bs[i][j / sn] = now;
			now.set(f[i][j].second);
		}
		if (n % sn == 0) bs[i][n / sn] = now;
	}
	auto getbst = [&](int i, int val) -> std::bitset<N> {
		// 如果求小于或等于的个数，这里要改成 upper_bound 并且要用 INT_MAX，还有最终答案减 1（去掉自身）
		int j = std::lower_bound(f[i].begin(), f[i].end(), std::make_pair(val, INT_MIN)) - f[i].begin();
		std::bitset<N> r = bs[i][j / sn];
		for (int t = j / sn * sn; t < j; ++t) r.set(f[i][t].second);
		return r;
	};
	std::vector<int> r(n);
	for (int j = 0; j < n; ++j) {
		std::bitset<N> now; now.set();
		for (int i = 0; i < k; ++i) {
			now &= getbst(i, a[i][j]);
		}
		r[j] = now.count();
	}
	return r;
} // http://cogs.pro:8081/cogs/problem/problem.php?pid=vSJzQVejP


// 二维区间型: f_{l, r} = \min_{l \leq k < r} f_{l, k} + f_{k + 1, r} + w(l, r) \qquad (1 \leq l < r \leq n)
template<typename T>
std::vector<std::vector<T>> quadrangleItvDp(std::vector<std::vector<T>> w, int n) {
	std::vector<std::vector<T>> f(n + 1, std::vector<T>(n + 1)), mf(n + 1, std::vector<T>(n + 1));
	for (int i = 1; i < n; ++i) {
		f[i][i + 1] = w[i][i + 1];
		mf[i][i + 1] = i;
	}
	auto const inf = std::numeric_limits<T>::max() / 2;
	for (int len = 2; len < n; ++len) {
		for (int l = 1, r = len + 1; r <= n; ++l, ++r) {
			f[l][r] = inf;
			for (int k = mf[l][r - 1]; k <= mf[l + 1][r]; ++k) {
				if (f[l][r] > f[l][k] + f[k + 1][r]) {
					f[l][r] = f[l][k] + f[k + 1][r];
					mf[l][r] = k;
				}
			}
			f[l][r] += w[l][r];
		}
	}
	return f;
}

// 二维滚动型: f_{i, j} = \min_{k < j} f_{i - 1, k} + w(k + 1, j) \quad (1 \leq i \leq n, 1 \leq j \leq m)
template<typename T>
std::vector<std::vector<T>> quadrangleRollDp(std::vector<std::vector<T>> w, int n, int m) {
// w 是 (n + 1, n + 1) 矩阵，答案是 (m + 1, n + 1) 矩阵
	std::vector<std::vector<T>> f(m + 1, std::vector<T>(n + 1)), mf(m + 1,  std::vector<T>(n + 2));
	auto const inf = std::numeric_limits<T>::max() / 2;
	for (int i = 1; i < n; ++i) f[0][i] = inf;
	for (int i = 1; i <= m; ++i) {
		mf[i][n + 1] = n;
		for (int j = n; j > 0; --j) {
			f[i][j] = inf;
			for (int k = std::max(i - 1, mf[i - 1][j]); k < j && k <= mf[i][j + 1]; ++k) {
				if (f[i][j] > f[i - 1][k] + w[k + 1][j]) {
					f[i][j] = f[i - 1][k] + w[k + 1][j];
					mf[i][j] = k;
				}
			}
		}
	}
	return f;
}
// https://www.luogu.com.cn/problem/P4767
