/***************************************************************************
                          testcasefactory.cpp  -
                             -------------------
    begin                : Sun 02 Apr 2017 16:15:23 CDT
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
#include <algorithm>
#include <ctime>
#include <cstdlib>


TestCaseFactory::TestCaseFactory( const int maxSize, const int numLimit, const bool randSize)
    : m_maxSize( maxSize ), m_numLimit( numLimit ), m_randSize( randSize ) {
    std::srand( std::time( 0 ) );
}

std::pair<std::vector<int>, int> TestCaseFactory::testCase() {
    std::vector<int> tc;

    int N = m_randSize ? rand()%m_maxSize + 1 : m_maxSize;
    tc.reserve( N );

    for ( int k = 0; k < N; ++k )
        tc.push_back( rand()%m_numLimit );

    std::sort( tc.begin(), tc.end() );

    bool needleExists = bool( rand()%2 );
    int needle = -1;
    if ( needleExists )
        needle = tc[ rand()%N ];
    else {
        // Hack: try 5 attempts to find a random number that does not exist in the array
        if ( N < m_numLimit ) {
            for ( int k = 0; k < 5; ++k ) {
                int x = rand()%m_numLimit;
                if ( *std::lower_bound( tc.begin(), tc.end(), x ) != x ) {
                    needle = x;
                    break;
                }
            }
        }
        if ( needle < 0 )
            needle = -( rand()%m_numLimit );
    }

    return make_pair( tc, needle );
}

std::pair<std::vector<int>, int> TestCaseFactory::testCaseNoReps() {
    std::vector<int> tc;

    if ( m_maxSize > m_numLimit )
        return std::pair<std::vector<int>, int>( tc, -1 );

    int N = m_randSize ? rand()%m_maxSize + 1 : m_maxSize;

    tc.reserve( N );

    // Use reservoir sampling to generate the testcase
    // Standard reservoir sampling: Algorithm R -- keep with probability N / i
    // O( numLimit )
    int i = 0;
    int needle = -1;
    for ( i = 0; i < N; ++i )
        tc.push_back( i );

    for ( ; i < m_numLimit; ++i ) {
        int j = rand()%i;
        if ( j < N )
            tc[j] = i;
        else
            if ( rand()%2 )
                needle = i; // By default, needle is an element that doesn't exist.
    }

    std::sort( tc.begin(), tc.end() );

    if ( rand()%2 )
        needle = tc[ rand()%N ]; // Pick an element that exists

    return make_pair( tc, needle );
}

bool TestCaseFactory::checkResult(const std::vector<int>& data, const int value, int resultIndex, signed short searchType) {
    auto ub = std::upper_bound( data.begin(), data.end(), value );
    auto lb = std::lower_bound( data.begin(), data.end(), value );
    if ( searchType == 0 ) {
        if ( resultIndex < 0 )
            return ( ub == lb );
        else
            return ( resultIndex >= lb - data.begin() && resultIndex < ub - data.begin() );
    }
    else if ( searchType > 0 )
        return ( ub == resultIndex + data.begin() );
    else
        return ( lb == resultIndex + data.begin() );
}
