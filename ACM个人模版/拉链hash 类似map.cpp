struct HashMap //拉链法hash表
{
	static const int MXSZ = 1e7 + 20; //元素总数 查询也会创建元素 能开大就开大
	static const int MOD = 1e7 + 19; //1e3+9 1e4+7 1e6+3 1e7+19 1e8+7
	struct node
	{
		ull key;
		int val, nxt;
	}elem[MXSZ];
	int head[MOD], tot;
	void Init() //注意初始化!!!
	{
		tot = 0;
		memset(head, -1, sizeof(head));
	}
	int& operator [] (ull key)
	{
		int k = key % MOD; //取模位置
		for (int i = head[k]; ~i; i = elem[i].nxt)
			if (elem[i].key == key) //key相等
				return elem[i].val; //返回val引用
		elem[tot].key = key, elem[tot].nxt = head[k], head[k] = tot; //新建项 将原有的接在当前后并记录当前
		return elem[tot++].val = 0; //清空值并返回引用
	}
}mp;