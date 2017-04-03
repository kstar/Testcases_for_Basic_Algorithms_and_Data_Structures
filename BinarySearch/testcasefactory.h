/***************************************************************************
                           testcasefactory.h  -  
                             -------------------
    begin                : Sun 02 Apr 2017 16:09:43 CDT
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



#ifndef TESTCASEFACTORY_H
#define TESTCASEFACTORY_H
/**
 * @class TestCaseFactory
 * @short Generates sorted array test cases for binary search, upper bound, lower bound
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

#include <vector>
#include <tuple>
#include <limits>

class TestCaseFactory {

public:

    /**
     * @short Constructor
     */
    TestCaseFactory( const int maxSize = 4096, const int numLimit = std::numeric_limits<int>::max(), const bool randSize = true );

    /**
     * @return a testcase that contains a sorted vector and an element that with roughly equal probability does / does not exist in the vector
     */
    std::pair<std::vector<int>, int> testCase();

    /**
     * @return a testcase with no repititions
     */
    std::pair<std::vector<int>, int> testCaseNoReps();

    /**
     * @return true if the result is correct
     * @param searchType is zero for binary search, 1 for upper_bound and -1 for lower_bound
     */
    static bool checkResult( const std::vector<int> &data, const int value, const int resultIndex, const signed short searchType = 0 );

private:

    int m_maxSize, m_numLimit;
    bool m_randSize;
};

#endif
