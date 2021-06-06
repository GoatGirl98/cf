
## [2021 Hubei Provincial Collegiate Programming Contest](https://codeforces.com/gym/103104)

### A：异或纠错码

挺简单，但是还有有意义的一道题，反正就在最后面补 k 个 0，然后处理到最后，这 k 个字符就是答案。

### D：不交区间维护

> 昨天 cf 722 div 1C 本质就是不交区间维护更新

很有意思的一题，注意到 C 必然是连续的一段自然数，我们先保存所有值的位置，然后我们从最小值开始遍历，用 Set 维护不交并的区间即可。

### F：贪心

注意到 $b_i$ 是 $2$ 的幂次，因此我们可以让 $a$ 从小到大贪心的每次取最小，就不用担心大的因为先取了小的而没取到的问题。

### J：用复数处理相似三角形

首先对一个图形进行伸缩和旋转是相似变换，那这不就相当于用一个复数乘以所有的端点吗？我们要最小的整格点，那么我们就除以它们的最大公约数即可，而 Euild 整环都可以用带余除法求最大公约数。注意这里我们做除法的时候要使得余数的模最小。

### K：经过一轮取差取绝对值（经典分块）

根据和 [Kelin](https://codeforces.com/profile/Kelin) 的 Talk，注意到值域是单调递减的。利用第二分块解决（为什么叫[第二分块](https://www.luogu.com.cn/training/44148)，有空可以挑战以下 Ynoi 分块）

最后根据 [zimpha](https://codeforces.com/contest/896/submission/110248894) 的代码读懂了 第二分块 的做法。

然后取差之后绝对值也就相当于两次 第二分块 来持续处理一个区间。

> 注意到这题不像原始第二分块可以直接黑科技暴力过！