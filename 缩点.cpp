#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e4 + 66;
vector<int> G[N], DAG[N], suod;
ll dfn[N], low[N], tot, col[N], su[N], f[N], ans;
//dfn dfs序 low 能到达的最小的 dfs序
// su 缩点后的点权 f 拓扑序dp col 标记在那个强连通分量中
int n, m, a[N], in[N];
stack<int> s;//记录遍历过的所有点
bool ins[N];//判断是否在栈中
void tarjan(int x)
{
	s.push(x);ins[x] = 1; dfn[x] = low[x] = ++ tot;//加入栈
	for(auto y : G[x])
	{
		if(!dfn[y])//如果没遍历过
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);//记录最小dfs序
		}
		else if(ins[y]) low[x] = min(low[x], low[y]);
	}
	if(dfn[x] == low[x])//如果最小的就是自己，说明自己是一个强连通分量的头，没有一个点能从这个点（即自己）出去
	{
		while(s.top() != x)
		{
			col[s.top()] = x;
			su[x] += a[s.top()];
			ins[s.top()] = 0;
			s.pop();
		}
		col[x] = x;su[x] += a[x];ins[x] = 0;s.pop();
	}
}
void topu()
{
	queue<int> q;
	for(auto i : suod) if(!in[i]) q.push(i), f[i] = su[i];
	while(!q.empty())
	{
		int x = q.front();q.pop();
		for(auto p : DAG[x])
		{
			f[p] = max(f[p], f[x] + su[p]);in[p] --;
			if(!in[p]) q.push(p);
		}
	}
	for(auto i : suod) ans = max(ans, f[i]);
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	for(int i = 1;i <= m;i ++)
	{
		int x, y;cin >> x >> y;
		G[x].push_back(y);
	}
	for(int i = 1;i <= n;i ++) if(!dfn[i]) tarjan(i);
	for(int i = 1;i <= n;i ++) if(col[i] == i) suod.push_back(i);
	for(int i = 1;i <= n;i ++) for(auto j : G[i]) if(col[j] != col[i]) DAG[col[i]].push_back(col[j]), in[col[j]] ++;
	topu();
	return 0;
}
