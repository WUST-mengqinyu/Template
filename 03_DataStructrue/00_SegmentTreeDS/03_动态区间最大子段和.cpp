namespace ST {
    struct node{
        ll ans,ls,rs,sum;
    }xx[maxn << 2];
    inline void pushdown(int x){
        xx[x].sum=xx[x<<1].sum+xx[x<<1|1].sum;
        xx[x].ls=max(xx[x<<1].ls,xx[x<<1].sum+xx[x<<1|1].ls);
        xx[x].rs=max(xx[x<<1|1].rs,xx[x<<1|1].sum+xx[x<<1].rs);
        xx[x].ans=max(xx[x<<1].ans,max(xx[x<<1|1].ans,xx[x<<1].rs+xx[x<<1|1].ls));
        return;
    }
    inline void build(int k,int l,int r){
        if(l==r){
            xx[k].ls=xx[k].rs=xx[k].ans=xx[k].sum=0;
            return;
        }
        int mid=l+r>>1;
        build(k<<1,l,mid),build(k<<1|1,mid+1,r);
        pushdown(k);
        return;
    }
    inline void change(int k,int l,int r,int x,int y,int w){ // 1, 1, n
        if(x<=l&&r<=y){
            xx[k].ls += w;
            xx[k].rs += w;
            xx[k].ans += w;
            xx[k].sum += w;
//            xx[k].ls=xx[k].rs=xx[k].ans=xx[k].sum=w;
            return;
        }
        int mid=l+r>>1;
        if(x<=mid) change(k<<1,l,mid,x,y,w);
        if(mid<y) change(k<<1|1,mid+1,r,x,y,w);
        pushdown(k);
        return;
    }
    inline node query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y) {
            return xx[k];
        }
        int mid=l+r>>1;
        if(x<=mid&&!(mid<y)) return query(k<<1,l,mid,x,y);
        else if(!(x<=mid)&&mid<y) return query(k<<1|1,mid+1,r,x,y);
        else{
            node st,t1=query(k<<1,l,mid,x,y),t2=query(k<<1|1,mid+1,r,x,y);
            st.sum=t1.sum+t2.sum;
            st.ls=max(t1.ls,t1.sum+t2.ls);
            st.rs=max(t2.rs,t2.sum+t1.rs);
            st.ans=max(t1.ans,max(t2.ans,t1.rs+t2.ls));
            return st;
        }
    }
}