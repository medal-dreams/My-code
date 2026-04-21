#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e5 + 66;
mt19937 rd(clock());
struct Treap{
	int ch[N][2], c[N], s[N], w[N], tot = 0, f[N];
	ll h[N];
	//c 权值个数 s 子树权值个数 w 权值
	void pushup(int u){s[u] = s[ch[u][0]] + s[ch[u][1]] + c[u];}
	int newnode(int v)
	{
		++ tot, c[tot] = s[tot] = 1;w[tot] = v;h[tot] = rd();
		return tot;
	}
	void rotate(int &p, int d)
	{
		int temp = ch[p][d ^ 1];
		ch[p][d ^ 1] = ch[temp][d];
		ch[temp][d] = p;
		p = temp;
		pushup(ch[p][d]), pushup(p);
	}
	void insert(int &p, int v)
	{
		if(p == 0) {p = newnode(v);return ;}
		if(w[p] == v) ++ c[p];
		else
		{
			int d = v > w[p];
			insert(ch[p][d], v);
			if(h[p] < h[ch[p][d]]) rotate(p, d ^ 1);
		}
		pushup(p);
	}
	void erase(int &p, int v)
	{
		if(!p) return ;
		if(v == w[p])
		{
			if(c[p] > 1) {c[p] --;pushup(p);return ;}
			if(ch[p][0] || ch[p][1])
			{
				if(!ch[p][1] || h[ch[p][0]] > h[ch[p][1]]) rotate(p, 1), erase(ch[p][1], v);
				else rotate(p, 0), erase(ch[p][0], v);
				pushup(p);
			}
			else p = 0;
			return ;
		}
		erase(ch[p][v > w[p]], v);
		pushup(p);
	}
	ll query_kth(const int p, int k)
	{
		if(s[ch[p][0]] >= k) return query_kth(ch[p][0], k);
		else if(s[ch[p][0]] + c[p] >= k) return w[p];
		return query_kth(ch[p][1], k - s[ch[p][0]] - c[p]);
	}
	ll query_rank(const int p, int k)
	{
		if(p == 0) return 1;
		if(k < w[p]) return query_rank(ch[p][0], k);
		if(k == w[p]) return s[ch[p][0]] + 1;
		return s[ch[p][0]] + c[p] + query_rank(ch[p][1], k);
	}
	ll query_pre(const int p, int k)
	{
		return query_kth(p, query_rank(p, k) - 1);
	}
	ll query_suc(const int p, int k)
	{
		return query_kth(p, query_rank(p, k + 1));
	}
	void dfs(int p)
	{
		if(ch[p][0]) dfs(ch[p][0]);
		cout << w[p] << ' ';
		if(ch[p][1]) dfs(ch[p][1]);
	}
}bst;
int n, r;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i ++)
	{
		int od, x;cin >> od >> x;
		switch(od)
		{
			case 1: bst.insert(r, x);break;
			case 2: bst.erase(r, x);break;
			case 3: cout << bst.query_rank(r, x) << '\n';break;
			case 4: cout << bst.query_kth(r, x) << '\n';break;
			case 5: cout << bst.query_pre(r, x) << '\n';break;
			case 6: cout << bst.query_suc(r, x) << '\n';break;
		}
	}
	return 0;
}
