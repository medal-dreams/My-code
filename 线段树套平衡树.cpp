#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 5e4 + 66, inf = 2147483647;
mt19937 rd(time(0));
struct node{
	int val, ls, rs, sz;
	ll h;
}nd[N << 6];
int tot = 0; 
struct FHQ_Treap{
	int root;
	#define val(k) nd[k].val
	#define ls(k) nd[k].ls
	#define rs(k) nd[k].rs
	#define sz(k) nd[k].sz
	#define h(k) nd[k].h
	int newnode(int k){val(++ tot) = k, ls(tot) = rs(tot) = 0, sz(tot) = 1, h(tot) = rd();return tot;}
	void pushup(int p){sz(p) = sz(ls(p)) + sz(rs(p)) + 1;}
	void split(int rot, int val, int &x, int &y)
	{
		if(!rot){x = y = 0;return ;}
		if(val(rot) <= val)
		{
			x = rot;
			split(rs(rot), val, rs(rot), y);
			pushup(rot);
		}
		else 
		{
			y = rot;
			split(ls(rot), val, x, ls(rot));
			pushup(y);
		}
	}
	int merge(int x, int y)
	{
		if(!x || !y) return x | y;
		if(h(x) <= h(y))
		{
			rs(x) = merge(rs(x), y);
			pushup(x);return x;
		}
		else
		{
			ls(y) = merge(x, ls(y));
			pushup(y);return y;
		}
	}
	void insert(int val)
	{
		int x, y;
		split(root, val, x, y);
		root = merge(x, merge(newnode(val), y));
	}
	void erase(int val)
	{
		int x, y, z;
		split(root, val, x, z);
		split(x, val - 1, x, y);
		y = merge(ls(y), rs(y));
		root = merge(x, merge(y, z));
	}
	int find_rank(int val)
	{
		int x, y;split(root, val - 1, x, y);
		int ans = sz(x) + 1;root = merge(x, y);return ans;
	}
	int find_num(int rot, int k)
	{
		if(k <= sz(ls(rot))) return find_num(ls(rot), k);
		else if(k == sz(ls(rot)) + 1) return val(rot);
		else return find_num(rs(rot), k - sz(ls(rot)) - 1);
	}
	int pre(int val)
	{
		int x, y;split(root, val - 1, x, y);
		int ans = -inf;if(sz(x)) ans = find_num(x, sz(x));
		root = merge(x, y);return ans;
	}
	int suf(int val)
	{
		int x, y;split(root, val, x, y);
		int ans = inf;if(sz(y)) ans = find_num(y, 1);
		root = merge(x, y);return ans;
	}
	#undef val
	#undef ls
	#undef rs
	#undef sz
	#undef h
};
int a[N], n, m;
struct Segment_Tree{
	FHQ_Treap tr[N << 2];
	#define ls k << 1
	#define rs k << 1 | 1
	void build(int k, int l, int r)
	{
		for(int i = l;i <= r;i ++) tr[k].insert(a[i]);
		if(l == r) return ;
		int mid = l + r >> 1;
		build(ls, l, mid);build(rs, mid + 1, r);
	}
	int find_rank(int k, int l, int r, int x, int y, int val)
	{
		if(x <= l && r <= y)return tr[k].find_rank(val) - 1;
		int mid = l + r >> 1, res = 0;
		if(x <= mid) res += find_rank(ls, l, mid, x, y, val);
		if(y > mid) res += find_rank(rs, mid + 1, r, x, y, val);
		return res;
	}
	int find_num(int x, int y, int rank)
	{
		ll l = 0, r = inf, ans = -1;
		while(l <= r)
		{
			ll mid = l + r >> 1;
			if(find_rank(1, 1, n, x, y, mid) + 1 <= rank) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		return ans;
	}
	void update(int k, int l, int r, int x, int val)
	{
		tr[k].erase(a[x]);tr[k].insert(val);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(x <= mid) update(ls, l, mid, x, val);
		else update(rs, mid + 1, r, x, val);
	}
	int find_pre(int k, int l, int r, int x, int y, int val)
	{
		if(x <= l && r <= y) return tr[k].pre(val);
		int mid = l + r >> 1, res = -inf;
		if(x <= mid) res = max(res, find_pre(ls, l, mid, x, y, val));
		if(y > mid) res = max(res, find_pre(rs, mid + 1, r, x, y, val));
		return res;
	}
	int find_suf(int k, int l, int r, int x, int y, int val)
	{
		if(x <= l && r <= y) return tr[k].suf(val);
		int mid = l + r >> 1, res = inf;
		if(x <= mid) res = min(res, find_suf(ls, l, mid, x, y, val));
		if(y > mid) res = min(res, find_suf(rs, mid + 1, r, x, y, val));
		return res;
	}
}seg;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	seg.build(1, 1, n);
	while(m --)
	{
		int op, l, r, k;cin >> op;
		if(op == 1)
		{
			cin >> l >> r >> k;
			cout << seg.find_rank(1, 1, n, l, r, k) + 1 << '\n';
		}
		else if(op == 2)
		{
			cin >> l >> r >> k;
			cout << seg.find_num(l, r, k) << '\n';
		}
		else if(op == 3) 
		{
			cin >> l >> k;
			seg.update(1, 1, n, l, k);
			a[l] = k;
		}
		else if(op == 4)
		{
			cin >> l >> r >> k;
			cout << seg.find_pre(1, 1, n, l, r, k) << '\n';
		}
		else 
		{
			cin >> l >> r >> k;
			cout << seg.find_suf(1, 1, n, l, r, k) << '\n';
		}
	}
	return 0;
}
