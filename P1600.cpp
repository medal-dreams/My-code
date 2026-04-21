#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 3e5 + 66;
vector<int> G[N];int dep[N], dp[N][20], ans[N];
void dfs(int rot, int fa)
{
	dep[rot] = dep[fa] + 1, dp[rot][0] = fa;
	for(auto p : G[rot]) if(p != fa) dfs(p, rot);
}
struct segmenttree{
	int root[N][2], tot = 0;
	struct node{
		int val, ls, rs, mx, id;
	}nd[N << 7];
#define val(k) nd[k].val
#define ls(k) nd[k].ls
#define rs(k) nd[k].rs
#define id(k) nd[k].id
#define mx(k) nd[k].mx
	void pushup(int p){val(p) = val(ls(p)) + val(rs(p)), mx(p) = max(mx(ls(p)), mx(rs(p))), id(p) = (mx(p) == mx(ls(p)) ? id(ls(p)) : id(rs(p)));}
	void update(int &p, int l, int r, int x, int val)
	{
		if(!p) p = ++ tot;
		if(l == r) {val(p) += val, id(p) = l, mx(p) += val;return ;}
		int mid = l + r >> 1;
		if(x <= mid) update(ls(p), l, mid, x, val);
		else update(rs(p), mid + 1, r, x, val);
		pushup(p);
	}
	int merge(int u, int v, int l, int r)
	{
		if(!u || !v) return u | v;
		if(l == r) {val(u) += val(v), mx(u) += mx(v);return u;}
		int mid = l + r >> 1;
		ls(u) = merge(ls(u), ls(v), l, mid);rs(u) = merge(rs(u), rs(v), mid + 1, r);
		pushup(u);return u;
	}
	int query(int p, int x, int l, int r)
	{
		if(l == r) return val(p);
		int mid = l + r >> 1;
		if(x <= mid) return query(ls(p), x, l, mid);
		else return query(rs(p), x, mid + 1, r);
	}
}seg;
int n, m, x, y, la, z, w[N];
void init()
{
	for(int i = 1;i <= 19;i ++) for(int j = 1;j <= n;j ++) dp[j][i] = dp[dp[j][i - 1]][i - 1];
}
int lca(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19;i >= 0;i --) if((dep[x] - dep[y]) >= (1 << i)) x = dp[x][i];
	if(x == y) return x;
	for(int i = 19;i >= 0;i --) if(dp[x][i] != dp[y][i]) x = dp[x][i], y = dp[y][i];
	return dp[x][0];
}
void dfs2(int rot)
{
	for(auto p : G[rot]) 
	{
		if(p == dp[rot][0]) continue;
		dfs2(p);
		seg.root[rot][0] = seg.merge(seg.root[rot][0], seg.root[p][0], -2 * n, 2 * n);
		seg.root[rot][1] = seg.merge(seg.root[rot][1], seg.root[p][1], -2 * n, 2 * n);
	}
	ans[rot] = (dep[rot] + w[rot] > n ? 0 : seg.query(seg.root[rot][0], dep[rot] + w[rot], -2 * n, 2 * n)) + seg.query(seg.root[rot][1], dep[rot] - w[rot], -2 * n, 2 * n);
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i < n;i ++)
	{
		cin >> x >> y;
		G[x].push_back(y), G[y].push_back(x);
	}
	dfs(1, 0);
	init();
	for(int i = 1;i <= n;i ++) cin >> w[i];
	while(m --)
	{
		cin >> x >> y;
		la = lca(x, y);
		seg.update(seg.root[x][0], -2 * n, 2 * n, dep[x], 1), seg.update(seg.root[la][0], -2 * n, 2 * n, dep[x], -1);
		seg.update(seg.root[y][1], -2 * n, 2 * n, 2 * dep[la] - dep[x], 1), seg.update(seg.root[dp[la][0]][1], -2 * n, 2 * n, 2 * dep[la] - dep[x], -1);
	}
	dfs2(1);
	for(int i = 1;i <= n;i ++) cout << ans[i] << ' ';
	return 0;
}
