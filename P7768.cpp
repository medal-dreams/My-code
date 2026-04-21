#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e6 + 66;
template<typename T> void read(T &x)
{
	x = 0;int f = 1;char c;
	do{c = getchar_unlocked();if(c == '-') f = -1;}while(!isdigit(c));
	do{x = x * 10 + c - '0';c = getchar_unlocked();}while(isdigit(c));
	x *= f;
}
int nxt[N], head[N], to[N], hd;
void add(int x, int y)
{
	nxt[++ hd] = head[x];
	to[hd] = y;
	head[x] = hd;
}
struct segmenttree{
	int root[N], tot = 0;
	struct node{
		int val, ls, rs;
	}nd[N << 5];
	inline int newnode(int p){nd[++ tot] = nd[p];return tot;}
	inline void pushup(int p){nd[p].val = nd[nd[p].ls].val ^ nd[nd[p].rs].val;}
	inline void update(int &p, int l, int r, int x, int val)
	{
		p = newnode(p);
		if(l == r) {nd[p].val ^= val;return ;}
		int mid = l + r >> 1;
		if(x <= mid) update(nd[p].ls, l, mid, x, val);
		else update(nd[p].rs, mid + 1, r, x, val);
		pushup(p);//因为我们用区间查询，所以我们要 pushup 一下父节点
	}
	inline int query(int u, int v, int l, int r, int x, int y)
	{
		if(x <= l && r <= y) return nd[u].val ^ nd[v].val;
		int mid = l + r >> 1, res = 0;
		if(x <= mid) res ^= query(nd[u].ls, nd[v].ls, l, mid, x, y);
		if(y > mid) res ^= query(nd[u].rs, nd[v].rs, mid + 1, r, x, y);
		return res;//常规区间查询
	}
}seg;
int n, m, id[N], mp[N], sz[N], cnt, a[N], dep[N], mx;
// id:dfn序 mp: dfn序对应的节点编号 sz:节点子树大小 a:节点权值 dep:节点深度 mx:最大节点深度
int x, h;
inline void dfs(int rot, int fa)
{
	id[rot] = ++ cnt, mp[cnt] = rot;sz[rot] = 1;dep[rot] = dep[fa] + 1;mx = max(mx, dep[rot]);
	for(int i = head[rot];i;i = nxt[i]) if(to[i] != fa) dfs(to[i], rot), sz[rot] += sz[to[i]];
}//处理 dfn sz dep
int main()
{
	read(n), read(m);
	for(int i = 1;i <= n;i ++) read(a[i]);
	for(int i = 2;i <= n;i ++)
	{
		read(x);
		add(x, i);
	}
	dfs(1, 0);
	for(int i = 1;i <= n;i ++)//按 dfn 序建树
	{
		seg.root[i] = seg.root[i - 1];
		seg.update(seg.root[i], 1, mx, dep[mp[i]], a[mp[i]]);//在对应深度修改
	}
	while(m --)
	{
		read(x), read(h);
		int ans = seg.query(seg.root[id[x] + sz[x] - 1], seg.root[id[x] - 1], 1, mx, dep[x], dep[x] + h);//查询dfn区间对应深度区间的异或和
		printf("%d.%03d\n", ans / 1000, ans % 1000);//卡常小技巧，这样比浮点数运算快很多
	}
	return 0;
}
