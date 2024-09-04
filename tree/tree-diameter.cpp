/*
- 木の直径とそれを構成するパスをO(N)で求める
*/





int tree_diameter(vvi &G){
	int n=G.size();
	vi seen(n,0);
	queue<int> q;
	q.push(0);
	seen[0]=1;
	int lst=0;
	while(!q.empty()){
		int a=q.front();
		lst=a;
		q.pop();
		for(auto x:G[a]){
			if(seen[x]==0){
				q.push(x);
				seen[x]=1;
			}
		}
	}
	q.push(a);
	int d=0;
	vi dp(n,inf);
	dp[a]=0;
	while(!q.empty()){
		int a=q.front();
		q.pop();
		for(auto x:G[a]){
			if(dp[x]>dp[a]+1){
				dp[x]=dp[a]+1;
				chmax(d,dp[x]);
				q.push(x);
			}
		}
	}
	return d;
}
