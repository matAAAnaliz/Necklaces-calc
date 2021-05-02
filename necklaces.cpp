#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
ll C(int n,int k){ 
    ll C[k+1];
    memset(C,0,sizeof(C));
    C[0]=1;
    for (int i=1;i<=n;i++){
        for (int j=min(i,k);j>0;j--) 
            C[j]=C[j]+C[j-1];
    } 
    return C[k];
}

bool satisfies(int a,vector<int> b){
	bool ans=true;
	for(auto x:b){
		if(x%a!=0)
			ans=false;
	}
	return ans;
}
int main(){
	int number_of_colours;
	int N=0;
	vector<int> v;
	vector<pair<int,ll>> vv;
	map<int,int> m;
	printf("Enter the number of colours: ");
	scanf("%d",&number_of_colours);
	for(int i=0;i<number_of_colours;i++){
		printf("Enter the number of beads of colour %d: ",i+1);
		int a;
		scanf("%d",&a);
		N+=a;
		v.push_back(a);
	}
	int M=N;
	ll sfz=1;
	for(int i=0;i<number_of_colours-1;i++){
		sfz*=C(M,v[i]);
		M-=v[i];
	}
	vv.push_back(make_pair(1,sfz));
	for(int i=1;i<N;i++){
		int t=__gcd(i,N);
		if(t>1){
			bool flag=true;
			for(auto x:m){
				if(x.first==t){
					m[t]+=1;
					flag=false;
				}
			}
			if(flag){
				m[t]=1;
			}
		}
	}
	for(auto x:m){
		int loc=N/x.first;
		int noc=x.first;
		bool f=satisfies(loc,v);
		if(f){
			ll p=1;
			for(int i=0;i<number_of_colours-1;i++){
				int t=v[i]/loc;
				p*=C(noc,t);
				noc-=t;
			}
			vv.push_back(make_pair(x.second,p));
		}
		else if(!f){
			vv.push_back(make_pair(0,0));
		}
	}
	int noo=0;
	for(auto x:v){
		if(x%2==1)
			noo++;
	}
	if(N%2==1){
		if(noo==1){
			int k=N/2;
			for(int i=0;i<number_of_colours;i++){
				if(v[i]%2==1)
					v[i]--;
			}
			ll p=1;
			for(int i=0;i<number_of_colours-1;i++){
				int t=v[i]/2;
				p*=C(k,t);
				k-=t;
			}
			vv.push_back(make_pair(N,p));
		}
	}else if(N%2==0){
		if(noo==0){
			int k=N/2;
			ll p=1;
			for(int i=0;i<number_of_colours-1;i++){
				int t=v[i]/2;
				p*=C(k,t);
				k-=t;
			}
			vv.push_back(make_pair(N,p));
		}else if(noo==2){
			int k=N/2;
			for(int i=0;i<number_of_colours;i++){
				if(v[i]%2==1)
					v[i]--;
			}
			ll p=1;
			for(int i=0;i<number_of_colours-1;i++){
				int t=v[i]/2;
				p*=C(k,t);
				k-=t;
			}
			vv.push_back(make_pair(k,p));
		}
	}
	ll res=0;
	for(auto x:vv){
		res+=(x.first*x.second);
	}
	printf("%d\n",res/(2*N));
	return 0;
}
