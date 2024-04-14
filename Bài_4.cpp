#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

#include <vector>
#include <string>

using namespace std;

// Helper function to split words separated by semicolons
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    size_t start = 0, end = str.find(delimiter);
    while (end != string::npos) {
        token = str.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = str.find(delimiter, start);
    }
    token = str.substr(start);
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

// Helper function to check if a word can be placed at a given position
bool canPlace(const vector<string>& crossword, const string& word, int row, int col, char axis) {
    int len = word.size();
    if (axis == 'H') {
        if (col + len > 10) return false;
        for (int i = 0; i < len; i++) {
            if (crossword[row][col + i] != '-' && crossword[row][col + i] != word[i])
                return false;
        }
    } else { // axis == 'V'
        if (row + len > 10) return false;
        for (int i = 0; i < len; i++) {
            if (crossword[row + i][col] != '-' && crossword[row + i][col] != word[i])
                return false;
        }
    }
    return true;
}

// Helper function to place or remove a word on the crossword
void placeWord(vector<string>& crossword, const string& word, int row, int col, char axis, bool place) {
    for (int i = 0; i < word.size(); i++) {
        if (axis == 'H') {
            if (place) crossword[row][col + i] = word[i];
            else crossword[row][col + i] = '-';
        } else { // axis == 'V'
            if (place) crossword[row + i][col] = word[i];
            else crossword[row + i][col] = '-';
        }
    }
}

// Recursive function to solve the crossword
bool solve(vector<string>& crossword, const vector<string>& words, int index) {
    if (index == words.size()) return true;  // All words are placed

    string word = words[index];
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if (canPlace(crossword, word, row, col, 'H')) {
                placeWord(crossword, word, row, col, 'H', true);
                if (solve(crossword, words, index + 1)) return true;
                placeWord(crossword, word, row, col, 'H', false);
            }
            if (canPlace(crossword, word, row, col, 'V')) {
                placeWord(crossword, word, row, col, 'V', true);
                if (solve(crossword, words, index + 1)) return true;
                placeWord(crossword, word, row, col, 'V', false);
            }
        }
    }
    return false; // Backtrack
}

// The main function that is expected to be completed
vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    vector<string> wordList = split(words, ';');
    solve(crossword, wordList, 0);
    return crossword;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
