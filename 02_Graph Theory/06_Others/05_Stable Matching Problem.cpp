const int maxn = 1000 + 10;

int pre[maxn][maxn], order[maxn][maxn], nex[maxn];
int hus[maxn], wife[maxn];
queue<int> que;

void engage(int man, int woman)
{
	int m = hus[woman];
	if(m) wife[m] = 0, q.push(m);
	wife[man] = woman;
	hus[woman] = man;
}

int solve()
{
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n; j ++)
			scanf("%d", &pre[i][j]);	
		nex[i] = 1;
		wife[i] = 0;
		que.push(i);
	}
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n; j ++)
		{
			int x;
			scanf("%d", &x);
			order[i][x] = j;	
		}
		hus[i] = 0;
	}

	while(!que.empty())
	{
		int man = que.front(); que.pop();
		int woman = pre[man][nex[man] ++];
		if(!hus[woman]) engage(man, woman);
		else if(order[woman][man] < order[woman][hus[woman]]) engage(man, woman);
		else que.push(man);
	}
}