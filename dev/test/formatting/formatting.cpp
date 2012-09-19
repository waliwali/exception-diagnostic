/*
	Copyright (c) 2010, Boris Sivko
	All rights reserved.

	E-mail: bsivko@gmail.com (Boris Sivko)

	This file is part of Exeption Diagnostic Library.

	Redistribution and use in source and binary forms, with or without 
	modification, are permitted provided that the following conditions are met:

	Redistributions of source code must retain the above copyright notice, 
	this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright notice, 
	this list of conditions and the following disclaimer in the documentation 
	and/or other materials provided with the distribution.

	Neither the name of the Intervale nor the names of its contributors 
	may be used to endorse or promote products derived from this software 
	without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
	USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*!
	\file base.cpp
	\brief Test formatting of info.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

#include <limits.h>
#include "gtest/1.6.0/include/gtest/gtest.h"

using ex_diag::reg;

//! Test function. 
void
test_function()
{
	std::string value2 = "XYZ";
	reg<std::string> reg_value2( value2 );

	std::string value1 = "abc";
	reg<std::string> reg_value1( value1 );

	throw std::runtime_error( "Boom!" );
}

// Test of default formatting.
TEST(Formatting, DelimiterDefault) 
{
	try
	{
		test_function();

		// test_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	(
			"abc" + ex_diag::default_delimiter + 
			"XYZ").c_str() 
		);
	}

	ex_diag::get_collector_instance().clear();
}


void
test_user_delimiter( const std::string & user_delimiter )
{
		try
	{
		ex_diag::get_collector_instance().
			set_delimiter( user_delimiter );

		test_function();

		// test_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	(
			"abc" + user_delimiter + 
			"XYZ").c_str() 
		);
	}

	ex_diag::get_collector_instance().
		set_delimiter( ex_diag::default_delimiter );

	ex_diag::get_collector_instance().clear();
}

// Test user long delimiter.
TEST(Formatting, DelimiterUserLong) 
{
	test_user_delimiter( "ASD" );
}

// Test user empty delimiter.
TEST(Formatting, DelimiterEmpty) 
{
	test_user_delimiter( "" );
}

//! Test comment function. 
void
test_comment_function()
{
	std::string value2 = "XYZ";
	reg<std::string> reg_value2( value2, "comment" );

	std::string value1 = "abc";
	reg<std::string> reg_value1( value1, "" );

	std::string value3 = "321";
	reg<std::string> reg_value3( value3, "info" );

	throw std::runtime_error( "Boom!" );
}

// Test of comment.
TEST(Formatting, Comment) 
{
	try
	{
		test_comment_function();

		// test_comment_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	(
			"info:321" + ex_diag::default_delimiter + 
			"abc" + ex_diag::default_delimiter + 
			"comment:XYZ").c_str() 
		);
	}

	ex_diag::get_collector_instance().clear();
}


int 
main( int argc, char ** argv ) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
