#include<bits/stdc++.h>
using namespace std;
int b,n;
double s;
double C(int n,int m){
	if (n<m)return 0;
	double res=1;
	for (int i=1;i<=m;++i)res=res*(n-i+1)/i;
	return res;
}
void dfs(int d,int n1,int n,double num,double M,int M1){
	if (d==b){
		if (n1!=n)return;
		s+=num/M;
		return;
	}
	for (int i=0;i<=n-n1;++i){
		dfs(d+1,n1+i,n,num*C(n1+i,i),M,M1);
		M*=d;
		if (d==2&&i==0)break;
		M1=__gcd(M1*d,b);
		if (M1==b)break;
	}
}
int main()
{
	b=4;
	for (n=1;n<=60;++n){
		s=0;
		dfs(1,0,n,1,1,1);  // no digit 2
		dfs(1,0,n-1,1,1,1);  // contain one digit 2, which is the last digit
		printf("b=%d n=%d s=%.2lf\n",b,n,s);
	}
	return 0;
}
