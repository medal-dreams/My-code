#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e6 + 66;
int root[N], tot;
struct Seg_Ment_Tree{
	struct node{
		int val, ls, rs;
	}nd[N << 7];
#define ls(k) nd[k].ls
#define rs(k) nd[k].rs
	int newnode(int p){nd[++ tot] = nd[p];return tot;}
	void update(int &p, int l, int r, int x, int val)
	{
		p = newnode(p);
		if(l == r){nd[p].val = val;return ;}
		int mid = l + r >> 1;
		if(x <= mid) update(ls(p), l, mid, x, val);
		else update(rs(p), mid + 1, r, x, val);
	}
	ll query(int p, int l, int r, int x)
	{
		if(l == r) return nd[p].val;
		int mid = l + r >> 1;
		if(x <= mid) return query(ls(p), l, mid, x);
		else return query(rs(p), mid + 1, r, x);
	}
}seg;
int n, m, a;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i ++) cin >> a, seg.update(root[0], 1, n, i, a);
	for(int i = 1;i <= m;i ++)
	{
		int od, v, p, c;
		cin >> v >> od >> p;
		root[i] = root[v];
		if(od == 1)
		{
			cin >> c;
			seg.update(root[i], 1, n, p, c);
		}
		else cout << seg.query(root[i], 1, n, p) << '\n';
	}
	return 0;
}
