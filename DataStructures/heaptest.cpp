/***************************************************************************
                             heaptest.cpp  -
                             -------------------
    begin                : Tue 04 Apr 2017 02:06:43 CDT
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
#include "heap.h"

/* STL Includes */
#include <cstdlib>
#include <ctime>
#include <queue>
#include <assert.h>

int main() {
    std::srand( std::time( 0 ) );

    const int numTestCases = 4096;
    const int maxKey = 1024;
    const int maxInitialSize = 512;
    const int maxOperationCount = 1024;

    for ( int k = 0; k < numTestCases; ++k ) {

        // Make a vector containing the initial contents of the heap
        std::vector<int> v;
        int N = rand()%( maxInitialSize + 1 );
        v.reserve( N );
        for ( int l = 0; l < N; ++l )
            v.push_back( rand()%( maxKey + 1 ) );

        std::priority_queue<int> refHeap( std::less<int>(), v ); // this is our reference heap to check the heap
        MaxHeap testHeap( v ); // this is our test heap
        int Nops = rand() % maxOperationCount;
        for ( int l = 0; l < Nops; ++l ) {
            bool insert = ( rand() % 2 ) || testHeap.empty();
            if ( insert ) {
                int key = rand()%( maxKey + 1 );
                refHeap.push( key );
                testHeap.push( key );
            }
            else {
                refHeap.pop();
                testHeap.pop();
            }
            assert( testHeap.empty() || refHeap.top() == testHeap.top() );
        }

        while ( !testHeap.empty() ) {
            assert( testHeap.top() == refHeap.top() );
            testHeap.pop();
            refHeap.pop();
        }
        assert( refHeap.empty() );

    }
}
