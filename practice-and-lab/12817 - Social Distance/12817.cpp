#include <iostream>
#include <vector>
#include <set>
#include <cstddef>
#include <algorithm>

using namespace std;

struct Segment {
	int L, R;
	Segment(int l, int r) : L(l), R(r) {}
	bool operator<(const Segment& rhs) const {
		int L_dist = (R - L) / 2;
		int R_dist = (rhs.R - rhs.L) / 2;
		if (L_dist != R_dist) return L_dist > R_dist;
		return L < rhs.L;
	}
};

class Classroom {
private:
	set<Segment> segs;
	set<int> seat;
	vector<int> id_to_pos;

	int seat_count;
	int student_count;
	int safe_distance;
	int min_distance;
	
	void queryStudentEnter(int id) {
		set<Segment>::iterator target = segs.begin();
		Segment lseg(target->L, (target->L + target->R) / 2);
		Segment rseg((target->L + target->R) / 2, target->R);
		if (target->L != 0) min_distance = min(min_distance, (target->L + target->R) / 2 - target->L);
		else if (target->R != seat_count + 1) min_distance = min(min_distance, target->R - (target->L + target->R) / 2);
		id_to_pos[id] = (target->L + target->R) / 2;
		seat.insert((target->L + target->R) / 2);
		segs.erase(target);
		segs.insert(lseg);
		segs.insert(rseg);
	}

	void queryStudentExit(int id) {
		set<int>::iterator target = seat.find(id_to_pos[id]);
		set<int>::iterator left = target, right = target;
		left--;
		right++;
		seat.erase(target);
		segs.erase(Segment(*left, id_to_pos[id]));
		segs.erase(Segment(id_to_pos[id], *right));
		segs.insert(Segment(*left, *right));
		id_to_pos[id] = -1;
	}

public:
	Classroom(int N, int M, int S) : seat_count(N), student_count(M), safe_distance(S), min_distance(INT32_MAX) {
		segs.insert(Segment(0, seat_count + 1));
		id_to_pos.resize(student_count + 1, -1);
		seat.insert(0);
		seat.insert(seat_count + 1);
	}

	~Classroom() = default;

	void processQueries() {
		char queryType;
		int student_id;
		for (int i = 0; i < 2 * student_count; i++) {
			cin >> queryType >> student_id;
			if (queryType == 'i') queryStudentEnter(student_id);
			else queryStudentExit(student_id);
		}
		if (min_distance < safe_distance) cout << "NO\n";
		else cout << "YES\n";
		if (min_distance == INT32_MAX) cout << "INF\n";
		else cout << min_distance << '\n';
	}

};

int main() {
	int N, M, S;
	cin >> N >> M >> S;
	Classroom Clockwise(N, M, S);
	Clockwise.processQueries();

	return 0;
}