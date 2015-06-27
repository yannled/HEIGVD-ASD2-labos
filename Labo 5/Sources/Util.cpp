
#include "Util.h"
#include <sstream>
#include <iostream>
#include <set>

namespace ASD2 {

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    /**
     * Repris de http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
     * @param str
     * @param tokens
     * @param delimiters
     */
    void Tokenize(const std::string& str,
            std::vector<std::string>& tokens,
            const std::string& delimiters = " ") {
        // Skip delimiters at beginning.
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        // Find first "non-delimiter".
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos) {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
    }

    int isAlphaLower(char c) {
        // here we only keep a-z chars, as requested! 
        // a better implementation would be to use isalpha 
        // which supports local-depending chars, like accentuated letter éàö ...
        // Here a word like "Böhm" in file "wikpedia" will be split in "b hm" !
        // return isalpha(c);
        if (c >= 'a' && c <= 'z') {
            return 1;
        } else {
            return 0;
        }
    }

    std::string DeleteNonAlpha(const std::string& str, char blank = ' ') {
        std::string alphaOnly;
        alphaOnly.reserve(str.size());
        for (int i = 0; i < str.size(); i++) {
            char c = str.at(i);
            if (isAlphaLower(c)) {
                alphaOnly.append(1, c);
            } else if (c == '\'' && i != 0 && i != str.size() - 1 && isAlphaLower(str.at(i - 1)) && isAlphaLower(str.at(i + 1))) {
                // previous and next char are alpha chars, 
                // then it's the middle of a word and apostrophe is autorised
                alphaOnly.append(1, c);
                // uncomment these if you want french diacyphs (accentuated letters) 
                // being replaced by 
                // be aware to change the isalpha method to system one isalpha(c)
                // in the condition of the apostroph (and not in the isAlphaLower 
                // because you wont reach following statements replacing diacryph)
                // otherwise apostrophe and diacryph contiguous wont allow apostrophe
                // (diacryph will be understood as end of word)

//            } else if (c == 'ç') {
//                alphaOnly.append(1, 'c');
//            } else if (c == 'ä' || c == 'à' || c == 'â') {
//                alphaOnly.append(1, 'a');
//            } else if (c == 'ë' || c == 'è' || c == 'ê' || c == 'é') {
//                alphaOnly.append(1, 'e');
//            } else if (c == 'ï' || c == 'ì' || c == 'î') {
//                alphaOnly.append(1, 'i');
//            } else if (c == 'ö' || c == 'ò' || c == 'ô') {
//                alphaOnly.append(1, 'o');
//            } else if (c == 'ü' || c == 'ù' || c == 'û') {
//                alphaOnly.append(1, 'u');
            } else {
                alphaOnly.append(1, blank);
            }
        }
        return alphaOnly;
    }



}