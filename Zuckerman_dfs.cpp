// Copyright (C) 2024 Qizheng He, <hqztrue@sina.com>
// License: The MIT License (MIT)
// ==================================================
// Algorithm for counting the base-b Zuckerman numbers with exactly n digits.
// Complexity: O((b-1)^{N/2}*C(N/2+b-2,b-2)) (*b).

#include<bits/stdc++.h>
//#include<omp.h>
using namespace std;
typedef unsigned long long ull;
namespace Hash{
	typedef unsigned int uint;
	const uint S=19,S1=64-S,_inf=~0u>>1;
	const ull MUL=12345678911234567891ull;
	#define H(x) ((ull)x*MUL>>S1)
	struct node{
		ull x;
		int y,t;
	}h[(1<<S)+105];
	int T=1;
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
	#undef H
} using namespace Hash;

const int N=10000005,B=105,b=10;
int c[B],c1[B],c2[B],*c_gen,n,n0,n_gen,p1;
ull p[N],powb[105],ans,S0,M,NLOW;
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
//Generate all possible numbers from a set of digits.
void GenNumsFromSet(int d,ull x){
	if (d==n_gen){
		p[p1++]=x;
		return;
	}
	for (int i=1;i<b;++i)
		if (c_gen[i]){
			--c_gen[i];
			GenNumsFromSet(d+1,x+i*powb[d]);
			++c_gen[i];
		}
}
const int d_thres=4,M_thres=1<<d_thres;
void GenNumsFromSetPrune(int d,ull x){
	if (d==n_gen){
		p[p1++]=x;
		return;
	}
	//if (d==d_thres&&x%M_thres)return;
	for (int i=1;i<b;++i)
		if (c_gen[i]){
			--c_gen[i];
			GenNumsFromSetPrune(d+1,x+i*powb[d]);
			++c_gen[i];
		}
}
//Search for the set of digits used in the higher part.
void DfsHighSet(int d,int s){
	if (d==b-1){
		if (s>c[d])return;
		c1[d]=s;
		//++S0;
		/*ull tmp=1;
		for (int i=1,n1=n0;i<b;++i)tmp*=C(n1,c1[i]),n1-=c1[i];
		S0+=tmp;*/
		//printf("M=%llu\n",M);
		
		//meet-in-the-middle
		for (int i=1;i<b;++i)c2[i]=c[i]-c1[i];
		++T; c_gen=c1; n_gen=n0; p1=0;
		GenNumsFromSet(0,0);
		for (int i=0;i<p1;++i){
			ull v=mul_mod_ll_asm(p[i],NLOW,M); //p[i]*NLOW%M;
			insert(v);
		}
		for (int i=1,t=find(0);i<=t;++i)insert(M);
		c_gen=c2; n_gen=n-n0; p1=0;
		if (M%M_thres==0)GenNumsFromSetPrune(0,0);
		else GenNumsFromSet(0,0);
		for (int i=0;i<p1;++i)
			ans+=find(M-p[i]%M);
		return;
	}
	for (int i=0;i<=min(c[d],s);++i){
		c1[d]=i;
		DfsHighSet(d+1,s-i);
	}
}
//Search for the set of digits used. This determines the modulus M.
void DfsSets(int d,int s){
	if (d==b-1){
		c[d]=s;
		M=1;
		for (int i=1;i<b;++i)
			for (int j=1;j<=c[i];++j)M*=i;
		//++S0;
		/*if (M>1e10){
			S0+=pow(10,n)/M;
			return;
		}*/
		DfsHighSet(1,n0);
		return;
	}
	for (int i=0;i<=s;++i){
		c[d]=i;
		DfsSets(d+1,s-i);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	powb[0]=1; for (int i=1;i<=64;++i)powb[i]=powb[i-1]*b;
	for (n=1;;++n){
		int t1=clock();
		n0=(n+1)/2-1; ans=0;
		NLOW=1; for (int i=1;i<=n-n0;++i)NLOW*=b;
		DfsSets(1,n);
		//printf("S=%I64d\n",S0);
		printf("n=%d ans=%I64d\n",n,ans);
		printf("time=%d\n",clock()-t1);
	}
	return 0;
}
