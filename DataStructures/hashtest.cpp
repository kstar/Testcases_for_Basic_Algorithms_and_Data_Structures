/***************************************************************************
                             hashtest.cpp  -
                             -------------------
    begin                : Thu 13 Apr 2017 04:55:48 CDT
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
#include "hash.h"

/* STL Includes */
#include <string>
#include <unordered_map>
#include <assert.h>
#include <ctime>
#include <iostream>

std::string randomString( int length ) {
    std::string rs;
    rs.reserve( length );
    for ( int i = 0; i < length; ++i )
        rs.push_back( 'a' + rand()%( 'z' - 'a' + 1 ) );
    return rs;
}

int main() {
    const int numTestCases = 4096;
    const int maxOps = 4096;
    const int maxInitialSize = 4096;
    const int maxKeyLength = 40;
    const int maxValue = 65535;

    std::srand( std::time( 0 ) );

    HashMap<std::string, int> testMap;
    std::unordered_map<std::string, int> refMap;

    for ( int k = 0; k < numTestCases; ++k  ) {

        std::cerr << "Testcase #" << k + 1 << std::endl;

        // Initialize with some data
        int initialSize = rand()%( maxInitialSize + 1 );
        for ( int j = 0; j < initialSize; ++j ) {
            std::string key = randomString( rand()%maxKeyLength + 1 );
            int value = rand()%( maxValue + 1 );
            testMap.insert( key, value );
            refMap[ key ] = value;
        }

        assert( testMap.checkTable() );


        // Perform some random operations
        int Nops = rand()%maxOps + 1;
        for ( int j = 0; j < Nops; ++j ) {
            bool insert = rand()%2;
            std::string key = randomString( rand()%maxKeyLength + 1 );
            if ( insert ) {
                int value = rand()%( maxValue + 1 );
                testMap.insert( key, value );
                refMap[ key ] = value;
                assert( testMap.at( key ) == refMap.at( key ) );
            }
            else {
                assert( bool( refMap.erase( key ) ) == testMap.erase( key ) );
                assert( !testMap.count( key ) );
            }
            assert( refMap.size() == testMap.size() );
        }

        // Verify that contents of the map are the same
        assert( testMap.checkTable() );
        for ( const auto &entry : refMap ) {
            assert( testMap.at( entry.first ) == entry.second );
        }
        assert( refMap.size() == testMap.size() );
        assert( testMap.checkTable() );

        // Remove sufficient number of elements to trigger a shrinking of the table
        int startSize = refMap.size();
        if ( startSize > 128 ) {
            while ( refMap.size() > startSize / 4 ) {
                auto it = refMap.begin();
                assert( testMap.erase( it->first ) );
                refMap.erase( it );
            }
            assert( refMap.size() == testMap.size() );
            assert( testMap.checkTable() );
        }

        // Clear both maps
        refMap.clear();
        testMap.clear();
        assert( testMap.checkTable() );

    }

}
