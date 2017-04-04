/***************************************************************************
                         listinsertionsort.cpp  -
                             -------------------
    begin                : Mon 03 Apr 2017 21:46:40 CDT
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
#include <assert.h>

typedef TestCaseFactory::ListNode ListNode;

// struct TestCaseFactory::ListNode is defined as follows:
/*
    struct ListNode {
        int value;
        ListNode *next;
    };
*/

void insertionSort( ListNode *head ) {
    // Implement insertion sort on list here
}

int main() {
    TestCaseFactory tcf( 2048, 4096 );
    const int numTestCases = 4096;
    for ( int k = 0; k < numTestCases; ++k ) {
        std::vector<int> v = tcf.testCase();
        ListNode *head = TestCaseFactory::testCaseToList( v );
        ListNode *foo = head;
        insertionSort( head );
        assert( TestCaseFactory::checkSorted( head ) );
        TestCaseFactory::deleteList( head );
    }
    return 0;
}
