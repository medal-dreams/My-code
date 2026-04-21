#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e5 + 66;
struct BST{
	int l[N], r[N], c[N], s[N], w[N], tot = 0;
	//l 左儿子 r 右儿子 c 权值个数 s 子树权值个数 w 权值
	void pushup(int u){s[u] = s[l[u]] + s[r[u]] + c[u];}
	int newnode(int v)
	{
		++ tot, l[tot] = r[tot] = 0;c[tot] = s[tot] = 1;w[tot] = v;
		return tot;
	}
	void insert(int &p, int v)
	{
		if(p == 0) p = newnode(v);
		else
		{
			if(w[p] == v) ++ s[p], ++ c[p];
			else if(w[p] < v) insert(r[p], v);
			else insert(l[p], v);
			pushup(p);
		}
	}
	void replace(int &o, int p)
	{
		if(l[o])
		{
			replace(l[o], p);
			pushup(o);
		}
		else
		{
			swap(w[o], w[p]);
			swap(c[o], c[p]);
			o = r[o];
		}
	}
	void erase(int &p, int v)
	{
		if(w[p] == v)
		{
			if(c[p] > 1){c[p] --, s[p] --;return ;}//如果在一个结点，就删去
			if(l[p] == 0 && r[p] == 0) p = 0;//如果在叶子上
			else if(l[p] == 0 || r[p] == 0) p = l[p] | r[p];//如果在链上，直接为儿子即可
			else {replace(r[p], p);pushup(p);}
		}
		else
		{
			if(v < w[p]) erase(l[p], v);
			else erase(r[p], v);
			pushup(p);
		}
	}
	ll query_kth(const int p, int k)
	{
		if(s[l[p]] >= k) return query_kth(l[p], k);
		else if(s[l[p]] + c[p] >= k) return w[p];
		return query_kth(r[p], k - s[l[p]] - c[p]);
	}
	ll query_rank(const int p, int k)
	{
		if(p == 0) return 1;
		if(k < w[p]) return query_rank(l[p], k);
		if(k == w[p]) return s[l[p]] + 1;
		return s[l[p]] + c[p] + query_rank(r[p], k);
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
		if(l[p]) dfs(l[p]);
		cout << w[p] << ' ';
		if(r[p]) dfs(r[p]);
	}
}bst;
int n, r;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i ++)
	{
		ll od, x;cin >> od >> x;
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
