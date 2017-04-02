/***************************************************************************
                           testcasefactory.h  -  
                             -------------------
    begin                : Thu 30 Mar 2017 02:44:09 CDT
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

#include <string>

/**
 * @class TestCaseFactory
 * @short 
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

class TestCaseFactory {

public:

    /**
     * @short Constructor
     */
    TestCaseFactory( int maxDigits = 8192, bool randomizeSize = true );

    /**
     * @return a testcase
     */
    std::string testcase();

    static bool checkResult( const std::string &num1, const std::string &num2, std::string result, bool addition = true );

private:

    static std::string add( const std::string &a, const std::string &b );
    int m_maxDigits;
    bool m_randomizeSize;
};

#endif
