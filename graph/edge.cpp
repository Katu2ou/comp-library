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

