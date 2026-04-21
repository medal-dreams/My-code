#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 66, mod = 998244353;
using ll = long long;
string s[N], s1[N], ss, sss;
ll len, tot, now, cp, p[N], nxt[N];
map<string, bool> mp;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	p[1] = 1;
	while(s[tot] != "$") 
	{
		cin >> s[++ tot];
		if(!mp.count(s[tot]))
		{
			ss += ('0' + (++ now));
			mp[s[tot]] = now;
		}
		else ss += '0' + mp[s[tot]];
	}
	tot --;
	mp.clear();
	while(s1[len] != "$") 
	{
		cin >> s1[++ len];
		if(!mp.count(s1[len]))
		{
			sss += ('0' + (++ cp));
			mp[s[len]] = cp;
		}
		else ss += '0' + mp[s[len]];
	}
	len --;
	ss = ' ' + ss, sss = ' ' + sss;
	for(int i = 2, j = 0;i < sss.size();i ++)
	{
		while(j > 0 && sss[i] != sss[j + 1]) j = nxt[j];
		if(sss[i] == sss[j + 1]) j ++;
		nxt[i] = j;
	}
	for(int i = 1, j = 0;i < ss.size();i ++)
	{
		while(j > 0 && (j == (ss.size() - 1) || ss[i] != sss[j + 1])) j = nxt[j];
		if(ss[i] == sss[j + 1]) j ++;
		if(j == (sss.size() - 1)) {cout << (i - sss.size() + 2) << '\n';return 0;}
			
			
	}
	return 0;
}
