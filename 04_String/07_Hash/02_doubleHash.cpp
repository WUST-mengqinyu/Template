namespace Hash{

    template<class __A,class __B>
    class Hash{
    private:
        static const int size=2000000;
        __B *hash; __A *O; int sz;
    public:
        Hash(int hash_size=size){ sz=hash_size;
            hash=(__B *)malloc(sizeof(__B)*sz);
            O=(__A *)malloc(sizeof(__A)*sz);
            memset(O,0xff,sizeof(__A)*sz);
        }~Hash(){free(O);free(hash);}
        __B &operator [](const __A &_O){
            int loc=_O%sz;
            while(~O[loc]&&O[loc]!=_O){
                ++loc;
                if(loc>sz)loc=0;
            }if(!~O[loc])O[loc]=_O;
            return hash[loc];
        }
        void clear(){memset(O,0xff,sizeof(__A)*sz);}
    };

    struct StringDoubleHashResult{
        int32_t *H1,*H2,c_len,len;
        StringDoubleHashResult(int32_t sz=0){
            len=sz; c_len=0; //cur_len;
            if(len<=0){
                H1=H2=0;
                return;
            }
            H1=(int32_t *)malloc(sizeof(int32_t)*sz);
            H2=(int32_t *)malloc(sizeof(int32_t)*sz);
        }
        ~StringDoubleHashResult(){}
        void clear(){free(H1);free(H2);len=0;H1=H2=0;}
        void resize(int new_len){
            int32_t *T1=(int32_t *)malloc(sizeof(int32_t)*new_len);
            int32_t *T2=(int32_t *)malloc(sizeof(int32_t)*new_len);
            for(int i=0;i<c_len;++i)T1[i]=H1[i],T2[i]=H2[i];
            free(H1);free(H2); H1=T1; H2=T2; len=new_len;
        }
        void erase(int ers_len){//erase suffix
            c_len-=ers_len;
            if(c_len<0)c_len=0;
        }
        //erase prefix not better than reculc
    };

    namespace hash_random{
        const int mod_tot=5;
        const int mod[]={1000000009,1000000007,998244353,917120411,515880193};
    };

    class StringDoubleHash{
    private:
        static const int enable_random=1;
        int32_t sz,HA1,HA2;
        long long B,C;
        int32_t *H1,*H2;
    public:
        StringDoubleHash(int32_t SZ=2e6+5,int32_t ha1=-1,int32_t ha2=-1,int32_t b=-1,int32_t c=-1){
            sz=SZ;
            if(enable_random){
                std::mt19937 rnd(time(0)+19990630);
                int z1= rnd() % hash_random::mod_tot;
                int z2= (z1 +rnd()%(hash_random::mod_tot - 1) + 1) % hash_random::mod_tot;
                if(ha1<0)ha1=hash_random::mod[z1];
                if(ha2<0)ha2=hash_random::mod[z2];
                if(b<0)b=rnd()%114514+23333;
                if(c<0)c=rnd()%1919810+23333;
            } else {
                if(ha1<0)ha1=1e9+7;
                if(ha2<0)ha2=1e9+9;
                if(b<0)b=114514;
                if(c<0)c=1919810;
            }
            HA1=ha1; HA2=ha2; B=b; C=c;
            //cerr<<HA1<<" "<<HA2<<" "<<B<<" "<<C<<endl;
            H1=(int32_t *)malloc(sizeof(int32_t)*sz);
            H2=(int32_t *)malloc(sizeof(int32_t)*sz);
            init_hash_val();
        }
        ~StringDoubleHash(){free(H1);free(H2);}
        void init_hash_val(){
            H1[0]=H2[0]=1;
            for(int32_t i=1;i<sz;++i){
                H1[i]=(H1[i-1]*B)%HA1;
                H2[i]=(H2[i-1]*B)%HA2;
            }
        }
        template <class _Tp>
        StringDoubleHashResult culc_hash(const _Tp &s,int32_t len,int32_t tot_len=-1){
            if(tot_len<0)tot_len=len;
            StringDoubleHashResult R(tot_len);
            if(len<=0)return R;
            R.H1[0]=(s[0]+C)%HA1;
            R.H2[0]=(s[0]+C)%HA2;
            for(int32_t i=1;i<len;++i){
                R.H1[i]=(R.H1[i-1]*B+s[i]+C)%HA1;
                R.H2[i]=(R.H2[i-1]*B+s[i]+C)%HA2;
            }
            R.c_len=len;
            return R;
        }
        // s is the char* first, len is the append length
        template <class _Tp>
        void append(StringDoubleHashResult &R,const _Tp &s,int32_t len){
            if(len<=0)return;
            int t_len=R.len;
            while(R.c_len+len>t_len)t_len<<=1;
            if(t_len>R.len)R.resize(t_len);
            for(int32_t i=R.c_len;i<R.c_len+len;++i){
                if(i==0){
                    R.H1[i]=(s[i-R.c_len]+C)%HA1;
                    R.H2[i]=(s[i-R.c_len]+C)%HA2;
                } else {
                    R.H1[i]=(R.H1[i-1]*B+s[i-R.c_len]+C)%HA1;
                    R.H2[i]=(R.H2[i-1]*B+s[i-R.c_len]+C)%HA2;
                }
            }
            R.c_len+=len;
        }
        void append(StringDoubleHashResult &R, char s){
            int t_len=R.len;
            while(R.c_len+1>t_len)t_len<<=1;
            if(t_len>R.len)R.resize(t_len);
            for(int32_t i=R.c_len;i<R.c_len+1;++i){
                if(i==0){
                    R.H1[i]=(s+C)%HA1;
                    R.H2[i]=(s+C)%HA2;
                } else {
                    R.H1[i]=(R.H1[i-1]*B+s+C)%HA1;
                    R.H2[i]=(R.H2[i-1]*B+s+C)%HA2;
                }
            }
            R.c_len+=1;
        }
        //return hash [l,r)
        ll gethash(const StringDoubleHashResult &R, int32_t l,int32_t r){
            if(l>r||l<0||r-->R.c_len)return -1;//fail
            ll v1=l>0?R.H1[l-1]*(long long)H1[r-l+1]%HA1:0;
            ll v2=l>0?R.H2[l-1]*(long long)H2[r-l+1]%HA2:0;
            v1=R.H1[r]-v1; v2=R.H2[r]-v2;
            if(v1<0)v1+=HA1; if(v2<0)v2+=HA2;
            return v1<<32|v2;
        }
        //merge two hashes as one(s1+s2), but need s2's length
        ll merge_hash(const long long &hs1,const long long &hs2,int lenr){
            int32_t m1=hs1>>32,m2=hs1&0xffffffffLL;
            int32_t m3=hs2>>32,m4=hs2&0xffffffffLL;
            m1=m1*(long long)H1[lenr]%HA1+m3;
            if(m1>=HA1)m1-=HA1;
            m2=m2*(long long)H2[lenr]%HA2+m4;
            if(m2>=HA2)m2-=HA2;
            return (long long)m1<<32|m2;
        }
    };
};