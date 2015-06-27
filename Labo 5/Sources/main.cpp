/* 
 * File:   main.cpp
 * Author: Valentin MINDER, Toni DE SOUSA DIAS
 *  MODIFIED BY Valentin MINDER, Toni DE SOUSA DIAS
 *  ASD2 - LAB5 - DICTIONARY
 * Created on January 8, 2015, 12:40 PM
 */

#include <cstdlib>
#include <set>
#include <unordered_set>

#include <vector>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <locale>

#include "Util.h"
#include "TernarySearchTrie.h"
#include "TernarySearchTrieAVL.h"
#include "TernarySearchTrieAVL_wildcard.h"

using namespace std;

/**
 * The dictionnary is a STL UNORDERED_SET.
 * 
 * Because "Sets are typically implemented as binary search trees."
 * which is the fasted method to test if an element belongs to the data or not.
 * 
 * We choose the unordered version because it was slightly fastest than a usual set.
 * A set uses values as key, and to keep the order and performance, 
 * it will need a lot of balancing.
 * An unordored_set doesn't need to keep the order or values, only the keys are ordered 
 * and it uses keys like hash, therefore needs less balancing, thus faster than set.
 * 
 * Indeed in the doc we can reed: "unordered_set containers are faster than set 
 * containers to access individual elements by their key"
 * 
 *  **** The whole C++ references says: *****
 * http://www.cplusplus.com/reference/unordered_set/unordered_set/
 * Unordered Set
 * 
 * Unordered sets are containers that store unique elements in no particular order, 
 * and which allow for fast retrieval of individual elements based on their value.
 * 
 * In an unordered_set, the value of an element is at the same time its key, 
 * that identifies it uniquely. Keys are immutable, therefore, the elements in 
 * an unordered_set cannot be modified once in the container - they can be 
 * inserted and removed, though.
 * 
 * Internally, the elements in the unordered_set are not sorted in any particular 
 * order, but organized into buckets depending on their hash values to allow for 
 * fast access to individual elements directly by their values (with a constant 
 * average time complexity on average).
 * 
 * unordered_set containers are faster than set containers to access individual 
 * elements by their key, although they are generally less efficient for range 
 * iteration through a subset of their elements.
 * 
 * Iterators in the container are at least forward iterators.
 */

std::unordered_set<std::string> dictionarySet;
TernarySearchTrie<char, int> myTST;
TernarySearchTrieAVL<char, int> myTSTAVL;
TernarySearchTrieAVLWildCard<char, int> myTSTAVLWILD;

int nbChar = 26 + 1; // M = 26 (a-z) + 1 (')
int datastructureType = 0;

//BinarySearchTree<const char* ,int> myTST;
//BinarySearchTree<string,int> myTST;

/**
 * Reads and store the dictionary file in the data structure.
 * @param filename
 */
void importDictionary(const std::string& filename) {
    cout << "Loading dictionary " << filename;
    switch (datastructureType) {
        case (1):
            cout << " with a STL C++ 11 unordered_set ";
            dictionarySet.reserve(637850);
            break;
        case (2):
            cout << " with a standard TST as binary search tree ";

            break;
        case (3):
            cout << " with an AVL Ternary Search Trie ";
            break;
        case (4):
            cout << " to test WILDCARD with an AVL Ternary Search Trie ";
            break;
    }
    cout << " ... " << endl;
    clock_t startTime = clock();
    std::ifstream s(filename);
    std::string lineWord;
    while (std::getline(s, lineWord, '\n')) {
        if (!lineWord.empty() && lineWord[lineWord.size() - 1] == '\r') {
            lineWord.erase(lineWord.size() - 1);
        }
        std::transform(lineWord.begin(), lineWord.end(), lineWord.begin(), ::tolower);


        switch (datastructureType) {
            case (1):
                dictionarySet.insert(lineWord);
                break;
            case (2):
                myTSTAVL.put(lineWord.c_str(), 1);
                break;
            case (3):
                myTST.put(lineWord.c_str(), 1);
                break;
            case (4):
                myTSTAVLWILD.put(lineWord.c_str(), 1);
                break;
        }
    }
    cout << "Dictionary loaded in " << double( clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
    if (datastructureType == 3) {
        cout << "AVL test: " << myTSTAVL.checkAVL() << ". Graph: " << endl;
        myTSTAVL.visit();
    }
}

/**
 * Tests if a word is contained in the dictionnary.
 * @param word
 * @return 1 if the word is in the dictionnary, 0 otherwise.
 */
int isInDictionnary(const std::string& word) {

    switch (datastructureType) {
        case (1):
            return dictionarySet.find(word) == dictionarySet.end() ? 0 : 1;
        case (2):
            return myTSTAVL.contains(word.c_str());
        case (3):
            return myTST.contains(word.c_str());
        case (4):
            return myTSTAVLWILD.contains(word.c_str());
        default: return 0;
    }
}

/**
 * Generates all valid and correct variations of word by deleting a single char at any place.
 * Ex: acqueux → aqueux (il y a un c en trop)
 * 
 * Complexity for length N: N
 * @param word
 * @return 
 */
std::vector<std::string> generatePossibilities_1_deletion(const std::string& word) {
    std::vector<std::string> possibilities;
    possibilities.reserve(word.length());
    for (int i = 0; i < word.length(); i++) {
        string alt = word.substr(0, i) + word.substr(i + 1, word.length());
        if (isInDictionnary(alt)) {
            possibilities.push_back(alt);
        }
    }
    return possibilities;
}

/**
 * Generates all valid and correct variations of word by inserting a single char at any place.
 * Ex: aqeux → aqueux (il manque la lettre u)
 * 
 * It includes leading and trailing position of the word (therefore N+1 places), 
 * and char '\'' is also tested (therefore M+1 chars).
 * 
 * Complexity for length N and M chars: (N+1) * M;
 * @param word
 * @return 
 */
std::vector<std::string> generatePossibilities_2_insertion(const std::string& word) {
    std::vector<std::string> possibilities;
    possibilities.reserve((word.length() + 1) * nbChar);
    for (int i = 0; i <= word.length(); i++) {
        for (int j = 'a'; j <= 'z'; j++) {
            string alt = word.substr(0, i) + ((char) j) + word.substr(i, word.length());
            if (isInDictionnary(alt)) {
                possibilities.push_back(alt);
            }
        }

        // char '\'' is also tested (could be commented out if needed)
        string alt = word.substr(0, i) + ((char) '\'') + word.substr(i, word.length());
        if (isInDictionnary(alt)) {
            possibilities.push_back(alt);
        }
    }
    return possibilities;
}

/**
 * Generates all valid and correct variations of word by changing a single mistyped char.
 * Ex: awueux → aqueux (il y a un w à la place du q)
 * 
 * Char '\'' is also tested, including at leading and trailing position (for simplification but these wont be correct)
 * 
 * Complexity for length N and M chars: N * M;
 * @param word
 * @return 
 */
std::vector<std::string> generatePossibilities_3_mistyped(const std::string& word) {
    std::vector<std::string> possibilities;
    possibilities.reserve(word.length() * nbChar);
    for (int i = 0; i < word.length(); i++) {
        for (int j = 'a'; j <= 'z'; j++) {
            string alt = word.substr(0, i) + ((char) j);
            if (i < word.length()) {
                alt += word.substr(i + 1, word.length());
            }
            if (isInDictionnary(alt)) {
                possibilities.push_back(alt);
            }
        }

        // char '\'' is also tested (could be commented out if needed)
        string alt = word.substr(0, i) + ((char) '\'');
        if (i < word.length()) {
            alt += word.substr(i + 1, word.length());
        }
        if (isInDictionnary(alt)) {
            possibilities.push_back(alt);
        }
    }
    return possibilities;
}

/**
 * Generates all valid and correct variations of word inverting two consecutive chars.
 * Ex: auqeux → aqueux (u et q intervertis)
 * 
 * Complexity for length N : N-1;
 * @param word
 * @return 
 */
std::vector<std::string> generatePossibilities_4_inversion(const std::string& word) {
    std::vector<std::string> possibilities;
    possibilities.reserve(word.length() - 1);
    if (word.length() < 2) {
        return possibilities;
    }
    for (int i = 0; i < word.length() - 1; i++) {
        string alt = word.substr(0, i) + word.at(i + 1) + word.at(i);
        if (i < word.length() - 2) {
            alt += word.substr(i + 2, word.length());
        }
        if (isInDictionnary(alt)) {
            possibilities.push_back(alt);
        }
    }
    return possibilities;
}

/**
 * Split lines, keep only alpha char, split words, check word, 
 * generates correction in an output file.
 * @param filename file to correct
 */
void testCorrectFile(const std::string& filename) {
    int errorCount = 0;
    std::ifstream in(filename);

    // one output file (out_in.txt) for each input file (in.txt), 
    // but if your prefer single output (overwritten): 
    // std::ofstream out("out.txt");
    std::string name = "out_";
    std::ofstream out(name.append(filename));
    std::string line;

    cout << "Correcting file " << filename << " ... " << endl;
    clock_t startTime = clock();

    // getline operates on "\n" by default
    while (std::getline(in, line)) {
        // if line ends with a "\r" as well, we remove it
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        // first, to lower case
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        // then, delete ALL non-alpha and replaced by blank 
        line = ASD2::DeleteNonAlpha(line, ' ');

        // finally, split by the blank spaces
        std::vector<std::string> words;
        ASD2::Tokenize(line, words, " ");

        // C++ 11 : range-based for loop is a C++11 extension [-Wc++11-extensions]
        // you can safely ignore the warning.
        for (std::string word : words) {
            //if it finds a word that is not in dictionnary...
            if (word.length() > 0 && !isInDictionnary(word)) {
                // ... it marks the word as uncorrect in output...
                errorCount++;
                out << "*" << word << endl;

                // ... and it generates all valid possibilities of correction

                /** all complexities (in term of number of possibilities generated that will be tested.
                 * for N = length of original word
                 * for M = number of chars (= 26 a-z), M = 27 because ' is taken into account
                 * 1: N
                 * 2: (N+1) * M
                 * 3: N * M
                 * 4: N - 1
                 * Total: (2N + 1) * M + (2N - 1)
                 * With M = 27, total: 56N + 26
                 * With M = 26, total: 54N + 25
                 * which is LINEAR complexity in term of length of the word.
                 * 
                 * Examples (M = 27):
                 * with N =  6: total = 362
                 * with N =  8: total = 474
                 * with N = 10: total = 586
                 * */

                // type 1: one letter too much
                std::vector<std::string> possibilities = generatePossibilities_1_deletion(word);
                for (std::string a : possibilities) {
                    out << "1:" << a << endl;
                }

                // type 2: one letter missing
                possibilities = generatePossibilities_2_insertion(word);
                for (std::string a : possibilities) {
                    out << "2:" << a << endl;
                }

                // type 3: one letter mistyped
                possibilities = generatePossibilities_3_mistyped(word);
                for (std::string a : possibilities) {
                    out << "3:" << a << endl;
                }

                // type 4: inversion of two consecutive letters
                possibilities = generatePossibilities_4_inversion(word);
                for (std::string a : possibilities) {
                    out << "4:" << a << endl;
                }

            }
        }
    }

    // final time and # of errors in file.
    if (errorCount == 0) {
        cout << "No errors found in " << filename << endl;
    } else {
        cout << errorCount << " error(s) found in " << filename << endl;
    }
    cout << "File corrected in " << double( clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
}

void testWildCard(const std::string& pattern) {
    cout << "Searching dictionary with pattern \"" << pattern << "\" ... " << endl;
    clock_t startTime = clock();
    //const std::string& pattern = "afterw...";
    std::list<std::string> list = myTSTAVLWILD.wildCardMatch(pattern);
    cout << "Found " << list.size() << " results in " << double( clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << endl;
    for (std::string a : list) {
        cout << a << endl;
    }

}

void test() {
    switch (datastructureType) {
        case(4):
        {
            const std::string& pattern = "afterw...";
            testWildCard(pattern);
            const std::string& pattern2 = "..............................";
            testWildCard(pattern2);
            const std::string& pattern3 = "..tmost";
            testWildCard(pattern3);
            break;
        }
        default:
        {
            testCorrectFile("input_lates.txt");
            testCorrectFile("input_simple.txt");
            testCorrectFile("input_sh.txt");
            testCorrectFile("input_wikipedia.txt");
        }
    }
}

int main(int argc, char** argv) {

    // unordered dictionnary (less time because insertion is not always at the end)
    int order_dictionary = false; // false: unordered, true: ordered.
    string filename = order_dictionary ? "ordered_dictionary.txt" : "dictionary.txt";
    /**
     * 0: test all...
     * 1: STL unordered_set
     * 2: TernarySearchTrie (without AVL, simple BST)
     * 3: TernarySearchTrie with AVL
     * 4: TernarySearchTrie with AVL, no file corrected, but wilcard test.
     */
    datastructureType = 0;
    switch (datastructureType) {
        case (0):
            while (datastructureType < 4) {
                datastructureType++;
                importDictionary(filename);
                test();
            }
            break;
        default:
            importDictionary(filename);
            test();
    }
    return 0;
}