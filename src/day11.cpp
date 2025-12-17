#include <vector>
#include <map>
// #include <array>
#include <iostream>
#include <string>
// #include <algorithm>
// #include <thread>
// #include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

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
    map<string, vector<string>> input;

    string s;
    while(getline(cin, s, delimiter)) {
        if (s.empty()) break;
        vector<string> tokens = split(s);
        vector<string> outputs(tokens.size() - 1);
        copy(tokens.begin() + 1, tokens.begin() + tokens.size(), outputs.begin());
        string k = tokens[0];
        k.pop_back();
        input[k] = outputs;
    }

    return input;
}

string repeat(const string& s, int n) {
    string out;
    out.reserve(s.size() * n);
    for (int i = 0; i < n; i++) out += s;
    return out;
}

long long traverse(const map<string, vector<string>>& m, const string& target, map<string, long long>& memo, string k, int depth = 0) {
    if (k == target) return 1;
    // otherwise we arrive at out and it's not the current target, return 0
    if (k == "out") return 0;
    if (memo.contains(k)) return memo.at(k);
    long long sum = 0;

    string prefix = repeat("┃ ", (depth == 0 ? 0 : depth - 1));
    // cout << prefix << (depth == 0 ? "" : "┃ ") << k << " : " << endl;
    for (string next : m.at(k)) {
        sum += traverse(m, target, memo, next, depth + 1);
    }
    // cout << endl;
    memo.insert({k, sum});
    return sum;
}

void solve1(map<string, vector<string>> m) {
    int sum = 0;

    // for (auto &p : m) {
    //     cout << p.first << " -> ";
    //     for (auto v : p.second) {
    //         cout << v << ", ";
    //     }
    //     cout << endl;
    // }
    map<string, long long> memo;
    cout << "sol 1 : " << traverse(m, "out", memo, "you") << endl;
    return;
}


void solve2(map<string, vector<string>> m) {
    map<string, long long> memo; // remember to clear memo after each one
    // confirmed that it's fft -> dac and not dac -> fft
    // long long res = traverse(m, "dac", memo, "fft");
    long long res1 = traverse(m, "fft", memo, "svr");
    memo.clear();
    long long res2 = traverse(m, "dac", memo, "fft");
    memo.clear();
    long long res3 = traverse(m, "out", memo, "dac");
    long long res = res1 * res2 * res3;
    cout << "sol 2 : " << res << endl;
    return;
}


int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    auto input = parseInput();

    solve1(input);
    solve2(input);
}
