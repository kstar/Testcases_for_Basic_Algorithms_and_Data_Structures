/***************************************************************************
                          testcasefactory.cpp  -
                             -------------------
    begin                : Thu 30 Mar 2017 02:47:47 CDT
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
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <algorithm>
#include <iostream>

TestCaseFactory::TestCaseFactory(int maxDigits, bool randomizeSize)
    : m_maxDigits( maxDigits ), m_randomizeSize( randomizeSize ) {

    std::srand( std::time( 0 ) );

}

std::string TestCaseFactory::testcase() {
    std::string tc;

    int N = m_randomizeSize ? rand() % m_maxDigits + 1 : m_maxDigits;
    tc.reserve( N );

    int i = -1;

    switch( rand()%4 ) {
    case 0:
        tc.push_back( '+' );
        break;
    case 1:
    case 2:
        tc.push_back( '-' );
        break;
    default:
        ;
    }

    while( ++i < N )
        tc.push_back( rand()%10 + '0' );

    return tc;
}


bool TestCaseFactory::checkResult(const std::string& num1, const std::string& num2, std::string result, bool addition) {
    if ( result[0] == '+' )
        result = result.substr( 1 );
    std::string knownResult;
    if ( !addition ) {
//        std::cout << "Subtraction test" << std::endl;
        std::string b( num2 );
        if ( num2[0] == '+' )
            b[0] = '-';
        else if ( num2[0] == '-' )
            b[0] = '+';
        else
            b.insert( b.begin(), '-' );
//        std::cout << "b is now " << b << std::endl;
        knownResult = add( num1, b );
    }
    else
        knownResult = add( num1, num2 );

    auto trim = []( std::string &trimThis ) {
        int trimPoint = 0;
        bool neg = false;
        if ( trimThis[0] == '+' )
            ++trimPoint;
        else if ( trimThis[0] == '-' ) {
            neg = true;
            ++trimPoint;
        }
        while ( trimThis[ trimPoint ] == '0' )
            ++trimPoint;
        trimThis = std::string( neg ? "-" : "" ) + trimThis.substr( trimPoint );
    };

//    std::cout << "Expected result: " << knownResult << std::endl;
//    std::cout << "Actual result: " << result << std::endl;

    trim( knownResult );
    trim( result );

//    std::cout << "Expected result after trimming: " << knownResult << std::endl;
//    std::cout << "Actual result after trimming: " << result << std::endl;

    return ( knownResult == result );
}


std::string TestCaseFactory::add(const std::string& a, const std::string& b) {
//    std::cout << "Adding: " << a << " and " << b << std::endl;
    bool neg_a( false ), neg_b( false );
    if ( a.size() == 0 )
        return b;
    if ( b.size() == 0 )
        return a;
    if ( a[0] == '-' )
        neg_a = true;
    if ( b[0] == '-' )
        neg_b = true;

    auto mostSignificantDigit = []( const std::string &s ) {
        auto sit = s.begin();
        while ( sit != s.end() && ( *sit == '0' || *sit == '+' || *sit == '-' ) )
            ++sit;
        return sit;
    };

    auto msd_a = mostSignificantDigit( a );
    auto msd_b = mostSignificantDigit( b );
    int size_a = a.end() - msd_a;
    int size_b = b.end() - msd_b;
    if ( size_a == 0 ) return b;
    if ( size_b == 0 ) return a;

    int comp = 0;

    if ( size_a > size_b )
        comp = 1;
    else if ( size_a < size_b )
        comp = -1;
    else {
        auto ait = msd_a; auto bit = msd_b;
        while ( ait != a.end() ) {
            if ( *ait > *bit ) {
                comp = 1; break;
            }
            else if ( *ait < *bit ) {
                comp = -1; break;
            }
            else {
                ++ait; ++bit;
            }
        }
    }

    // std::cerr << "Compare result: " << comp << std::endl;
    bool neg_result = ( ( neg_a && neg_b ) || ( neg_a && comp > 0 ) || ( neg_b && comp < 0 ) );
    const std::string &top = ( comp >= 0 )? a : b;
    const std::string &bottom = ( comp < 0 )? a : b;
    auto top_msd = ( comp >= 0 ) ? msd_a : msd_b;
    auto bottom_msd = ( comp < 0 ) ? msd_a : msd_b;
    auto top_size = ( comp >= 0 ) ? size_a : size_b;
    std::string result;
    result.reserve( top_size + 1 );

    auto singleDigitOperation = []( const char &t, const char &b, const bool &subtract, short &carry ) -> char {
        char res = ( ( subtract ) ? ( ( t - b ) + '0' - carry ) : ( t + ( b - '0' ) + carry ) );
        carry = 1;
        if ( res > '9' )
            res -= 10;
        else if ( res < '0' )
            res += 10;
        else
            carry = 0;
        return res;
    };

    short carry = 0;
    bool subtract = ( ( neg_a && !neg_b ) || ( neg_b && !neg_a ) );
    auto tit = top.end();
    auto bit = bottom.end();
    do {
        --tit; --bit;
        result.push_back( singleDigitOperation( *tit, *bit, subtract, carry ) );
    } while ( bit != bottom_msd );

    while ( tit != top_msd ) {
        --tit;
        result.push_back( singleDigitOperation( *tit, '0', subtract, carry ) );
    }
    if ( carry ) {
        assert( !subtract );
        result.push_back( '1' );
    }
    if ( neg_result )
        result.push_back( '-' );

    std::reverse( result.begin(), result.end() );
    return result;

}
