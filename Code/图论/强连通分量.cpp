struct SCC
{
	int n,cur,cnt;
	vector<vector<int>> adj;
	vector<int> stk,dfn,low,bel;

	SCC() {}
	SCC(int n) { init(n); }

	void init(int n)
	{
		this->n=n;
		adj.assign(n,{});
		stk.clear();
		dfn.assign(n,-1);
		low.resize(n);
		bel.assign(n,-1);
		cur=cnt=0;
	}

	void add(int u,int v) { adj[u].push_back(v); }

	void dfs(int x)
	{
		dfn[x]=low[x]=cur++;
		stk.push_back(x);
		for (auto y:adj[x])
		{
			if (dfn[y]==-1)
			{
				dfs(y);
				low[x]=min(low[x],low[y]);
			}
			else if (bel[y]==-1) low[x]=min(low[x],dfn[y]);
		}
		if (dfn[x]==low[x])
		{
			int y;
			do
			{
				y=stk.back();
				bel[y]=cnt;
				stk.pop_back();
			} while (y!=x);
			cnt++;
		}
	}

	vector<int> work()
	{
		for (int i=0;i<n;i++)
			if (dfn[i]==-1) dfs(i);
		return bel;
	}

	struct Graph
	{
		int n;
		vector<pair<int,int>> edges;
		vector<int> siz,cnte;
	};

	Graph compress()
	{
		Graph G;
		G.n=cnt;
		G.siz.resize(cnt);
		G.cnte.resize(cnt);
		for (int i=0;i<n;i++)
		{
			G.siz[bel[i]]++;
			for (auto j:adj[i])
				if (bel[i]!=bel[j])
					G.edges.emplace_back(bel[j],bel[i]);
		}
		return G;
	};
};
