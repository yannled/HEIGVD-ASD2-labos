/* 
 * File:   Util.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:26
 */

#ifndef UTIL_CORR_H
#define	UTIL_CORR_H

#include <vector>
#include <string>

namespace ASD2 {
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
}

#endif	/* UTIL_CORR_H */

