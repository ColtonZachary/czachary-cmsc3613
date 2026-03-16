#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include "LazyBinarySearchTree.h"

using namespace std;

static string trim(const string& s) {
    int i = 0;
    while (i < (int)s.size() && isspace((unsigned char)s[i])) i++;

    int j = (int)s.size() - 1;
    while (j >= i && isspace((unsigned char)s[j])) j--;

    if (j < i) return "";
    return s.substr(i, j - i + 1);
}

static bool parseIntStrict(const string& s, int& out) {
    string t = trim(s);
    if (t == "") return false;

    int start = 0;
    if (t[0] == '+' || t[0] == '-') start = 1;
    if (start >= (int)t.size()) return false;

    for (int i = start; i < (int)t.size(); i++) {
        if (!isdigit((unsigned char)t[i])) return false;
    }

    try {
        out = stoi(t);
        return true;
    } catch (...) {
        return false;
    }
}

static bool inRange(int k) { return (k >= 1 && k <= 99); }

static void outBool(ofstream& fout, bool b) {
    fout << (b ? "true" : "false") << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input.dat output.dat\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin) { cerr << "Cannot open input file\n"; return 1; }
    if (!fout) { cerr << "Cannot open output file\n"; return 1; }

    LazyBinarySearchTree tree;
    string line;

    while (getline(fin, line)) {
        string s = trim(line);
        if (s == "") continue;

        size_t pos = s.find(':');
        string cmd = (pos == string::npos) ? s : trim(s.substr(0, pos));
        string arg = (pos == string::npos) ? "" : trim(s.substr(pos + 1));

        if (cmd == "insert" || cmd == "remove" || cmd == "contains") {
            if (pos == string::npos || arg == "") {
                fout << "Error: " << cmd << " (no key)\n";
                continue;
            }

            int key = 0;
            if (!parseIntStrict(arg, key)) {
                fout << "Error: " << cmd << " (invalid argument)\n";
                continue;
            }

            if (!inRange(key)) {
                fout << "Error: " << cmd << " (illegal argument: not in range)\n";
                continue;
            }

            if (cmd == "insert") outBool(fout, tree.insert(key));
            else if (cmd == "remove") outBool(fout, tree.remove(key));
            else outBool(fout, tree.contains(key));
        }
        else if (cmd == "print") {
            if (pos != string::npos) { fout << "Error: " << s << " (invalid command)\n"; continue; }
            fout << tree.print() << "\n";
        }
        else if (cmd == "findMin") {
            if (pos != string::npos) { fout << "Error: " << s << " (invalid command)\n"; continue; }
            fout << tree.findMin() << "\n";
        }
        else if (cmd == "findMax") {
            if (pos != string::npos) { fout << "Error: " << s << " (invalid command)\n"; continue; }
            fout << tree.findMax() << "\n";
        }
        else if (cmd == "height") {
            if (pos != string::npos) { fout << "Error: " << s << " (invalid command)\n"; continue; }
            fout << tree.height() << "\n";
        }
        else if (cmd == "size") {
            if (pos != string::npos) { fout << "Error: " << s << " (invalid command)\n"; continue; }
            fout << tree.size() << "\n";
        }
        else {
            fout << "Error: " << cmd << " (invalid command)\n";
        }
    }
    return 0;
}