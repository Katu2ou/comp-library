/*
複素数を用いた幾何ライブラリ
    - 点/等号判定
    - c++の関数
    - 単位ベクトル化/法線ベクトル/
    - 内積/外積/回転
    - ラジアン・度変換
    - 直線/線分
    - 円
    - 射影/反射
    - 点の回転方向
    - 直交/平行判定
    - 線分の交差判定
    - 直線/線分の交点
    - 線分と点の距離
    - 線分と線分の距離
    - 多角形の面積
    - 凸判定
    - 多角形に点が含まれるか
    - 凸包
    - 2円の交差判定
    - 内心
    - 円と直線の交点
    - 円と円の交点
    - 点pを通る円cの接線


long double型を使っているので境界などでの誤差に注意

*/

//点(a,b)=a+bi
using Point = complex<long double>;
typedef Point pt;
const long double EPS = 1e-10;
const long double PI =3.1415926535;

inline bool equal(const long double &a, const long double &b) {
    return fabs(a - b) < EPS;
}

// //各種関数
// Point a=Point(1,2);
// a.real() real(a) //実部
// a.imag() imag(a) //虚部
// abs(a) //絶対値
// arg(a) //偏角
// norm(a) //複素数体のノルム
// conj(a) //共役複素数
// proj(a) //リーマン球面への射影を得る
// polar(a) //複素数を極形式で指定して作る

// 単位ベクトル(unit vector)を求める
Point unitVector(const Point &a) { return a / abs(a); }

// 法線ベクトル(normal vector)を求める
// 90度回転した単位ベクトルをかける
// -90度がよければPoint(0, -1)をかける
Point normalVector(const Point &a) { return a * Point(0, 1); }

// 内積(dot product) : a・b = |a||b|cosΘ
long double dot(const Point &a, const Point &b) {
    return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積(cross product) : a×b = |a||b|sinΘ
long double cross(const Point &a, const Point &b) {
    return (a.real() * b.imag() - a.imag() * b.real());
}

// 点pを反時計回りにtheta度回転
Point rotate(const Point &p, const long double &theta) {
    return Point(cos(theta) * p.real() - sin(theta) * p.imag(),
                 sin(theta) * p.real() + cos(theta) * p.imag());
}    

// ラジアン->度
long double radianToDegree(const long double &radian) { return radian * 180.0 / PI; }

// 度->ラジアン
long double degreeToRadian(const long double &degree) { return degree * PI / 180.0; }

// Line : 直線を表す構造体
// b - a で直線・線分を表せる
struct Line {
    Point a, b;
    Line() = default;
    Line(Point a, Point b) : a(a), b(b) {}
    // Ax+By=C
    Line(long double A, long double B, long double C) {
        if(equal(A, 0)) {
            a = Point(0, C / B), b = Point(1, C / B);
        } else if(equal(B, 0)) {
            b = Point(C / A, 0), b = Point(C / A, 1);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
};

// Segment : 線分を表す構造体
// Lineと同じ
struct Segment : Line {
    Segment() = default;

    Segment(Point a, Point b) : Line(a, b) {}
};

// Circle : 円を表す構造体
// pが中心の位置ベクトル、rは半径
struct Circle {
    Point p;
    long double r;

    Circle() = default;

    Circle(Point p, long double r) : p(p), r(r) {}
};

// 射影(projection)
// 直線(線分)lに点pから引いた垂線の足を求める
Point projection(const Line &l, const Point &p) {
    long double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
    long double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

// 反射(reflection)
// 直線lを対称軸として点pと線対称の位置にある点を求める
Point reflection(const Line &l, const Point &p) {
    return p + (projection(l, p) - p) * (long double)2.0;
}

// 点の回転方向
// 点a, b, cの位置関係について(aが基準点)
int ccw(const Point &a, Point b, Point c) {
    b -= a, c -= a;
    // 点a, b, c が
    // 反時計回りの時、
    if(cross(b, c) > EPS) {
        return 1;
    }
    // 時計回りの時、
    if(cross(b, c) < -EPS) {
        return -1;
    }
    // c, a, bがこの順番で同一直線上にある時、
    if(dot(b, c) < 0) {
        return 2;
    }
    // a, b, cがこの順番で同一直線上にある場合、
    if(norm(b) < norm(c)) {
        return -2;
    }
    // cが線分ab上にある場合、
    return 0;
}

// 2直線の直交判定 : a⊥b <=> dot(a, b) = 0
bool isOrthogonal(const Line &a, const Line &b) {
    return equal(dot(a.b - a.a, b.b - b.a), 0);
}
// 2直線の平行判定 : a//b <=> cross(a, b) = 0
bool isParallel(const Line &a, const Line &b) {
    return equal(cross(a.b - a.a, b.b - b.a), 0);
}

// 線分sと線分tが交差しているかどうか
bool isIntersect(const Segment &s, const Segment &t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
           ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

// 直線s, tの交点の計算
Point crossPoint(const Line &s, const Line &t) {
    long double d1 = cross(s.b - s.a, t.b - t.a);
    long double d2 = cross(s.b - s.a, s.b - t.a);
    if(equal(abs(d1), 0) && equal(abs(d2), 0)) {
        return t.a;
    }
    return t.a + (t.b - t.a) * (d2 / d1);
}

// 線分s, tの交点の計算
Point crossPoint(const Segment &s, const Segment &t) {
    return crossPoint(Line(s), Line(t));
}

// 線分lと点pの距離を求める
// 定義：点pから「線分lのどこか」への最短距離
long double distanceBetweenSegmentAndPoint(const Segment &l, const Point &p) {
    if(dot(l.b - l.a, p - l.a) < EPS) {
        return abs(p - l.a);
    }
    if(dot(l.a - l.b, p - l.b) < EPS) {
        return abs(p - l.b);
    }
    return abs(cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
}

// 線分sとtの距離
long double distanceBetweenSegments(const Segment &s, const Segment &t) {
    if(isIntersect(s, t)) {
        return (long double)(0);
    }
    long double ans = distanceBetweenSegmentAndPoint(s, t.a);
    chmin(ans, distanceBetweenSegmentAndPoint(s, t.b));
    chmin(ans, distanceBetweenSegmentAndPoint(t, s.a));
    chmin(ans, distanceBetweenSegmentAndPoint(t, s.b));
    return ans;
}

// 多角形の面積を求める
long double PolygonArea(const vector<Point> &p) {
    long double res = 0;
    int n = p.size();
    for(int i = 0; i < n - 1; i++) {
        res += cross(p[i], p[i + 1]);
    }
    res += cross(p[n - 1], p[0]);
    return res * 0.5;
}

// 凸多角形かどうか
bool isConvex(const vector<Point> &p) {
    int n = p.size();
    int now, pre, nxt;
    for(int i = 0; i < n; i++) {
        pre = (i - 1 + n) % n;
        nxt = (i + 1) % n;
        now = i;
        if(ccw(p[pre], p[now], p[nxt]) == -1) {
            return false;
        }
    }
    return true;
}

// 多角形gに点pが含まれているか?
// 含まれる:2, 辺上にある:1, 含まれない:0
int isContained(const vector<Point> &g, const Point &p) {
    bool in = false;
    int n = (int)g.size();
    for(int i = 0; i < n; i++) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if(imag(a) > imag(b)) {
            swap(a, b);
        }
        if(imag(a) <= EPS && EPS < imag(b) && cross(a, b) < -EPS) {
            in = !in;
        }
        if(cross(a, b) == 0 && dot(a, b) <= 0) {
            return 1;
        }
    }
    return (in ? 2 : 0);
}

// 凸包 O(NlogN)
vector<Point> ConvexHull(vector<Point> &p) {
    int n = (int)p.size(), k = 0;
    sort(all(p), [](const Point &a, const Point &b) {
        return (real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b));
    });
    vector<Point> ch(2 * n);
    // 一直線上の3点を含める -> (< -EPS)
    // 含めない -> (< EPS)
    for(int i = 0; i < n; ch[k++] = p[i++]) { // lower
        while(k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS)
            --k;
    }
    for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) { // upper
        while(k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS)
            --k;
    }
    ch.resize(k - 1);
    return ch;
}

// 2つの円の交差判定
// 返り値は共通接線の数
int isIntersect(const Circle &c1, const Circle &c2) {
    long double d = abs(c1.p - c2.p);
    // 2つの円が離れている場合
    if(d > c1.r + c2.r + EPS) {
        return 4;
    }
    // 外接している場合
    if(equal(d, c1.r + c2.r)) {
        return 3;
    }
    // 内接している場合
    if(equal(d, abs(c1.r - c2.r))) {
        return 1;
    }
    // 内包している場合
    if(d < abs(c1.r - c2.r) - EPS) {
        return 0;
    }
    return 2;
}

//仮
long double distanceBetweenLineAndPoint(const Line &l, pt a){
	return 0.1;
}
// 三角形の内心
Circle inCircle(const Point &a, const Point &b, const Point &c) {
     long double A = abs(b - c), B = abs(a - c), C = abs(a - b);
     Point p(A * real(a) + B * real(b) + C * real(c),
                 A * imag(a) + B * imag(b) + C * imag(c));
     p /= (A + B + C);
     long double r = distanceBetweenLineAndPoint(Line(a, b), p);
     return Circle(p, r);
}

// 円cと直線lの交点
vector<Point> crossPoint(const Circle &c, const Line &l) {
    vector<Point> res;
    long double d = distanceBetweenLineAndPoint(l, c.p);
    // 交点を持たない
    if(d > c.r + EPS) {
        return res;
    }
    // 接する
    Point h = projection(l, c.p);
    if(equal(d, c.r)) {
        res.emplace_back(h);
        return res;
    }
    Point e = unitVector(l.b - l.a);
    long double ph = sqrt(c.r * c.r - d * d);
    res.emplace_back(h - e * ph);
    res.emplace_back(h + e * ph);
    return res;
}

// 2つの円の交点
vector<Point> crossPoint(const Circle &c1, const Circle &c2) {
    vector<Point> res;
    int mode = isIntersect(c1, c2);
    // 2つの中心の距離
    long double d = abs(c1.p - c2.p);
    // 2円が離れている場合
    if(mode == 4) {
        return res;
    }
    // 1つの円がもう1つの円に内包されている場合
    if(mode == 0) {
        return res;
    }
    // 2円が外接する場合
    if(mode == 3) {
        long double t = c1.r / (c1.r + c2.r);
        res.emplace_back(c1.p + (c2.p - c1.p) * t);
        return res;
    }
    // 内接している場合
    if(mode == 1) {
        if(c2.r < c1.r - EPS) {
            res.emplace_back(c1.p + (c2.p - c1.p) * (c1.r / d));
        } else {
            res.emplace_back(c2.p + (c1.p - c2.p) * (c2.r / d));
        }
        return res;
    }
    // 2円が重なる場合
    long double rc1 = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * d);
    long double rs1 = sqrt(c1.r * c1.r - rc1 * rc1);
    if(c1.r - abs(rc1) < EPS) {
        rs1 = 0;
    }
    Point e12 = (c2.p - c1.p) / abs(c2.p - c1.p);
    res.emplace_back(c1.p + rc1 * e12 + rs1 * e12 * Point(0, 1));
    res.emplace_back(c1.p + rc1 * e12 + rs1 * e12 * Point(0, -1));
    return res;
}

// 点pを通る円cの接線
// 2本あるので、接点のみを返す
vector<Point> tangentToCircle(const Point &p, const Circle &c) {
    return crossPoint(c, Circle(p, sqrt(norm(c.p - p) - c.r * c.r)));
}

vector<Line> tangent(const Circle &a, const Circle &b) {
    vector<Line> ret;
    // 2円の中心間の距離
    long double g = abs(a.p - b.p);
    // 円が内包されている場合
    if(equal(g, 0)) {
        return ret;
    }
    Point u = unitVector(b.p - a.p);
    Point v = rotate(u, PI / 2);
    for(int s : {-1, 1}) {
        long double h = (a.r + b.r * s) / g;
        if(equal(h * h, 1)) {
            ret.emplace_back(a.p + (h > 0 ? u : -u) * a.r,
                             a.p + (h > 0 ? u : -u) * a.r + v);

        } else if(1 - h * h > 0) {
            Point U = u * h, V = v * sqrt(1 - h * h);
            ret.emplace_back(a.p + (U + V) * a.r, b.p - (U + V) * (b.r * s));
            ret.emplace_back(a.p + (U - V) * a.r, b.p - (U - V) * (b.r * s));
        }
    }
    return ret;
}


int main(){
int n;
cin>>n;
vector<pt> vec;
rep(i,n){
long double a,b;cin>>a>>b;
complex<long double> cp(a,b);
vec.pb(cp);
}

if(n==2){
	cout<<0.5<<endl;
	cout<<0.5<<endl;
	return 0;
}

vector<pt> cpvec=vec;
vector<Point> ansv=ConvexHull(vec);
vector<long double> ans(n);
fill(ans.begin(),ans.end(),2.0);
for(int i=0;i<ansv.size();i++){
for(int j=0;j<n;j++){
	if(ansv[i]==cpvec[j]){
		if(i>=1 && i<=ansv.size()-2)
		ans[j]=PI-acos(dot(ansv[i-1]-ansv[i],ansv[i+1]-ansv[i])/(abs(ansv[i-1]-ansv[i])*abs(ansv[i+1]-ansv[i])));
		else if(i==0)
		ans[j]=PI-acos(dot(ansv[n-1]-ansv[i],ansv[i+1]-ansv[i])/(abs(ansv[n-1]-ansv[i])*abs(ansv[i+1]-ansv[i])));
        else
		ans[j]=acos(dot(ansv[i-1]-ansv[i],ansv[0]-ansv[i])/(abs(ansv[i-1]-ansv[i])*abs(ansv[0]-ansv[i])));
		ans[j]=ans[j]/(2*PI);
		break;
	}
}
}

for(int i=0;i<n;i++){
	if(ans[i]==2.0){ans[i]=0.0;}
}

dcout;
for(int i=0;i<n;i++){
cout<<ans[i]<<endl;
}

return 0;
}





//その他(複素数でなく定義)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
	long long px, py;
};

Point operator+(const Point& a1, const Point& a2) {
	return Point{ a1.px + a2.px, a1.py + a2.py };
}

Point operator-(const Point& a1, const Point& a2) {
	return Point{ a1.px - a2.px, a1.py - a2.py };
}

bool operator<(const Point& a1, const Point& a2) {
	if (a1.px < a2.px) return true;
	if (a1.px > a2.px) return false;
	if (a1.py < a2.py) return true;
	return false;
}

// 点 p1 と p2 の外積を求める
long long crs(Point p1, Point p2) {
	return p1.px * p2.py - p1.py * p2.px;
}

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

long long N;
Point G[100009];

int main() {
	// Step #1. 入力
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> G[i].px >> G[i].py;
	sort(G + 1, G + N + 1);

	// Step #2. 凸包を求める
	vector<Point> G1, G2, Totsuhou;
	G1.push_back(G[1]); G2.push_back(G[1]);
	G1.push_back(G[2]); G2.push_back(G[2]);
	for (int i = 3; i <= N; i++) {
		while (G1.size() >= 2 && crs(G1[G1.size() - 1] - G1[G1.size() - 2], G[i] - G1[G1.size() - 1]) <= 0) G1.pop_back();
		while (G2.size() >= 2 && crs(G2[G2.size() - 1] - G2[G2.size() - 2], G[i] - G2[G2.size() - 1]) >= 0) G2.pop_back();
		G1.push_back(G[i]);
		G2.push_back(G[i]);
	}
	for (int i = 0; i < G1.size(); i++) Totsuhou.push_back(G1[i]);
	for (int i = (int)G2.size() - 2; i >= 1; i--) Totsuhou.push_back(G2[i]);

	// Step #3. 辺上の格子点の数を求める
	long long EdgePoint = Totsuhou.size();
	for (int i = 0; i < Totsuhou.size(); i++) {
		long long ax = Totsuhou[(i + 0) % Totsuhou.size()].px, ay = Totsuhou[(i + 0) % Totsuhou.size()].py;
		long long bx = Totsuhou[(i + 1) % Totsuhou.size()].px, by = Totsuhou[(i + 1) % Totsuhou.size()].py;
		long long vx = abs(bx - ax);
		long long vy = abs(by - ay);
		long long r = gcd(vx, vy);
		EdgePoint += (r - 1LL);
	}

	// Step #4. 多角形の面積（を 2 倍した値）を求める
	long long Area = 0;
	for (int i = 0; i < Totsuhou.size(); i++) {
		long long ax = Totsuhou[(i + 0) % Totsuhou.size()].px, ay = Totsuhou[(i + 0) % Totsuhou.size()].py;
		long long bx = Totsuhou[(i + 1) % Totsuhou.size()].px, by = Totsuhou[(i + 1) % Totsuhou.size()].py;
		Area += (bx - ax) * (by + ay);
	}
	Area = abs(Area);

	// Step #5. 答えを求める
	long long Answer = Area + EdgePoint + 2LL;
	cout << (Answer / 2LL) - N << endl;
	return 0;
}
