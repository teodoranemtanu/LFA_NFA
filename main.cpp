#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
ifstream fin("..\\NFA.in");
ofstream fout("..\\NFA.out");


map<pair<int, char>, vector<int> > M; // automatul
//pt perechea (q, c): q -> stare curenta; c -> caracterul cu care pot pleca din acea stare;
// m[(q1,c)] = (q2, q3, q4 ....)  -> din starea q1 pot pleca cu caracterul c in starile q2, q3, ....
map<int, bool> finalStates;
// finalStates[q] = true; -> x e o stare finala
int initalState;
int nrStates, nrFinalStates, nrTransitions;
int nrWords;
vector<string> words; // cuvintele pe care le testez


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

bool isAccepted(string word) {
    if (word.size() == 0 && !finalStates[initalState]) { // testul pentru cuvantul vid
        return false;
    }

    pair<int, char> p;
    vector<int> currentStates;
    vector<int> nextStates;

    currentStates.push_back(initalState); // initial pot incepe doar din starea initiala

    for (int i = 0; i < word.size(); i++) {
        p.second = word[i];
        for (int j = 0; j < currentStates.size(); j++) {
            // pentru o litera curenta, ma deplasez in functie de starile curente incerc sa le gasesc pe cele viitoare
            p.first = currentStates[j];
            nextStates.insert(nextStates.end(), M[p].begin(), M[p].end()); //starile viitoare sunt salvate in lista de adiacenta corespunzatoare perechii p curente,
            // pe care o concatenez la vectorul de stari urmatoare
            if (nextStates.empty()) return false;
            //daca pentru o anumita litera nu am stari din care sa ma deplasez mai departe, atunci nu accept cuvantul
        }
        currentStates = nextStates;
        nextStates.clear();
    }

    for (int i = 0; i < currentStates.size(); i++)
        if (finalStates[currentStates[i]]) { // accept cuvantul doar daca vreo stare din cele gasite ca fiind valide e si finala
            currentStates.clear();
            return true;
        }
    currentStates.clear();
    return false;
}

int main() {
    readData()
    for (int i = 0; i < nrWords; i++) {
        if (isAccepted(words[i])) {
            fout << "acceptat\n";
        } else {
            fout << "neacceptat\n";
        }
    }

    return 0;
}
