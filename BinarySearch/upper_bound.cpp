/***************************************************************************
                            upper_bound.cpp  -
                             -------------------
    begin                : Mon 03 Apr 2017 03:20:16 CDT
    copyright            : (c) 2017 by Akarsh Simha
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
#include <vector>
#include <assert.h>
#include <functional>

// Implement upperBound to behave exactly like std::upper_bound(),
// except working with indices instead of iterators.
int upperBound( const std::vector<int> &haystack, const int needle ) {
    return haystack.size();
}

int main() {
    const int numTestCases = 4096;
    const int maxSize = 4096;
    const int numLimit = 8192;
    typedef std::pair<std::vector<int>, int> testcase_t;
    TestCaseFactory tcf( maxSize, numLimit );
    int k = 0;
    for ( ; k < numTestCases/2; ++k ) {
        testcase_t tc = tcf.testCase();
        assert( TestCaseFactory::checkResult( tc.first, tc.second, upperBound( tc.first, tc.second ), 1 ) );
    }
    for ( ; k < numTestCases; ++k ) {
        testcase_t tc = tcf.testCaseNoReps();
        assert( TestCaseFactory::checkResult( tc.first, tc.second, upperBound( tc.first, tc.second ), 1 ) );
    }
}
