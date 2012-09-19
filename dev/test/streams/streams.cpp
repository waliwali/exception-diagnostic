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
	\brief Test streams and using of it.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstdio>

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

std::string
read_file_to_string( std::istream & inp ) 
{
	char ch = inp.get();
	std::string result("");

	while( !inp.eof() ) 
	{
		result += ch;
		ch = inp.get();
	}
	return result;
}

// Test of changing stream to file.
TEST(Streams, File) 
{
	const std::string filename = "test.dump";
	remove( filename.c_str() );

	std::ofstream out_file( filename.c_str(), std::ios::out );

	try
	{
		ASSERT_TRUE( out_file.good() );

		ex_diag::get_err_stream_instance().set_stream( out_file );

		test_function();

		// test_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		ex_diag::get_collector_instance().dump();

		std::ifstream in_file( filename.c_str(), std::ios::in );
		const std::string log = read_file_to_string( in_file );

		EXPECT_STREQ( 
			log.c_str()
		,	(
			"abc" + ex_diag::default_delimiter + 
			"XYZ").c_str() 
		);
	}

	out_file.close();
	remove( filename.c_str() );

	ex_diag::get_err_stream_instance().set_stream( std::cerr );
}

// Test of changing stream to string stream.
TEST(Streams, StringStream) 
{
	std::stringstream stream;

	try
	{
		ex_diag::get_err_stream_instance().set_stream( stream );

		test_function();

		// test_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		ex_diag::get_collector_instance().dump();

		EXPECT_STREQ( 
			stream.str().c_str()
		,	(
			"abc" + ex_diag::default_delimiter + 
			"XYZ").c_str() 
		);
	}

	ex_diag::get_err_stream_instance().set_stream( std::cerr );
}

int 
main( int argc, char ** argv ) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
