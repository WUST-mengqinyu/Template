const int maxn = 1e7 + 10;
const double Pi = acos(-1.0);

struct complex
{
	double x, y;
	complex (double xx = 0, double yy = 0) { x = xx, y = yy; }
}a[maxn], b[maxn];

complex operator + (complex a, complex b) { return complex(a.x + b.x, a.y + b.y); }
complex operator - (complex a, complex b) { return complex(a.x - b.x, a.y - b.y); }
complex operator * (complex a, complex b) { return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

int n, m;
int l, r[maxn];
int limit;

void FFT(complex *A, int type)
{
	for(int i = 0; i < limit; i ++)
		if(i < r[i]) swap(A[i], A[r[i]]);
	for(int mid = 1; mid < limit; mid <<= 1)
	{
		complex Wn(cos(Pi / mid), type * sin(Pi / mid));
		for(int R = mid << 1, j = 0; j < limit; j += R)
		{
			complex w(1, 0);
			for(int k = 0; k < mid; k ++, w = w * Wn)
			{
				complex x = A[j + k], y = w * A[j + mid + k];
				A[j + k] = x + y;
				A[j + mid + k] = x - y;
			}
		}
	}
}

void mul()
{
	l = 0, limit = 1;
	while(limit <= n + m) limit <<= 1, l ++;
	for(int i = 0; i < limit; i ++)
		r[i] = (r[i >> 1] >> 1) | ( (i & 1) << (l - 1));
	FFT(a, 1);
	FFT(b, 1);
	for(int i = 0; i <= limit; i ++) a[i] = a[i] * b[i];
	FFT(a, -1);
	for(int i = 0; i <= n + m; i ++)
		printf("%d ", (int)(a[i].x / limit + 0.5));
}