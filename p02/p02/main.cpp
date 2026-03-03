#include <fstream>
#include "utility.h"
#include "List.h"

using namespace std;

// Student added come starts here

void backtrack(int r, string &current, bool used[], List<string> &list)
{
    if ((int)current.size() == r) { // found a valid permutation
        list.insert(list.size(), current); // insert at the end of the list
        return;
    }

    for (int i = 0; i < 26; i++) { // try each letter
        if (used[i]) continue; // skip if already used

        char next = 'a' + i; // get the next letter
 
        int n = current.size(); // check the last two letters to avoid consecutive sequences
        if (n >= 2) { // if the last two letters are consecutive and the next letter is also consecutive, skip
            char a = current[n - 2]; // second last letter
            char b = current[n - 1]; // last letter

            if (a + 1 == b && b + 1 == next) { // found a sequence of three consecutive letters, skip
                continue;
            }
        }

        // choose
        used[i] = true; // mark the letter as used
        current.push_back(next); // add the letter to the current permutation

        // recurse
        backtrack(r, current, used, list); // explore further

        // undo
        current.pop_back(); // remove the letter from the current permutation
        used[i] = false; // unmark the letter as used
    }
}


List<string> permuteAlphabet(int r) { // generate all permutations of r letters from the alphabet without consecutive sequences
    List<string> list; // list to store the permutations

    if (r <= 0 || r > 8) return list; // return an empty list if r is out of bounds

    bool used[26] = {false}; // track which letters have been used
    string current; // current permutation being built

    backtrack(r, current, used, list); // start the backtracking process

    return list;
}

// Student added code ends here

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            throw CommandLineException();
        
        }
        if (!isNumber(argv[1])) {
            throw CommandLineException();
        }

        int r = string_to_int(argv[1]);
        ofstream output;
        output.open(argv[2]);

        if (output.fail()) {
            throw FileException(argv[2]);
        }

        List<string> list = permuteAlphabet(r);

        output << "The number of permutations is " << list.size() << endl;
        for (int i = 0; i < list.size(); i++) {
            string perm(r, 'a');
            list.retrieve(i, perm);
            output << perm << endl; 
        }

        output.close();

    } catch(...) {
        exit(EXIT_FAILURE);
    }

    return 0;
}