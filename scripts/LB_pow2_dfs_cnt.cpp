#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int LMAX=28,inf=~0u>>2,b=10;
int a[1<<LMAX],L;
ll M;
void dfs(int d,ll mod,int cnt){
	if (cnt>L)return;
	if (d==L){
		if (cnt<=L)++a[mod];
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
		int mi=inf,ma=0; M=1uLL<<L;
		for (int i=0;i<(1<<L);++i)a[i]=0;
		dfs(0,0,0);
		for (int i=0;i<(1<<L);++i){
			//printf("%d %d\n",i,a[i]);
			mi=min(mi,a[i]);
			ma=max(ma,a[i]);
			//if (a[i]<=1)printf("%d %d\n",i,a[i]);
		}
		printf("L=%d mi=%d ma=%d time=%.2lfs\n",L,mi,ma,double(clock()-t1)/CLOCKS_PER_SEC);
	}
	return 0;
}
