#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> A[100010];
vector<int> v[100010];
int Q[100010][5]; /* y, x, steps */
int cord[2][2]; /* st, ed | y, x */
int diry[4] = {-1, 0, 1, 0}; /* U, R, D, L*/
int dirx[4] = {0, 1, 0, -1};
int i, x, y, c, ans, QS, QF;

int Reached(int cury, int curx){
	if (cury!=cord[1][0]) return 0;
	if (curx!=cord[1][1]) return 0;
	return 1;
}

int BFS(){
	for (i=0; i<2; i++) Q[0][i] = cord[0][i];
	Q[0][2] = 0;
	v[Q[0][0]][Q[0][1]] = 1;
	QF = 1;
	
	for (QS=0; QS<QF; QS++){
		int cury = Q[QS][0];
		int curx = Q[QS][1];
		
		for (i=0; i<4; i++){
			int ny = cury + diry[i];
			int nx = curx + dirx[i];
			if (ny<1) continue;
			if (nx<1) continue;
			if (ny>N) continue;
			if (nx>M) continue;
			if (v[ny][nx]) continue;
			if (A[ny][nx]<A[cury][curx]) continue;
			if (Reached(ny, nx)) return (Q[QS][2]+1);
			
			Q[QF][0] = ny;
			Q[QF][1] = nx;
			Q[QF][2] = Q[QS][2]+1;
			v[ny][nx] = 1;
			QF++;
		}
		
	}
	
	return -1;
}

int main(){
	scanf("%d%d", &N, &M);
	
	for (y=1; y<=N; y++){
		A[y].clear();
		v[y].clear();
		A[y].resize(M+1, 0);
		v[y].resize(M+1, 0);
		for (x=1; x<=M; x++){
			scanf("%d", &c);
			A[y][x] = c;
		}
	}
	
	for (i=0; i<2; i++) for (x=0; x<2; x++) scanf("%d", &cord[i][x]);
	
	printf("%d\n", BFS());
	
	
	return 0;
}

