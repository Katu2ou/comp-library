//名前がtemplateのmintと被っているので注意(使う時はtemplateの方を削除するなど)

//mint基本
template<unsigned mod=998244353>struct mint {
   unsigned val;
   static unsigned get_mod(){return mod;}
   unsigned inv() const{
      int tmp,a=val,b=mod,x=1,y=0;
      while(b)tmp=a/b,a-=tmp*b,swap(a,b),x-=tmp*y,swap(x,y);
      if(x<0)x+=mod; return x;
   }
   mint():val(0){}
   mint(ll x):val(x>=0?x%mod:mod+(x%mod)){}
   mint pow(ll t){mint res=1,b=*this; while(t){if(t&1)res*=b;b*=b;t>>=1;}return res;}
   mint& operator+=(const mint& x){if((val+=x.val)>=mod)val-=mod;return *this;}
   mint& operator-=(const mint& x){if((val+=mod-x.val)>=mod)val-=mod; return *this;}
   mint& operator*=(const mint& x){val=ll(val)*x.val%mod; return *this;}
   mint& operator/=(const mint& x){val=ll(val)*x.inv()%mod; return *this;}
   mint operator+(const mint& x)const{return mint(*this)+=x;}
   mint operator-(const mint& x)const{return mint(*this)-=x;}
   mint operator*(const mint& x)const{return mint(*this)*=x;}
   mint operator/(const mint& x)const{return mint(*this)/=x;}
   bool operator==(const mint& x)const{return val==x.val;}
   bool operator!=(const mint& x)const{return val!=x.val;}
};

//階乗
template<unsigned mod=998244353>struct factorial {
   using Mint=mint<mod>;
   vector<Mint> Fact, Finv;
public:
   factorial(int maxx){
      Fact.resize(maxx+1),Finv.resize(maxx+1); Fact[0]=Mint(1); rep(i,0,maxx)Fact[i+1]=Fact[i]*(i+1);
      Finv[maxx]=Mint(1)/Fact[maxx]; rrep(i,maxx,0)Finv[i-1]=Finv[i]*i;
   }
   Mint fact(int n,bool inv=0){if(inv)return Finv[n];else return Fact[n];}
   Mint nPr(int n,int r){if(n<0||n<r||r<0)return Mint(0);else return Fact[n]*Finv[n-r];}
   Mint nCr(int n,int r){if(n<0||n<r||r<0)return Mint(0);else return Fact[n]*Finv[r]*Finv[n-r];}
};