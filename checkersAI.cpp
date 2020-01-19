#include <bits/stdc++.h>
using namespace std;

const int inf = 1e7;
const int row = 8;
const int col = 8;

char board[row][col];
char temp[row][col];

void design_board(char board[8][8]) {
    cout << "\n    0   1   2   3   4   5   6   7 " << "\n";
    for (int i = 0; i < 8; i++) {
        cout << "  +---+---+---+---+---+---+---+---+" << "\n";
        cout << (i) << " | " << board[i][0] << " | " << board[i][1] << " | "
             << board[i][2] << " | " << board[i][3] << " | " << board[i][4] << " | "
             << board[i][5] << " | " << board[i][6] << " | " << board[i][7] << " |"
             << "\n";
    }
    cout << "  +---+---+---+---+---+---+---+---+" << "\n\n";
}

void console_clear() {
    system("CLS");
}

// assign the initial board, a = ai player, h = human player.
void assign_board() {
    for (int i = 0; i < 8; i++) {
        for( int j = 0; j < 8; j++) {
            if (i <= 2) if (i%2 != j%2) board[i][j] = 'a';
            if (i >= 5) if (i%2 != j%2) board[i][j] = 'h';
        }
    }
}

// struct to store the move infor, position, direction, # of kill.
struct data {
    int x, y, dir, kill;
    data() {}
    data(int x, int y, int dir, int kill): x(x), y(y), dir(dir), kill(kill) {}
    bool operator <(const data &other) const {
        return kill > other.kill;
    }
};

int get_random(int l, int r) {
    return rand()%(r - l + 1);
}

bool king(int r, int c) {
    return isupper(board[r][c]);
}

bool in(int r, int c) {
    return r >= 0 && r < row && c >= 0 && c < col;
}

bool emp(int r, int c) {
    return board[r][c] != 'a' && board[r][c] != 'A' && board[r][c] != 'h' && board[r][c] != 'H';
}

bool valid(int r, int c) {
    return in(r, c) && emp(r, c);
}

/// 1 - rightup, 2 - leftup, 3 - rightdown, 4 - leftdown
vector <data> possible_moves_human(int r, int c) {
    vector <data> ret;
    if (in(r - 1, c + 1) && (board[r-1][c+1] == 'a' || board[r-1][c+1] == 'A')) {
        int cr = r - 1, cc = c + 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'a' || board[cr][cc] == 'A')) cr--, cc++, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 1, kill));
    }
    if (in(r - 1, c - 1) && (board[r-1][c-1] == 'a' || board[r-1][c-1] == 'A')) {
        int cr = r - 1, cc = c - 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'a' || board[cr][cc] == 'A')) cr--, cc--, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 2, kill));
    }
    if (king(r, c) && in(r + 1, c + 1) && (board[r+1][c+1] == 'a' || board[r+1][c+1] == 'A')) {
        int cr = r + 1, cc = c + 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'a' || board[cr][cc] == 'A')) cr++, cc++, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 3, kill));
    }
    if (king(r, c) && in(r + 1, c - 1) && (board[r+1][c-1] == 'a' || board[r+1][c-1] == 'A')) {
        int cr = r + 1, cc = c - 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'a' || board[cr][cc] == 'A')) cr++, cc--, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 4, kill));
    }
    if (valid(r - 1, c + 1)) ret.push_back(data(r - 1, c + 1, 1, 0));
    if (valid(r - 1, c - 1)) ret.push_back(data(r - 1, c - 1, 2, 0));
    if (valid(r + 1, c + 1) && king(r, c)) ret.push_back(data(r + 1, c + 1, 3, 0));
    if (valid(r + 1, c - 1) && king(r, c)) ret.push_back(data(r + 1, c - 1, 4, 0));
    return ret;
}

/// 1 - rightup, 2 - leftup, 3 - rightdown, 4 - leftdown
vector <data> possible_moves_AI(int r, int c) {
    vector <data> ret;
    if (in(r + 1, c + 1) && (board[r+1][c+1] == 'h' || board[r+1][c+1] == 'H')) {
        int cr = r + 1, cc = c + 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'h' || board[cr][cc] == 'H')) cr++, cc++, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 3, kill));
    }
    if (in(r + 1, c - 1) && (board[r+1][c-1] == 'h' || board[r+1][c-1] == 'H')) {
        int cr = r + 1, cc = c - 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'h' || board[cr][cc] == 'H')) cr++, cc--, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 4, kill));
    }

    if (king(r, c) && in(r - 1, c + 1) && (board[r-1][c+1] == 'h' || board[r-1][c+1] == 'H')) {
        int cr = r - 1, cc = c + 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'h' || board[cr][cc] == 'H')) cr--, cc++, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 1, kill));
    }
    if (king(r, c) && in(r - 1, c - 1) && (board[r-1][c-1] == 'h' || board[r-1][c-1] == 'H')) {
        int cr = r + 1, cc = c - 1, kill = 0;
        while (in(cr, cc) && (board[cr][cc] == 'h' || board[cr][cc] == 'H')) cr--, cc--, kill++;
        if (in(cr, cc) && board[cr][cc] == ' ') ret.push_back(data(cr, cc, 2, kill));
    }
    if (valid(r + 1, c + 1)) ret.push_back(data(r + 1, c + 1, 3, 0));
    if (valid(r + 1, c - 1)) ret.push_back(data(r + 1, c - 1, 4, 0));
    if (valid(r - 1, c + 1) && king(r, c)) ret.push_back(data(r - 1, c + 1, 1, 0));
    if (valid(r - 1, c - 1) && king(r, c)) ret.push_back(data(r - 1, c - 1, 2, 0));
    return ret;
}

// execute the move from cx, cy to nx, ny with direction dir.
void execute_move(int cx, int cy, int nx, int ny, int dir) {
    if (dir == 1) {
        char cur = board[cx][cy];
        while (!(cx == nx && cy == ny)) board[cx][cy] = ' ', cx--, cy++;
        board[nx][ny] = cur;
    }
    if (dir == 2) {
        char cur = board[cx][cy];
        while (!(cx == nx && cy == ny)) board[cx][cy] = ' ', cx--, cy--;
        board[nx][ny] = cur;
    }
    if (dir == 3) {
        char cur = board[cx][cy];
        while (!(cx == nx && cy == ny)) board[cx][cy] = ' ', cx++, cy++;
        board[nx][ny] = cur;
    }
    if (dir == 4) {
        char cur = board[cx][cy];
        while (!(cx == nx && cy == ny)) board[cx][cy] = ' ', cx++, cy--;
        board[nx][ny] = cur;
    }
}

// any human move possible?
bool move_left_human() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'h' || board[i][j] == 'H') {
                vector <data> cur = possible_moves_human(i, j);
                if (cur.size() != 0) return true;
            }
        }
    }
    return false;
}

// any ai move possible?
bool move_left_AI() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'a' || board[i][j] == 'A') {
                vector <data> cur = possible_moves_AI(i, j);
                if (cur.size() != 0) return true;
            }
        }
    }
    return false;
}

// evalution function for the current state of board
int evaluate() {
    int ai = 0, human = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'a') ai += 100;
            if (board[i][j] == 'A') ai += 500;
            if (board[i][j] == 'h') human += 100;
            if (board[i][j] == 'H') human += 500;
            if (board[i][j] == 'a' || board[i][j] == 'A') {
                vector <data> v = possible_moves_AI(i, j);
                ai += 100 * (int)v.size();
                for (int i = 0; i < v.size(); i++) ai += 50000 * v[i].kill;
            }
            if (board[i][j] == 'h' || board[i][j] == 'H') {
                vector <data> v = possible_moves_human(i, j);
                human += 100 * (int)v.size();
                for (int i = 0; i < v.size(); i++) human += 50000 * v[i].kill;
            }
        }
    }
    return (ai - human);
}

// alpha beta pruning
int alpha_beta(int depth, int alpha, int beta, bool max_player) {
    if (max_player && !move_left_human()) return inf;
    if (max_player && !move_left_AI()) return -inf;
    if (!max_player && !move_left_AI()) return -inf;
    if (!max_player && !move_left_human()) return inf;
    if (depth == 0) return evaluate();
    if (max_player) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if ((board[i][j] == 'a' || board[i][j] == 'A') && possible_moves_AI(i, j).size() > 0) {
                    vector <data> v = possible_moves_AI(i, j);
                    assert((int)v.size() > 0);
                    sort(v.begin(), v.end());
                    execute_move(i, j, v[0].x, v[0].y, v[0].dir);
                    int cur = -inf;
                    cur = max(cur, alpha_beta(depth - 1, cur, beta, false));
                    alpha = max(alpha, cur);
                    if (alpha >= beta) return cur;
                }
            }
        }
    }
    else {
        vector < pair <int, int> > pos;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (board[i][j] == 'h' || board[i][j] == 'H') {
                    if (possible_moves_human(i, j).size() > 0 ) pos.push_back(make_pair(i, j));
                }
            }
        }
        int idx = get_random(0, (int)pos.size() - 1);
        vector <data> v = possible_moves_human(pos[idx].first, pos[idx].second);
        int to = get_random(0, v.size() - 1);
        execute_move(pos[idx].first, pos[idx].second, v[to].x, v[to].y, v[to].dir);
        int cur = inf;
        cur = min(cur, alpha_beta(depth - 1, alpha, cur, true));
        beta = min(beta, cur);
        if (alpha >= beta) return cur;
    }
    return evaluate();
}

// check the current state of the board.
void check_game_state() {
    int ai = 0, human = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'a' || board[i][j] == 'A') {
                ai++;
            }
            if (board[i][j] == 'h' || board[i][j] == 'H') {
                human++;
            }
        }
    }
    cout << "ai pieces left : " << ai << "\n";
    cout << "human pieces left : " << human << "\n";
    cout << "\n";
}

// make new king if any piece have reached good position
void update_king() {
    for (int i = 0; i < col; i++) if (board[0][i] == 'h') board[0][i] = 'H';
    for (int i = 0; i < col; i++) if (board[row - 1][i] == 'a') board[row - 1][i] = 'A';
}

// this is the random ai that plays random moves.
void go_random_AI() {
    if (!move_left_AI()) {
        cout << "AI have no move left" << "\n";
        cout << "Human Wins!" << "\n";
        exit(0);
    }
    vector < pair <int, int> > pos;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'a' || board[i][j] == 'A') {
                if (possible_moves_AI(i, j).size() > 0 ) pos.push_back(make_pair(i, j));
            }
        }
    }
    int idx = get_random(0, (int)pos.size() - 1);
    vector <data> v = possible_moves_AI(pos[idx].first, pos[idx].second);
    int to = get_random(0, v.size() - 1);
    execute_move(pos[idx].first, pos[idx].second, v[to].x, v[to].y, v[to].dir);
    update_king();
}

void make_copy() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            board[i][j] = temp[i][j];
        }
    }
}

// ai player
void go_AI() {
    if (!move_left_AI()) {
        cout << "******* AI have no move left *******" << "\n";
        cout << "******* Human Wins! ********" << "\n";
        exit(0);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            temp[i][j] = board[i][j];
        }
    }
    int mx = -1, my = -1, best = -inf;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            make_copy();
            if ((board[i][j] == 'a' || board[i][j] == 'A') && (int)possible_moves_AI(i, j).size() > 0) {
                int cur_best = alpha_beta(5, -inf, +inf, true);
                if (cur_best > best) best = cur_best, mx = i, my = j;
            }
        }
    }
    make_copy();
    assert(mx != -1 && my != -1);
    vector <data> v = possible_moves_AI(mx, my);
    sort(v.begin(), v.end());
    execute_move(mx, my, v[0].x, v[0].y, v[0].dir);
}

// human player
void go_human() {
    if (!move_left_human()) {
        cout << "*********** Human have no move left *********" << "\n";
        cout << "********** AI Wins! ***********" << "\n";
        exit(0);
    }
    cout << "Your turn!" << "\n";
    cout << "Enter a valid coordiante to move your piece: ";
    int r, c;
    while (cin >> r >> c) {
        if (in(r, c) && (board[r][c] == 'h' || board[r][c] == 'H') && possible_moves_human(r, c).size() > 0) break;
        cout << "Invalid Move!" << "\n";
        cout << "Enter a valid coordiante to move your piece: ";
    }
    vector <data> v = possible_moves_human(r, c);
    sort(v.begin(), v.end());
    cout << "Select the # of the option to move:" << "\n";
    for (int i = 0; i < v.size(); i++) {
        cout << "option # " << i + 1 << ": ";
        cout << "move to : ( " << v[i].x << ", " << v[i].y << " ) with kill = " << v[i].kill << "\n";
    }
    int to;
    while (cin >> to) {
        if (to >= 1 && to <= (int)v.size()) break;
        cout << "Invalid Option, Enter you option again!" << "\n";
    }
    execute_move(r, c, v[to - 1].x, v[to - 1].y, v[to - 1].dir);
    update_king();
}

int main() {
    ios_base::sync_with_stdio(false);
    srand(time(NULL));
    assign_board();
    design_board(board);
    for (int step = 1; step <= 20; step++) {
        if (step%2 == 1) {
            go_human();
        }
        else {
            //go_random_AI();
            go_AI();
        }
        design_board(board);
        check_game_state();
    }
    if (evaluate() > 0) cout << "******************* AI Wins!****************" << "\n";
    else if (evaluate() < 0) cout << "Human Wins!" << "\n";
    else cout << "******************** Game Drawn! *******************" << "\n";
    return 0;
}







