/***************************************************************************
                           binary_search.cpp  -
                             -------------------
    begin                : Mon 03 Apr 2017 01:13:49 CDT
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

// Implement binary search to return -1 if the element is not found,
// and the index of at least one repetition of the element if found.
int binarySearch( const std::vector<int> &haystack, const int needle ) {
    return -1;
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
        assert( TestCaseFactory::checkResult( tc.first, tc.second, binarySearch( tc.first, tc.second ), 0 ) );
    }
    for ( ; k < numTestCases; ++k ) {
        testcase_t tc = tcf.testCaseNoReps();
        assert( TestCaseFactory::checkResult( tc.first, tc.second, binarySearch( tc.first, tc.second ), 0 ) );
    }
}
