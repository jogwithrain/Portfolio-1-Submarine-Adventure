#include <iostream>
#include <cassert>
#include <vector>


using namespace std;

class gameBoard {
private:
    string player;
    int money = 0;
public:
    gameBoard() {
        player = "Unknown";
        money = 0;
    }
    gameBoard(string p) {
        player = p;
        money = 0;
    }
    string getName() {
        return player;
    }
    int getMoney() {
        return money;
    }
    void addMoney(int x) {
        money = money + x;
    }

};
void camera(vector<vector<char>>& v, string input, int& r, int& c, int& pr, int& pc, int& o, vector<int>& total, vector<string>& name);
bool easy(gameBoard& x);
bool game(gameBoard& x);


int main() {
    srand(time(0));
    string name;
    cout << "To Start Enter your Name:" << endl;
    cin >> name;
    gameBoard player1(name);
    bool start = true;
    while (start) {
        string input;
        cout << "Type play to start and quit to end" << endl;
        cin >> input;
        if (input == "play" || input == "Play" || input == "PLAY") {
            game(player1);
        }
        else if (input == "quit" || input == "QUIT" || input == "Quit") {
            start = false;
        }
        else {
            cout << "Invaild response, please retry" << endl;
        }
   }
}

bool game(gameBoard& x) {
    bool easylvl = easy(x);
    if (easylvl == false) {
        cout << x.getName() << " has failed the easy level. You will be brought to the main menu to restart from the beginning." << endl;
        return false;
    }
    else {
        cout << x.getName() << " has passed easy mode! New levels will come soon. For now you will be brought to the main menu with your renevue" << endl;
        return true;
    }
}

bool easy(gameBoard& z) {
    cout << "You can move up, down, right, left, and inspect an item. You can't cross a wall or potential treasure" << endl;
    cout << "In order to pass Easy level, you need to collect 7 treasures. Good luck scientist!" << endl;
    int r = 0; //row
    int c = 2; //colum
    int pr = 0; //tracks the @ rows
    int pc = 4; //tracks the @ column
    int totalEarnings = 0;
    int track = 0;
    vector<int> total = {};
    vector<string> treasures = {};
    int oxygen = 50;
    vector<vector<char>> v = {
        {'~', '~', '~', '~','@','~','~','~','~','~'},
        {' ', ' ', '*', ' ',' ',' ',' ',' ',' ',' '},
        {' ', ' ', ' ', ' ',' ','*',' ','#',' ',' '},
        {'*', ' ', ' ', ' ',' ',' ',' ',' ',' ',' '},
        {'#', ' ', ' ', ' ','#',' ',' ',' ',' ',' '},
        {'#', ' ', ' ', '#','#',' ',' ',' ','*','#'},
        {'#', ' ', ' ', ' ',' ',' ',' ','#','#','#'},
        {' ', ' ', '#', '*',' ','#','#','#','#','#'},
        {'*', '#', '#', '*','#','#','#','#','#','#'},
        {'#', '#', '#', '#','#','#','#','#','#','#'},
    };
    for (int i = r;i < 5;i++) { //Displays the first box
        for (int j = c;j < 7;j++) {
            cout << v[i][j];
        }
        cout << endl;
    }

    bool success = false;
    while ((oxygen > 0) || (success == true)) {
        string x;
        cout << "Enter your move: " << endl;
        cin >> x;
        camera(v, x, r, c, pr, pc, oxygen, total, treasures);
        if (pr == 0) {
            if (track < treasures.size()) {
                int temp = 0;
                cout << "Treasures collected:" << endl;
                while (track < treasures.size()) {
                    cout << treasures.at(track) << ": $" << total.at(track) << endl;
                    temp = temp + total.at(track);
                    track++;
                }
                cout << "Total Earnings: $" << temp << endl;
            }
        }
        if (treasures.size() > 6) {
            success = true;
            int temp = 0;
            cout << "You've collected: " << endl;
            for (int i = 0;i < treasures.size();i++) {
                cout << treasures.at(i) << ": $" << total.at(i) << endl;
                temp = temp + total.at(i);
            }
            cout << "Total Revanue of: $" << temp << endl;
            z.addMoney(temp);
            cout << "Your money now is: $" << z.getMoney() << endl;
            return true;
        }
    }
    cout << "You failed!" << endl;
    return false;
}

void camera(vector<vector<char>>& v, string input, int& r, int& c, int& pr, int& pc, int& o, vector<int>& total, vector<string>& name) {
    if (input == "w" || input == "W" || input == "Up" || input == "up") {
        if (pr > 0 && v[pr - 1][pc] != '#' && v[pr - 1][pc] != '*') {
            v[pr][pc] = ' ';
            pr--;
            v[pr][pc] = '@';
            if (pr == 0) {
                o = 50;
            }
            else {
                o = o - (rand() % 5);
            }
            if (r == 0) { //Bound check. Reprints if reachs out-of-bounds
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
            else { //No issues and moves up
                r--;
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
        }
        else {
            for (int i = r;i < r + 5;i++) {
                for (int j = c;j < c + 5;j++) {
                    cout << v[i][j];
                }
                cout << endl;
            }
            cout << "You can't cross over there, you lose no oxygen" << endl;
            cout << o << "/50" << endl;
        }
    }
    else if (input == "s" || input == "S" || input == "Down" || input == "down") {
        if (pr < 9 && (v[pr + 1][pc] != '#' && v[pr + 1][pc] != '*')) {
            if (pr == 0) {
                v[pr][pc] = '~';
            }
            else {
                v[pr][pc] = ' ';
            }
            pr++;
            v[pr][pc] = '@';
            o = o - (rand() % 5);
            if (r == 5) { //Bound check. Reprints if reachs out-of-bounds
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
            else { //Moves down if no issue
                r++;
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
        }
        else {
            for (int i = r;i < r + 5;i++) {
                for (int j = c;j < c + 5;j++) {
                    cout << v[i][j];
                }
                cout << endl;
            }
            cout << "You can't cross over there, you lose no oxygen" << endl;
            cout << o << "/50" << endl;
        }

    }
    else if (input == "d" || input == "D" || input == "Right" || input == "right") {
        if (pc < 9 && v[pr][pc + 1] != '#' && v[pr][pc + 1] != '*') {
            if (pr == 0) {
                v[pr][pc] = '~';
            }
            else {
                v[pr][pc] = ' ';
            }
            pc++;
            v[pr][pc] = '@';
            if (pr == 0) {
                o = 50;
            }
            else {
                o = o - (rand() % 5);
            }
            if (c == 5) { //Bound check. Reprints if reachs out-of-bounds
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
            else { //No issues, moves to the right
                c++;
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
        }
        else {
            for (int i = r;i < r + 5;i++) {
                for (int j = c;j < c + 5;j++) {
                    cout << v[i][j];
                }
                cout << endl;
            }
            cout << "You can't cross over there, you lose no oxygen" << endl;
            cout << o << "/50" << endl;
        }
    }
    else if (input == "a" || input == "A" || input == "Left" || input == "left") {
        if (pc > 0 && v[pr][pc - 1] != '#' && (v[pr][pc - 1] != '*')) { 
            if (pr == 0) {
                v[pr][pc] = '~';
            }
            else {
                v[pr][pc] = ' ';
            }
            pc--;
            v[pr][pc] = '@';
            if (pr == 0) {
                o = 50;
            }
            else {
                o = o - (rand() % 5);
            }
            if (c == 0) { //Bound check. Reprints if reachs out-of-bounds
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
            else { //No issues, moves to the left
                c--;
                for (int i = r;i < r + 5;i++) {
                    for (int j = c;j < c + 5;j++) {
                        cout << v[i][j];
                    }
                    cout << endl;
                }
                cout << o << "/50" << endl;
            }
        }
        else {
            for (int i = r;i < r + 5;i++) {
                for (int j = c;j < c + 5;j++) {
                    cout << v[i][j];
                }
                cout << endl;
            }
            cout << "You can't cross over there, you lose no oxygen" << endl;
            cout << o << "/50" << endl;
        }
    }
    else if (input == "inspect" || input == "Inspect") {
        if ((pr > 0 && v[pr - 1][pc] == '*') || (pr < 9 && v[pr + 1][pc] == '*') || (pc < 9 && v[pr][pc + 1] == '*') || (pc > 0 && v[pr][pc - 1] == '*')) {
            vector<string> treasure = { "Boot","Coin","Crab","Echo Shard","Golden Shark-tooth","Pearls","Bronze Sword" };
            vector<int> value = { 3,5,1,45,80,100,25 };
            int x = rand() % 7; //goes from 0 to 6
            name.push_back(treasure.at(x));
            total.push_back(value.at(x));
            cout << "You found treasure! You specifically found: " << treasure.at(x) << " worth $" << value.at(x) << endl;
            if ((pr > 0 && v[pr - 1][pc] == '*')) {
                v[pr - 1][pc] = ' ';
            }
            if ((pr < 9 && v[pr + 1][pc] == '*')) {
                v[pr + 1][pc] = ' ';
            }
            if ((pc < 9 && v[pr][pc + 1] == '*')) {
                v[pr][pc + 1] = ' ';
            }
            if ((pc > 0 && v[pr][pc - 1] == '*')) {
                v[pr][pc - 1] = ' ';
            }
        }
    }
}

