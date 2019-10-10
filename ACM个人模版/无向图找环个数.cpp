// 注意图点数的下标从0开始
for(int i=0;i<n;i++)dp[1<<i][i]=1;//初始化
		for(int s=1;s<(1<<n);s++)
	    {
	        for(int u=0;u<n;u++)
	        {
	            if(dp[s][u])
	            {
	                for(auto &v:G[u])
	                {
	                    if((s&-s)>(1<<v)) continue;
	                    if(s&(1<<v))
	                    {
	                        if((s&-s)==(1<<v)) ans+=dp[s][u];
	                    }
	                    else
	                    {
	                    	dp[s|(1<<v)][v]+=dp[s][u];
	                    }
	                }
	            }
	        }
	    }
ans=(ans-m)/2;