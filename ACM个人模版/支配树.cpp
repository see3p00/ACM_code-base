//input : succ
//output dom_t and idom redfn
//notice that the index i in dom_t[i] and dom_t[i][j] is the vertex's timestamp in dfs
//hence you need redfn[i] to find the original vertex
//o(mlogm) where m is the number of edges
//UPD:new version is o(m¦Á(m, n)), the previous version is in comment
/*
 succ数组存的是原图
 fa数组存的是i结点的先驱，在dfs生成树上的父亲
 dfn数组存的是i结点的新编号，redfn存的是i结点的原编号
 prod数组存根据dfs重新排序之后的图
 semi数组存半必经点的新编号，表示的是在dfs树上，节点i的祖先中，可以通过一系列的非树边走到i的，深度最小的祖先，i的直系父亲也可以是半必经点
 bucket数组存的是，以i作为半必经点的点
 idom数组存的是，i的immediate dominator
 anc数组：step3里把点都先当成孤立的森林，然后每访问一个点，就将他和他父亲连边，anc数组存的就是结点的父亲，并且compress用了类似并查集的方式压缩，以此更快速地找到深度最小的祖先
 */
const int vector_num; //max number of vertices

vector<int> succ[vector_num+10], prod[vector_num+10], bucket[vector_num+10], dom_t[vector_num+10];
int semi[vector_num+10], anc[vector_num+10], idom[vector_num+10], best[vector_num+10], fa[vector_num+10];
int dfn[vector_num+10], redfn[vector_num+10];
int child[vector_num+10], size[vector_num+10];
int timestamp;

void dfs(int now) {
	dfn[now] = ++timestamp;
	redfn[timestamp] = now;
	anc[timestamp] = idom[timestamp] = child[timestamp] = size[timestamp] = 0;
	semi[timestamp] = best[timestamp] = timestamp;
	int sz = succ[now].size();
	for(int i = 0; i < sz; ++i) {
		if(dfn[succ[now][i]] == -1) {
			dfs(succ[now][i]);
			fa[dfn[succ[now][i]]] = dfn[now];
		}
		prod[dfn[succ[now][i]]].push_back(dfn[now]);
	}
}

void compress(int now) {
	if(anc[anc[now]] != 0) {
		compress(anc[now]);
		if(semi[best[now]] > semi[best[anc[now]]])
			best[now] = best[anc[now]];
		anc[now] = anc[anc[now]];
	}
}

//eval function of previous version
/*
int eval(int now) {
	if(anc[now] == 0)
		return now;
	compress(now);
	return best[now];
}
*/

inline int eval(int now) {
	if(anc[now] == 0)
		return now;
	else {
		compress(now);
		return semi[best[anc[now]]] >= semi[best[now]] ? best[now]
			: best[anc[now]];
	}
}

inline void link(int v, int w) {
	int s = w;
	while(semi[best[w]] < semi[best[child[w]]]) {
		if(size[s] + size[child[child[s]]] >= 2*size[child[s]]) {
			anc[child[s]] = s;
			child[s] = child[child[s]];
		} else {
			size[child[s]] = size[s];
			s = anc[s] = child[s];
		}
	}
	best[s] = best[w];
	size[v] += size[w];
	if(size[v] < 2*size[w])
		swap(s, child[v]);
	while(s != 0) {
		anc[s] = v;
		s = child[s];
	}
}

void lengauer_tarjan(int n) { // n is the vertices' number
	memset(dfn, -1, sizeof dfn);
	memset(fa, -1, sizeof fa);
	timestamp = 0;
	dfs(n);
	fa[1] = 0;
	for(int w = timestamp; w > 1; --w) {
		int sz = prod[w].size();
		for(int i = 0; i < sz; ++i) {
			int u = eval(prod[w][i]);
			if(semi[w] > semi[u])
				semi[w] = semi[u];
		}
		bucket[semi[w]].push_back(w);
		//anc[w] = fa[w]; link operation for o(mlogm) version
                link(fa[w], w);
		if(fa[w] == 0)
			continue;
		sz = bucket[fa[w]].size();
		for(int i = 0; i < sz; ++i) {
			int u = eval(bucket[fa[w]][i]);
			if(semi[u] < fa[w])
				idom[bucket[fa[w]][i]] = u;
			else
				idom[bucket[fa[w]][i]] = fa[w];
		}
		bucket[fa[w]].clear();
	}
	for(int w = 2; w <= timestamp; ++w) {
		if(idom[w] != semi[w])
			idom[w] = idom[idom[w]];
	}
	idom[1] = 0;
	for(int i = timestamp; i > 1; --i) {
		if(fa[i] == -1)
			continue;
		dom_t[idom[i]].push_back(i);
	}
}
