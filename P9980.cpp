#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1000;
bitset<N> b[N];
int n, ans;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1;i < n;i ++)
	{
		string s;cin >> s;
		for(int j = 0;j < s.size();j ++) if(s[j] == '1')b[i].set(i + j + 1);
	}
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
			if(b[j][i]) b[j] ^= b[i];
	for(int i = 1;i <= n;i ++)
		for(int j = i + 1;j <= n;j ++)
			if(b[i][j] ^ b[j][i])
				ans ++;
	cout << ans << '\n';
	return 0;
}
