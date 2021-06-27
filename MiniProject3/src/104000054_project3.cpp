#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x, y;
  Point() : Point(0, 0) {}
  Point(float x, float y) : x(x), y(y) {}
  bool operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Point &rhs) const { return !operator==(rhs); }
  Point operator+(const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator-(const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
};

class OthelloBoard {
public:
  enum SPOT_STATE { EMPTY = 0, BLACK = 1, WHITE = 2 };
  static const int SIZE = 8;
  const array<Point, 8> directions{
      {Point(-1, -1), Point(-1, 0), Point(-1, 1), Point(0, -1),
       /*{0, 0}, */ Point(0, 1), Point(1, -1), Point(1, 0), Point(1, 1)}};
  array<array<int, SIZE>, SIZE> board;
  vector<Point> next_valid_spots;
  array<int, 3> disc_count;
  int cur_player;
  bool done;
  int winner;

private:
  int get_next_player(int player) const { return 3 - player; }
  bool is_spot_on_board(Point p) const {
    return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
  }
  int get_disc(Point p) const { return board[p.x][p.y]; }
  void set_disc(Point p, int disc) { board[p.x][p.y] = disc; }
  bool is_disc_at(Point p, int disc) const {
    if (!is_spot_on_board(p))
      return false;
    if (get_disc(p) != disc)
      return false;
    return true;
  }
  bool is_spot_valid(Point center) const {
    if (get_disc(center) != EMPTY)
      return false;
    for (Point dir : directions) {
      // Move along the direction while testing.
      Point p = center + dir;
      if (!is_disc_at(p, get_next_player(cur_player)))
        continue;
      p = p + dir;
      while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
        if (is_disc_at(p, cur_player))
          return true;
        p = p + dir;
      }
    }
    return false;
  }
  void flip_discs(Point center) {
    for (Point dir : directions) {
      // Move along the direction while testing.
      Point p = center + dir;
      if (!is_disc_at(p, get_next_player(cur_player)))
        continue;
      vector<Point> discs({p});
      p = p + dir;
      while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
        if (is_disc_at(p, cur_player)) {
          for (Point s : discs) {
            set_disc(s, cur_player);
          }
          disc_count[cur_player] += discs.size();
          disc_count[get_next_player(cur_player)] -= discs.size();
          break;
        }
        discs.push_back(p);
        p = p + dir;
      }
    }
  }

public:
  OthelloBoard() { reset(); }
  void reset() {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        board[i][j] = EMPTY;
      }
    }
    board[3][4] = board[4][3] = BLACK;
    board[3][3] = board[4][4] = WHITE;
    cur_player = BLACK;
    disc_count[EMPTY] = 8 * 8 - 4;
    disc_count[BLACK] = 2;
    disc_count[WHITE] = 2;
    next_valid_spots = get_valid_spots();
    done = false;
    winner = -1;
  }
  vector<Point> get_valid_spots() const {
    vector<Point> valid_spots;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        Point p = Point(i, j);
        if (board[i][j] != EMPTY)
          continue;
        if (is_spot_valid(p))
          valid_spots.push_back(p);
      }
    }
    return valid_spots;
  }
  bool put_disc(Point p) {
    if (!is_spot_valid(p)) {
      winner = get_next_player(cur_player);
      done = true;
      return false;
    }
    set_disc(p, cur_player);
    disc_count[cur_player]++;
    disc_count[EMPTY]--;
    flip_discs(p);
    // Give control to the other player.
    cur_player = get_next_player(cur_player);
    next_valid_spots = get_valid_spots();
    // Check Win
    if (next_valid_spots.size() == 0) {
      cur_player = get_next_player(cur_player);
      next_valid_spots = get_valid_spots();
      if (next_valid_spots.size() == 0) {
        // Game ends
        done = true;
        int white_discs = disc_count[WHITE];
        int black_discs = disc_count[BLACK];
        if (white_discs == black_discs)
          winner = EMPTY;
        else if (black_discs > white_discs)
          winner = BLACK;
        else
          winner = WHITE;
      }
    }
    return true;
  }
  string encode_player(int state) {
    if (state == BLACK)
      return "O";
    if (state == WHITE)
      return "X";
    return "Draw";
  }
  string encode_spot(int x, int y) {
    if (is_spot_valid(Point(x, y)))
      return ".";
    if (board[x][y] == BLACK)
      return "O";
    if (board[x][y] == WHITE)
      return "X";
    return " ";
  }
};

int player;
const int SIZE = 8;
array<array<int, SIZE>, SIZE> score_board;
array<array<int, SIZE>, SIZE> board;
vector<Point> next_valid_spots;
vector<Point> valid_spots;

void initScoreBoard() {
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      score_board[i][j] = 1;

  score_board[0][0] = score_board[0][7] = score_board[7][0] = score_board[7][7] = 9999;
}

int ABP(/*node*/ OthelloBoard now, int depth, int alpha, int beta,
        bool maximizingPlayer) {

  if (depth == 0 || now.next_valid_spots.size() == 0){
    //return now.disc_count.size();
    int value = 0;

    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
        if(now.board[i][j] == player)
          value += score_board[i][j];
      }
    }

    return value;
  }

  // if maximizingPlayer
  if (maximizingPlayer) {
    // value = -999999
    int value = -999999;
    // for each child of node do
    for (auto tmp : now.next_valid_spots) {
      // value := max(value, ABP(child, depth - 1, alpha, beta, FALSE))
      // alpha := max(alpha, value)
      OthelloBoard _try = now;
      _try.put_disc(tmp);

      value = max(value, ABP(_try, depth - 1, alpha, beta, false));
      alpha = max(alpha, value);

      // if beta <= alpha
      // break (*pruning beta*)
      if (beta <= alpha)
        break;
    }
    // return value
    return value;
  } else {
    // else (*minimizing player*)
    // value := 999999
    int value = 999999;
    // for each child of node do
    for (auto tmp : now.next_valid_spots) {
      // value := min(value, ABP(child, depth - 1, alpha, beta, TRUE))
      // beta := min(beta, value)
      OthelloBoard _try = now;
      _try.put_disc(tmp);

      value = min(value, ABP(_try, depth - 1, alpha, beta, true));
      beta = min(beta, value);

      // if beta <= alpha
      // break (*pruning alpha*)
      if (beta <= alpha)
        break;
    }
    return value;
  }
}

void read_board(ifstream &fin) {
  fin >> player;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      fin >> board[i][j];
    }
  }
}

void read_valid_spots(ifstream &fin) {
  int n_valid_spots;
  fin >> n_valid_spots;
  int x, y;
  for (int i = 0; i < n_valid_spots; i++) {
    fin >> x >> y;
    valid_spots.push_back({static_cast<float>(x), static_cast<float>(y)});
  }
}

void write_valid_spot(ofstream &fout) {
  for (auto tmp : valid_spots) {
    if ((tmp.x == 0 && tmp.y == 0) || (tmp.x == 0 && tmp.y == 7) ||
        (tmp.x == 7 && tmp.y == 0) || (tmp.x == 7 && tmp.y == 7)) {
      fout << tmp.x << " " << tmp.y << endl;
      fout.flush();

      return;
    }
  }

  OthelloBoard now;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      now.board[i][j] = board[i][j];
  now.cur_player = player;
  now.next_valid_spots = valid_spots;

  int best = -1;
  
  Point ans;
  for (auto tmp : valid_spots) {
    OthelloBoard _try = now;
    _try.put_disc(tmp);
    int val = ABP(_try, 7, -99999999, 99999999, true);

    if (val > best) {
      best = val;
      ans = tmp;
    }

    fout << ans.x << " " << ans.y << endl;
    fout.flush();
  }
}

int main(int, char **argv) {
  // cout << "start random" << endl;
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);
  initScoreBoard();
  read_board(fin);
  read_valid_spots(fin);
  write_valid_spot(fout);
  fin.close();
  fout.close();
  return 0;
}
