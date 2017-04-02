/***************************************************************************
                                add.cpp  -
                             -------------------
    begin                : Mon 19 Sep 2016 01:43:33 CDT
    copyright            : (c) 2016 by Akarsh Simha
    email                : akarsh.simha@kdemail.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/* Project Includes */
#include "testcasefactory.h"

/* STL Includes */
#include <string>
#include <algorithm>
#include <assert.h>

std::string add(const std::string& a, const std::string& b) {
    std::string result;


    return result;
}

int main() {
    const int testcases = 4096;
    const int maxDigits = 4096;
    TestCaseFactory tcf( maxDigits );
    for ( int k = 0; k < testcases; ++k ) {
        std::string a = tcf.testcase();
        std::string b = tcf.testcase();
        std::string result = add( a, b );
        assert( TestCaseFactory::checkResult( a, b, result ) );
    }
}
