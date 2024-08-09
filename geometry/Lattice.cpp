///格子点に関する問題(ここで格子点とは整数座標の点のことを指す)

struct point(ll x,ll y){
    point(){}
    point(ll x,ll y):x(x),y(y){}
    point operator+(point p){return point(x+p.x,y+p.y);}
    point operator-(point p){return point(x-p.x,y-p.y);}
    point operator*(ll k){return point(x*k,y*k);}
    point operator/(ll k){return point(x/k,y/k);}
    bool operator==(point p){return x==p.x&&y==p.y;}
    bool operator!=(point p){return !(x==p.x&&y==p.y);}
};

//三角形の面積---の2倍の値---を返す
ll area3(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3){
     return abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
}

//二点を結ぶ線分上の格子点の数(端点を含む) (二点は相異なるとする)
ll latseg(ll x1,ll y1,ll x2,ll y2){
    return gcd(abs(x1-x2),abs(y1-y2))+1;
}

//線分を表すクラス

//直線を表すクラス