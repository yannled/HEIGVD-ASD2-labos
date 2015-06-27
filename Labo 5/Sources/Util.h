/* 
 * File:   Util.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:26
 */

#ifndef UTIL_H
#define	UTIL_H

#include <vector>
#include <string>

namespace ASD2 {
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    void Tokenize(const std::string& str,
            std::vector<std::string>& tokens,
            const std::string& delimiters);
    std::string DeleteNonAlpha(const std::string& str, char blank);
}

#endif	/* UTIL_H */

