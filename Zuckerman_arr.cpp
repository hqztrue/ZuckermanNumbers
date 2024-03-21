// Copyright (C) 2024 Qizheng He, <hqztrue@sina.com>
// License: The MIT License (MIT)
// ==================================================
// Algorithm for counting the base-b Zuckerman numbers with exactly n digits.
// Complexity: O~((b-1)^{N/2}).

#include<bits/stdc++.h>
//#include<omp.h>
using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
struct Hash{
	uint S1;
	const static ull MUL=12345678911234567891ull;
	#define H(x) (x*MUL>>S1)
	struct node{
		ull x;
		int y,t;
	}*h;
	int T;
	void init(int S){
		S1=64-S; T=1;
		int n=(1<<S)+105;
		h=new node[n];
		memset(h,0,sizeof(node)*n);
	}
	Hash(int n=1){
		int S=1;
		while ((1<<S)<n*2)++S;
		init(S);
	}
	inline void insert(ull x){
		node *p=h+H(x);
		for (;p->t==T;++p)
			if (p->x==x){++p->y; return;}
		p->t=T; p->x=x; p->y=1;
	}
	inline int find(ull x){
		for (node *p=h+H(x);p->t==T;++p)
			if (p->x==x)return p->y;
		return 0;
	}
	~Hash(){delete[] h;}
	#undef H
};
const int N=105,B=105,b=10;
int n;
ull powb[105],ans;
inline ull mul_mod_ll_asm(ull a,ull b,ull p){
	ull ret;
	__asm__ __volatile__("movq %1,%%rax\n imulq %2\n idivq %3\n":"=d"(ret):"m"(a),"m"(b),"m"(p):"%rax");
	return ret;
}
inline ull C(int n,int m){
	if (n<m)return 0;
	ull res=1;
	for (int i=1;i<=m;++i){
		assert(~0ull/(n-i+1)>=res);
		res=res*(n-i+1)/i;
	}
	return res;
}
unordered_set<ull> products[N];
void DfsProducts(int d,int s,ull M,int n){
	if (d==b-1){
		for (int i=1;i<=s;++i)M*=d;
		products[n].insert(M);
		return;
	}
	for (int i=0;i<=s;++i){
		DfsProducts(d+1,s-i,M,n);
		M*=d;
	}
}
unordered_map<ull,vector<ull>> nums[N];
int nums1=-1;
void DfsNums(int d,ull M,ull x,int n){
	if (d==n){
		nums[n][M].push_back(x);
		return;
	}
	for (int i=1;i<b;++i)
		DfsNums(d+1,M*i,x*b+i,n);
}
ull solve(int n,int n0,ull M){
	ull res=0;
	ull N_low=powb[n-n0];
	for (auto &M_high:products[n0]){
		if (M%M_high)continue;
		ull M_low=M/M_high;
		if (products[n-n0].find(M_low)==products[n-n0].end())continue;
		//meet-in-the-middle
		Hash h(nums[n0][M_high].size());
		++h.T;
		for (auto &u:nums[n0][M_high]){
			ull v=mul_mod_ll_asm(u,N_low,M);
			h.insert(v);
		}
		for (int i=1,t=h.find(0);i<=t;++i)h.insert(M);
		for (auto &u:nums[n-n0][M_low])res+=h.find(M-u%M);
	}
	return res;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	powb[0]=1; for (int i=1;i<=64;++i)powb[i]=powb[i-1]*b;
	products[0].insert(1);
	for (n=1;;++n){
		int t1=clock();
		printf("n=%d\n",n);
		ans=0;
		DfsProducts(1,n,1,n);
		//printf("size=%d\n",products[n].size());
		int n0=n/2;
		while (nums1<max(n0,n-n0))DfsNums(0,1,0,++nums1);
		for (auto &M:products[n]){
			ull res=solve(n,n0,M);
			ans+=res;
		}
		printf("ans=%I64d\n",ans);
		printf("time=%d\n",clock()-t1);
	}
	return 0;
}
