#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int LMAX=28,inf=~0u>>2,b=10;
int a[1<<LMAX],L;
ll M;
void dfs(int d,ll mod,int cnt){
	//if (cnt>(L+1)/2+1)return;
	if (cnt>(L+1)/2)return;
	if (d==L){
		a[mod]=min(a[mod],cnt);
		return;
	}
	dfs(d+1,(mod*b+1)%M,cnt);
	dfs(d+1,(mod*b+2)%M,cnt+1);
	dfs(d+1,(mod*b+4)%M,cnt+2);
	dfs(d+1,(mod*b+8)%M,cnt+3);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (L=1;L<=LMAX;++L){
		int t1=clock();
		int ans=0; M=1uLL<<L;
		for (int i=0;i<(1<<L);++i)a[i]=inf;
		dfs(0,0,0);
		for (int i=0;i<(1<<L);++i){
			//printf("%d %d\n",i,a[i]);
			ans=max(ans,a[i]);
		}
		printf("L=%d ans=%d time=%.2lfs\n",L,ans,double(clock()-t1)/CLOCKS_PER_SEC);
	}
	return 0;
}
