//連結とは限らない無向グラフに対し、それを連結成分ごとに分解してそれぞれの頂点集合を返す
    //入力: 無向グラフG
    //出力: 各連結成分ごとの頂点集合のvector


vvi partitioned_graph(vvi& g){
    int n=g.size();
    vi memo(n,-1);
    vvi ans;
    int ind=0;
    rep(i,n){
        if(memo[i]!=-1)continue;
        ans.pb(vi());
        queue<int> que;
        que.push(i);
        while(que.size()){
            int s=que.front();
            que.pop();
            memo[s]=ind;
            ans[ind].pb(s);
            for(auto u:g[s]){
                if(memo[u]==-1){
                    que.push(u);
                }
            }
        }
        ind++;
    }
    return ans;
}
