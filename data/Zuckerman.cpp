/*
	Algorithm for counting the base-b Zuckerman numbers with exactly n digits.
	Complexity: O((b-1)^{N/2}*N^O(b/log b)).
*/
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
typedef unsigned int uint;
typedef uint64_t ull;
typedef __int128 u128;
#define LARGE_NUM
#ifdef LARGE_NUM
	#define vtype u128
#else
	#define vtype ull
#endif
struct Hash{
	uint S1;
	const static ull MUL=12345678911234567891ull;
	const int LEN_OVERFLOW=105;
	#define H(x) ((ull)x*MUL>>S1)
	struct node{
		vtype x;
		int y;
	}*h;
	int size;
	void init(int S){
		S1=64-S;
		size=(1<<S)+LEN_OVERFLOW;
		h=new(nothrow) node[size];
		assert(h);
		memset(h,0,sizeof(node)*size);
	}
	Hash(int n=1){
		int S=1;
		while ((1<<S)<n*2)++S;
		init(S);
	}
	inline void insert(vtype x){
		node *p=h+H(x);
		for (;p->y;++p)
			if (p->x==x){++p->y; return;}
		p->x=x; p->y=1;
	}
	inline int find(vtype x){
		for (node *p=h+H(x);p->y;++p)
			if (p->x==x)return p->y;
		return 0;
	}
	void destroy(){delete[] h;}
	~Hash(){}
	#undef H
};
const int N=105;  //maximum #digits
const int B=105;  //maximum base
int b=10;   //the base we use
int n;
ull powb[N];
atomic<ull> ans;
/*template<>
struct std::hash<u128>{
    size_t operator()(const u128 &x)const {
        return x;
    }
};*/
inline ull mul_mod_ull_asm(ull a,ull b,ull p){
	ull ret;
	__asm__ __volatile__("movq %1,%%rax\n mulq %2\n divq %3\n":"=d"(ret):"m"(a),"m"(b),"m"(p):"%rax");
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
unordered_set<vtype> products[N];
void DfsProducts(int d,int s,vtype M,int n){
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
unordered_map<vtype,vector<ull>> nums[N],nums_prune[N];
int nums1=-1,nums2=-1;
void DfsNums(int d,ull M,ull x,int n){
	if (M%b==0)return;
	if (d==n){
		nums[n][M].push_back(x);
		return;
	}
	for (int i=1;i<b;++i)
		DfsNums(d+1,M*i,x*b+i,n);
}
const int d_thres=8,M_thres=1<<d_thres;
void DfsNumsPrune(int d,ull M,ull x,int n){
	if (M%b==0)return;
	if (d==n){
		nums_prune[n][M].push_back(x);
		return;
	}
	if (d==d_thres&&x%M_thres)return;
	for (int i=1;i<b;++i)
		DfsNumsPrune(d+1,M*i,x+i*powb[d],n);
}
void solve(int n,int n0,vtype M,bool prune=0){
	ull res=0;
	ull N_low=powb[n-n0];
	for (const auto &M_high:products[n0]){
		if (M%M_high)continue;
		vtype M_low=M/M_high;
		if (products[n-n0].find(M_low)==products[n-n0].end())continue;
		//meet-in-the-middle
		Hash h(nums[n0][M_high].size());
		for (const auto &u:nums[n0][M_high]){
		#ifdef LARGE_NUM
			vtype v=(vtype)u*N_low%M;
		#else
			vtype v=mul_mod_ull_asm(u,N_low,M);
		#endif
			h.insert(v);
		}
		for (int i=1,t=h.find(0);i<=t;++i)h.insert(M);
		assert(h.h[h.size-1].y==0);
		if (!prune)for (const auto &u:nums[n-n0][M_low])res+=h.find(M-u%M);
		else for (const auto &u:nums_prune[n-n0][M_low])res+=h.find(M-u%M);
		h.destroy();
	}
	ans.fetch_add(res);
}
int main(int argc, char *argv[])
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//srand(time(0));
	if (argc>=2)b=stoi(argv[1]);
	powb[0]=1; for (int i=1;i<N;++i)powb[i]=powb[i-1]*b;
	products[0].insert(1);
	for (n=1;;++n){
	#ifndef LARGE_NUM
		assert(pow(b-1.,n)<~0ull);
	#endif
		double t1=omp_get_wtime();
		//printf("n=%d b=%d\n",n,b);
		ans=0;
		for (int i=1;i<=n;++i)
			if (products[i].empty())DfsProducts(1,i,1,i);
		int prods_cnt=0;
		for (auto &v:products[n])prods_cnt+=v%b>0;
		//printf("size=%d %d\n",products[n].size(),prods_cnt);
		int n0=n/2,n0_prune=max(0,(n+1)/2-2);
		while (nums1<max(n0,n-n0))DfsNums(0,1,0,++nums1);
		if (b==10)while (nums2<n-n0_prune)DfsNumsPrune(0,1,0,++nums2);
		vector<vtype> prods(products[n].begin(),products[n].end());
		random_shuffle(prods.begin(),prods.end());
		//printf("time pre=%.3lfs\n", omp_get_wtime()-t1);
        double pre_time = omp_get_wtime()-t1;
		int T=0;
		#pragma omp parallel for schedule(dynamic, 1) //reduction(+:ans)
		for (auto &M:prods){
			if (M%b==0)continue;
			/*#pragma omp critical
			{
				printf("T=%d %d\n",T,prods_cnt);
				++T;
			}*/
			if (b==10&&M%M_thres==0)solve(n,n0_prune,M,1);
			else solve(n,n0,M);
		}
		//printf("ans=%llu\n",ans.load(memory_order_acquire));
		//printf("time=%.3lfs\n", omp_get_wtime()-t1);

        ull Z = ans.load(memory_order_acquire);
        double n_time = omp_get_wtime()-t1;

        std::cout << n << "\t" << Z << "\t" << pre_time << "\t" << n_time << std::endl;
	}
	return 0;
}
