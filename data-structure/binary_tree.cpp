//二分木の実装例
template<class T>
class BinaryTree{
    struct node{
        T val;
        node *lch,*rch;
    };
    node *root=NULL; //木の根を指すポインタ 最初は木がないので木の根もない=null
    node *find(node *x,T v){
        if(x==NULL||x->val==v)return x;
        if(v<x->val)return find(x->lch,v);
        return find(x->rch,v);
    }
    node *insert(node *x,T v){
        if(x==NULL){
            node *q=new node;
            q->val=v;
            q->lch=q->rch=NULL;
            return q;
        }
        if(v<x->val)x->lch=insert(x->lch,v);
        else if(x->val<v)x->rch=insert(x->rch,v);
        return x;
    }
    node *erase(node *x,T v){
        if(x==NULL)return x;
        if(v<x->val)x->lch=erase(x->lch,v);
        else if(v>x->val)x->rch=erase(x->rch,v);
        else if(x->lch==NULL){
            node *q=x->rch;
            delete x;
            return q;
        }else if(x->lch->rch==NULL){
            node *q=x->lch;
            q->rch=x->rch;
            delete x;
            return q;
        }else {
            node *q;
            for(q=x->lch;q->rch->rch!=NULL;q=q->rch);
            node *r=q->rch;
            q->rch=r->lch;
            r->lch=x->lch;
            r->rch=x->rch;
            delete x;
            return r;
        }
        return x;
    }
public:
     node *find(T v){
         return find(root,v);
     }
     void insert(T v){
         root=insert(root,v);
     }
     void erase(T v){
         root=erase(root,v);
     }
};

