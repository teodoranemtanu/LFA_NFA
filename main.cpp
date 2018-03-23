#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
ifstream fin("..\\NFA.in");
ofstream fout("..\\NFA.out");


map<pair<int, char>, vector<int> > M; // the NFA
//pt perechea (q, c): q -> current state
// c -> the character which i can move forward from the state q
// m[(q1,c)] = (q2, q3, q4 ....)  -> from the state q1 I can move with the character c to the states q2, q3 ...
map<int, bool> finalStates;
// finalStates[q] = true; -> x is a final state
int initalState;
int nrStates, nrFinalStates, nrTransitions;
int nrWords;
vector<string> words; // the words which will be tested


/**
 * the function reads the data from file and builds the map and the vector of words,
 * which are going to be tested
 */
void readData() {
    fin >> nrStates >> nrTransitions >> initalState >> nrFinalStates;
    for (int i = 0; i < nrFinalStates; i++) {
        int x;
        fin >> x;
        finalStates[x] = true;
    }
    for (int i = 0; i < nrTransitions; i++) {
        int q1, q2;
        char c;
        pair<int, char> p;
        fin >> q1 >> c >> q2;
        p.first = q1;
        p.second = c;
        M[p].push_back(q2);
    }
    fin >> nrWords;
    for (int i = 0; i < nrWords; i++) {
        string word;
        fin >> word;
        words.push_back(word);
    }
}

/**
 * tests if a word is going to be accepted by the NFA
 * @param word  represent a string, the tested word
 * @return - true if the word is accepted, false otherwhise
 */

bool isAccepted(string word) {
    if (word.size() == 0 && !finalStates[initalState]) { // test for the void word
        return false;
    }

    pair<int, char> p;
    vector<int> currentStates;
    vector<int> nextStates;

    currentStates.push_back(initalState); // initially only the initialState can be counted as current state

    for (int i = 0; i < word.size(); i++) {
        p.second = word[i];
        for (int j = 0; j < currentStates.size(); j++) {
            // for a current letter, I move takimg into account the current states and I try to find the next ones
            p.first = currentStates[j];
            nextStates.insert(nextStates.end(), M[p].begin(),
                              M[p].end()); //the next states are saved into a list corresponding to the current pair p
            //which I concatenate to the vector of next states
            if (nextStates.empty()) return false;
            // if for a certain letter I don't have any next states, then I don't accept the word
        }
        currentStates = nextStates;
        nextStates.clear();
    }

    for (int i = 0; i < currentStates.size(); i++)
        if (finalStates[currentStates[i]]) { //I accept the word only if one of the states found as valid is also final
            currentStates.clear();
            return true;
        }
    currentStates.clear();
    return false;
}

int main() {
    readData();
    for (int i = 0; i < nrWords; i++) {
        if (isAccepted(words[i])) {
            fout << "acceptat\n";
        } else {
            fout << "neacceptat\n";
        }
    }

    return 0;
}
