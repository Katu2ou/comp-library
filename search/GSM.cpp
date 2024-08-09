//黄金分割探索
//狭義な単峰性のある列に対して、その最大値を求める 三分探索より早い
/*
アルゴリズム
1: 

*/

//入力: 単峰性のあるvector 
//出力: 最大値とそのindex
template<typename T> 
pair<int,T> GSM(vector<T> &vec){
    int n = vec.size();
    if(n==1){
        return make_pair(0,vec[0]);
    }
    if(n==2){
        if(vec[0]>vec[1]) return make_pair(0,vec[0]);
        else return make_pair(1,vec[1]);
    }
    vector<int> Fib(40);
    Fib[0]=1;
    Fib[1]=1;
    for(int i=2;i<40;i++){
        Fib[i]=Fib[i-1]+Fib[i-2];
    }
    int Fibind = 0;
    while(n+2>Fib[Fibind]){
        Fibind++;
    }
    vector<T> vec2(Fib[Fibind]);
    vec2[0] = -inf;
    for(int i=1;i<=n;i++){
        vec2[i]=vec[i];
    }
    for(int i=n+1;i<=Fib[Fibind];i++){
        vec2[i]=-inf-i;
    }
    int l = Fib[Fibind-2];
    int r = Fib[Fibind-2]+Fib[Fibind-3];
    T maxv = vec2[0];
    int maxind = 0;
    while(Fibind>2){
        if(vec2[l]>vec2[r]){
            maxv = vec2[l];
            r = l;
            if(Fibind>3) l = l-Fib[Fibind-3];
        }
        else{
            maxv = vec2[r];
            l = r;
            if(Fibind>3) r = r+Fib[Fibind-3];
        }
        Fibind--;
        if(maxv < vec2[l]){
            maxv = vec2[l];
            maxind = l;
        }
    }

    return make_pair(maxind-1,maxv);

}