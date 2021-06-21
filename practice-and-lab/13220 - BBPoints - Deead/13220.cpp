#include <bits/stdc++.h>
using namespace std;

int N, Q;
long long int A[100010];
map<int, set<int>> M;
map<int, set<int>>::iterator itM;
set<int>::iterator itS;
int QT;
int i, x, y, p, c;

void CheckState(){
	set<int>::iterator itS;
	for (i=0; i<20; i++) if (M[i].begin()!=M[i].end()){
		printf("Height %3d:", i);
		for (itS=M[i].begin(); itS!=M[i].end(); itS++) printf(" %2d", *itS);
		puts("");
	}
}

int main(){
	scanf("%d%d", &N, &Q);
	for (i=1; i<=N; i++) A[i] = 0;
	M.clear();
	for (i=1; i<=N; i++) M[0].insert(i);
	//CheckState();
	
	while(Q--){
		scanf("%d", &QT);
		if (QT==1){
			scanf("%d%d", &x, &c);
			y = A[x];
			if (A[x]==-1) continue;
			if (y<=1000000000){
				itS = M[y].find(x);
				M[y].erase(itS);
				M[y+c].insert(x);
			}
			A[x] = y+c;
		}
		if (QT==2){
			scanf("%d%d%d", &x, &y, &c);
			if (x>N) continue;
			itS = M[y].lower_bound(x);
			if (itS==M[y].end()) continue;
			int nx = *itS;
			if (nx>(x+c)) continue;
			M[y].erase(itS);
			A[nx] = -1;
		}
	}
	
	printf("%lld", A[1]);
	for (i=2; i<=N; i++) printf(" %lld", A[i]);
	puts("");
	
	return 0;
}
/*
10 7 1 1 5 1 2 3 1 2 4 1 9 3 2 2 7 2 2 8 3 2 1 5 5
*/
