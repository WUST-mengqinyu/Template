// Treap
//
// Todas as operacoes custam
// O(log(n)) com alta probabilidade, exceto meld
// meld custa O(log^2 n) amortizado com alta prob.,
// e permite unir duas treaps sem restricao adicional
// Na pratica, esse meld tem constante muito boa e
// o pior caso eh meio estranho de acontecer

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
	struct node {
		node *l, *r;
		int p, sz;
		T val, mi;
		node(T v) : l(NULL), r(NULL), p(rng()), sz(1), val(v), mi(v) {}
		void update() {
			sz = 1;
			mi = val;
			if (l) sz += l->sz, mi = min(mi, l->mi);
			if (r) sz += r->sz, mi = min(mi, r->mi);
		}
	};

	node* root;

	treap() { root = NULL; }
	treap(const treap& t) {
		throw logic_error("Nao copiar a treap!");
	}
	~treap() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	int size(node* x) { return x ? x->sz : 0; }
	int size() { return size(root); }
	void join(node* l, node* r, node*& i) { // assume que l < r
		if (!l or !r) return void(i = l ? l : r);
		if (l->p > r->p) join(l->r, r, l->r), i = l;
		else join(l, r->l, r->l), i = r;
		i->update();
	}
	void split(node* i, node*& l, node*& r, T v) {
		if (!i) return void(r = l = NULL);
		if (i->val < v) split(i->r, i->r, r, v), l = i;
		else split(i->l, l, i->l, v), r = i;
		i->update();
	}
	int count(node* i, T v) {
		if (!i) return 0;
		if (i->val == v) return 1;
		if (v < i->val) return count(i->l, v);
		return count(i->r, v);
	}
	void index_split(node* i, node*& l, node*& r, int v, int key = 0) {
		if (!i) return void(r = l = NULL);
		if (key + size(i->l) < v) index_split(i->r, i->r, r, v, key+size(i->l)+1), l = i;
		else index_split(i->l, l, i->l, v, key), r = i;
		i->update();
	}
	int count(T v) {
		return count(root, v);
	}
	void insert(T v) {
		if (count(v)) return;
		node *L, *R;
		split(root, L, R, v);
		node* at = new node(v);
		join(L, at, L);
		join(L, R, root);
	}
	void erase(T v) {
		node *L, *M, *R;
		split(root, M, R, v+1), split(M, L, M, v);
		if (M) delete M;
		M = NULL;
		join(L, R, root);
	}
	void meld(treap& t) { // segmented merge
		node *L = root, *R = t.root;
		root = NULL;
		while (L or R) {
			if (!L or (L and R and L->mi > R->mi)) std::swap(L, R);
			if (!R) join(root, L, root), L = NULL;
			else if (L->mi == R->mi) {
				node* LL;
				split(L, LL, L, R->mi+1);
				delete LL;
			} else {
				node* LL;
				split(L, LL, L, R->mi);
				join(root, LL, root);
			}
		}
		t.root = NULL;
	}
};

// Treap Implicita
//
// Todas as operacoes custam
// O(log(n)) com alta probabilidade

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
	struct node {
		node *l, *r;
		int p, sz;
		T val, sub, lazy;
		bool rev;
		node(T v) : l(NULL), r(NULL), p(rng()), sz(1), val(v), sub(v), lazy(0), rev(0) {}
		void prop() {
			if (lazy) {
				val += lazy, sub += lazy*sz;
				if (l) l->lazy += lazy;
				if (r) r->lazy += lazy;
			}
			if (rev) {
				swap(l, r);
				if (l) l->rev ^= 1;
				if (r) r->rev ^= 1;
			}
			lazy = 0, rev = 0;
		}
		void update() {
			sz = 1, sub = val;
			if (l) l->prop(), sz += l->sz, sub += l->sub;
			if (r) r->prop(), sz += r->sz, sub += r->sub;
		}
	};

	node* root;

	treap() { root = NULL; }
	treap(const treap& t) {
		throw logic_error("Nao copiar a treap!");
	}
	~treap() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	int size(node* x) { return x ? x->sz : 0; }
	int size() { return size(root); }
	void join(node* l, node* r, node*& i) { // assume que l < r
		if (!l or !r) return void(i = l ? l : r);
		l->prop(), r->prop();
		if (l->p > r->p) join(l->r, r, l->r), i = l;
		else join(l, r->l, r->l), i = r;
		i->update();
	}
	void split(node* i, node*& l, node*& r, int v, int key = 0) {
		if (!i) return void(r = l = NULL);
		i->prop();
		if (key + size(i->l) < v) split(i->r, i->r, r, v, key+size(i->l)+1), l = i;
		else split(i->l, l, i->l, v, key), r = i;
		i->update();
	}
	void push_back(T v) {
		node* i = new node(v);
		join(root, i, root);
	}
	T query(int l, int r) {
		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		T ans = M->sub;
		join(L, M, M), join(M, R, root);
		return ans;
	}
	void update(int l, int r, T s) {
		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		M->lazy += s;
		join(L, M, M), join(M, R, root);
	}
	void reverse(int l, int r) {
		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		M->rev ^= 1;
		join(L, M, M), join(M, R, root);
	}
};