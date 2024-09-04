struct edge{int to, cap, cost, rev; };

int V; //頂点数
vector<edge> G[500]; //(MAX_V)
int h[500]; //ポテンシャル
int dist[500]; //最短距離
int prevv[500], preve[500]; //直前の頂点と辺

//無向辺の場合は下。有向辺の場合は逆向きのcapを0にする
void add_edge(int from, int to, int cap, int cost){
G[from].pb((edge){to,cap,cost,G[to].size()});
G[to].pb((edge){from,0,-cost,G[from].size()-1});
}

//sからtへの流量fの最小費用流(流せない場合は-1を返す)
int min_cost_flow(int s, int t, int f){
    int res=0;
    fill(h,h+V,INF); //inf はintでとる
    while(f>0){
        priority_queue<P, vector<P>, greater<P>> que;
        fill(dist,dist+V, INF);
        dist[s]=0;
        que.push(P(0,s));
        while(!que.empty()){
            P p=que.top(); que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
            for(int i=0;i<G[v].size();i++){
                edge &e=G[v][i];
                if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if(dist[t]==INF) return -1;
        for(int v=0;v<V;v++) h[v]+=dist[v];

        int d=f;
        for(int v=t;v!=s;v=prevv[v]){
            d=min(d,G[prevv[v]][preve[v]]);
        }
        f -= d;
        res += d*h[t];
        for(int v=t; v!=s;v=prevv[v]){
            edge &e =G[prevv[v]][preve[v]];
            e.cap -=d;
            G[v][e.rev].cap +=d;
        }
    }
    return res;
}

/* 最小費用流
有向グラフにおいて、各辺には「頂点uからvまで水をmaxでcapだけ
流せて、単位量流すコストがcost」の情報がある
→SからTまでFだけ流す時、最小コストCはいくらか?

<方針(最短路反復)>
0. まず、(u,v,cap,cost)の辺を張る時に逆辺(v,u,0,-cost)も張る
1. Sからcap>0の辺だけを使って、S→Tを現時点で最も安く流せるパスを
   1つ見つけ、そのパスに流せるだけ流す(逆辺も含む)
   パス上の辺のcapの最小値がそこに流せる最大流量fである。
2. 残り流量とコストを更新する(F←F-f, C←C+f×パス上のcost和)
3. パス上の全ての辺のcapをfだけ減らし、それらの逆辺のcapをfだけ増やす

1-3をF=0になるまで繰り返すとCが答えとなる
(O(FElogV))

- 最大費用流の形は、辺のcostに対し十分大きいBIGに対して
  BIG-costとして最小費用流を解くことで求められる

(書き方の例はABC247G)
//

//二部グラフの重み付きマッチングは最小費用流で解ける!
