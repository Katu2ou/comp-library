//普通にpair型で書く
//V 頂点数
//G vector<vector<pii>>型のグラフ(G[i][j]は{長さ, 行き先})を表す (cost,to)
// vi d(V,inf)は最短距離を表す
//queに入れるのは(その頂点までの最短距離, 頂点)の組
//(長さをfirst、頂点をsecondにする! priority queueでの順番を決めるため長さがfirstになっている必要がある)
//始点s, グラフG, 頂点数nを引数に取る。各頂点への最短距離を含む配列dを返す。
template<typename T>
vector<T> dijkstra(int s, vector<vector<pair<T,int>>> &G){
    int n=G.size();
    priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> que;
    vector<T> d(n,inf); //llならINFに
    d[s]=0;
    que.push({0,s});
while(!que.empty()){
    pair<T,int> p=que.top(); que.pop();
    int v=p.second;
    if(d[v]<p.first) continue;
    for(int i=0;i<G[v].size();i++){
        pair<T,int> e=G[v][i];
        if(d[e.second]>d[v]+e.first){
            d[e.second]=d[v]+e.first;
            que.push({d[e.second], e.second});
        }
    }
}
return d;
}


//構造体
//Edgeの例
struct Edge{
    int from, to;
    ll cost;
    int color;
    int index;
    bool operator<(const Edge& o) const{
        return cost<o.cost; 
    }
};


vector<ll> dijkstra(int s, vector<vector<Edge>> &G){
   int n=G.size();
    priority_queue<pll, vector<pll>, greater<pll>> que;
    vector<ll> d(n,INF);
    d[s]=0;
    que.push(pii(0,s));
while(!que.empty()){
    pll p=que.top(); que.pop();
    ll v=p.second;
    if(d[v]<p.first) continue;
    for(int i=0;i<G[v].size();i++){
        Edge e=G[v][i];
        if(d[e.to]>d[v]+e.cost){
            d[e.to]=d[v]+e.cost;
            que.push(make_pair(d[e.to],e.to));
        }
    }
}
return d;
}

//経路復元
//グラフGの逆辺からなるグラフRGを用いる
//入力: 始点・終点・グラフ・逆グラフ
//出力: (始点から各点までの最短距離),(始点から終点までの1つの最短経路の頂点番号リスト)
pair<vector<ll>,vector<int>> dijkstra_route(int s, int g, vector<vector<Edge>> &G, vector<vector<Edge>> &RG){
    int n=G.size();
    priority_queue<pll, vector<pll>, greater<pll>> que;
    vector<ll> d(n,INF);
    d[s]=0;
    que.push(pii(0,s));
while(!que.empty()){
    pll p=que.top(); que.pop();
    ll v=p.second;
    if(d[v]<p.first) continue;
    for(int i=0;i<G[v].size();i++){
        Edge e=G[v][i];
        if(d[e.to]>d[v]+e.cost){
            d[e.to]=d[v]+e.cost;
            que.push(pii(d[e.to], e.cost));
        }
    }
}
    vector<int> route;
    if(d[g]==INF) return make_pair(d,route); //s,t間が連結でない時にすぐに返す
    int nowind=g;
    route.push_back(nowind);
    while(nowind!=s){
        for(auto e:RG[nowind]){
            if(d[nowind]==d[e.to]+e.cost){
                nowind=e.to;
                route.push_back(nowind);
                break;
            }
        }
    }
    reverse(route.begin(),route.end());
    return make_pair(d,route);
}
