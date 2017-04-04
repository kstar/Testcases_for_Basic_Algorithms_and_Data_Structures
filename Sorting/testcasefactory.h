/***************************************************************************
                           testcasefactory.h  -  
                             -------------------
    begin                : Wed 29 Mar 2017 20:04:18 CDT
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

#include <vector>
#include <limits>

/**
 * @class TestCaseFactory
 * @short Test case factory for sorting problems
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

class TestCaseFactory {

public:

    struct ListNode {
        int value;
        ListNode *next;
    };

    /**
     * @short Constructor
     * @param maxSize is the size of the largest possible testcase
     * @param randSize if false, the size of the testcase is always maxSize
     * @param numLimit specifies the range [0, numLimit) of possible values in the testcase
     */
    TestCaseFactory( int maxSize = 1024, const int numLimit = std::numeric_limits<int>::max(), bool randSize = true );

    /**
     * @short Get testcase
     */
    std::vector<int> testCase();

    /**
     * @short Get a testcase without repetition of numbers
     * @note if the numeric limit is smaller than the size requested, this method returns an empty vector
     */
    std::vector<int> testCaseNoReps();

    /**
     * @short Convert a vector test case into a singly-linked list
     */
    static ListNode *testCaseToList( const std::vector<int> &testCaseV );

    /**
     * @short deletes the list, convenience method
     */
    static void deleteList( ListNode *head );

    /**
     * @short Checks if the given vector is sorted in ascending order
     */
    static bool checkSorted( const std::vector<int> &v );

    /**
     * @short Checks if the given list is sorted in ascending order
     */
    static bool checkSorted( const ListNode *head );

private:
    int m_maxSize, m_numLimit;
    bool m_randSize;
};

#endif
