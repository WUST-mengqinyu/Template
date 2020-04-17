const int maxn=1000+10;
const int inf=0x3f3f3f3f;

int n;
int lx[maxn],ly[maxn],edge[maxn][maxn];
int match[maxn],delta;
bool vx[maxn],vy[maxn];

bool dfs(int x)	//DFS增广，寻找相等子图的完备匹配
{
	vx[x]=true;
	for(int y=1;y<=n;y++)
	{
		if(!vy[y])
		{
			int tmp=lx[x]+ly[y]-edge[x][y];
			if(!tmp)	//edge(x,y)为可行边
			{
				vy[y]=true;
				if(!match[y]||dfs(match[y]))
				{
					match[y]=x;
					return true;
				}
			}
			else delta=min(delta,tmp);
		}
	}
	return false;
}

void KM()
{
	for(int i=1;i<=n;i++)	//初始化可行顶标的值
	{
		lx[i]=-inf;
		ly[i]=0;
		for(int j=1;j<=n;j++)
			lx[i]=max(lx[i],edge[i][j]);
	}
	memset(match,0,sizeof(match));
	for(int x=1;x<=n;x++)
	{
		for(;;)
		{
			delta=inf;
			memset(vx,0,sizeof(vx));
			memset(vy,0,sizeof(vy));
			if(dfs(x)) break;
			for(int i=1;i<=n;i++)	//修改顶标
			{
				if(vx[i]) lx[i]-=delta;
				if(vy[i]) ly[i]+=delta;
			}
		}
	}
}