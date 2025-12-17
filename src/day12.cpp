#include <vector>
// #include <map>
#include <array>
#include <iostream>
#include <string>
// #include <algorithm>
// #include <thread>
// #include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

struct Present {
    array<array<bool, 3>, 3> shape;     // 2dshape
    int vol;                            // volume
};

struct Region {
    vector<int> q;                      // present quantities
    int total_q;                        // sum of q
    int x, y;                           // x and y of the area
};

struct Input {
    vector<Present> presents;
    vector<Region> regions;
};

vector<string> split(string s, char delimiter = ' ') {
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) tokens.push_back(token);
        s.erase(0, pos + 1);
    }
    if (!s.empty()) tokens.push_back(s);

    return tokens;
}

auto parseInput(char delimiter = '\n') {
    Input input;

    string s;
    // get presents first
    for(;;) {
        // get the index (and check if we're out of presents)
        getline(cin, s, delimiter);
        if (s.back() != ':') {
            break;
        }
        Present p { {} , 0 };
        for(int i = 0; i < 3; i++) {
            getline(cin, s, delimiter);
            // read the current line
            for (int j = 0; j < 3; j++) {
                if (s[j] == '#') {
                    p.vol++;
                    p.shape[i][j] = true;
                }
            }
        }
        input.presents.push_back(p);
        // should be getting the newline from here
        getline(cin, s, delimiter);
    }

    do {
        // get the region next
        vector<string> tokens = split(s);

        Region r { {}, 0, 0, 0};
        vector<string> dimensions = split(tokens[0], 'x');
        dimensions[1].pop_back();          // remove the : from the y
        r.x = stoi(dimensions[0]);
        r.y = stoi(dimensions[1]);

        for (int i = 1; i < tokens.size(); i++) {
            r.q.push_back(stoi(tokens[i]));
            r.total_q+=stoi(tokens[i]);
        }
        input.regions.push_back(r);
    }
    while(getline(cin, s, delimiter));

    return input;
}

void solve1(Input input) {
    int sum = 0;

    // first count all the trivial "yes" solutions
    for (Region r: input.regions) {
        // check if the dimensions allow the loosest packing ever and accept those immediately
        // get dimensions of "presents"
        int xt = r.x / 3;       // x three's
        int yt = r.y / 3;       // y three's
        if (xt * yt >= r.total_q) {
            sum++;
            continue;
        }

        // next check the cases where the sum of present volumes is greater than area volume
        int total_v = 0;
        for (int i = 0; i < input.presents.size(); i++) {
            total_v += (input.presents[i].vol * r.q[i]);
        }
        if ((r.x * r.y) < total_v) continue;
        cout << "manually check" << r.x << "x" << r.y << "!!" << endl; // but nobody came! so we can sleep :,)
    }
    cout << "sol 1 : " << sum << endl;
    return;
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    Input input = parseInput();

    solve1(input);
}
