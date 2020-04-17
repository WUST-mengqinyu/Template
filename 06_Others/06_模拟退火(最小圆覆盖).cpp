const int maxn = 1e5 + 10;
const double eps = 1e-8;
const double delta = 0.98;
const double inf = 1e18;

struct Point { double x, y; } p[maxn];

double dis(Point A, Point B) { return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)); };

double Simulate_Annea(int n)
{
	Point S;
	S.x = S.y = 0;
	double t = 1000;
	double res = inf;
	while(t > eps)
	{
		int k = 0;
		for(int i = 0; i < n; i ++) if(dis(S, p[i]) > dis(S, p[k])) k = i;
		double d = dis(S, p[k]);
		res = min(res, d);
		S.x += (p[k].x - S.x) / d * t;
		S.y += (p[k].y - S.y) / d * t;
		t *= delta;
	}
	return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%lf%lf", &p[i].x, &p[i].y);
    printf("%.3f\n", Simulate_Annea(n));
    return 0;
}
