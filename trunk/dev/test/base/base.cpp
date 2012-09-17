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
	\brief Test base functions.
*/

#include <exception_diagnostic/h/pub.hpp>

#include <iostream>
#include <stdexcept>

#include <limits.h>
#include "gtest/1.6.0/include/gtest/gtest.h"

//! Some deep funtion, under the pass function.
void
deep_function()
{
	throw std::runtime_error( "Boom!" );
}

//! Pass function. 
/*!
	This function have instances which need 
	to dump information at failure.
*/
void
pass_function()
{
	unsigned int value = 120;
	exception_diagnostic::reg<unsigned int> reg_value( value );

	deep_function();
}

// Test simple collect and intercept.
TEST(InterceptInfo, Simple) 
{
	try
	{
		pass_function();

		// pass_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			exception_diagnostic::get_collector_instance().info().c_str(), 
			"120" );

		EXPECT_STREQ( ex.what(), "Boom!" );
	}

	// Collector must be fill after get in catch (there are no clear() or dump() ).
	EXPECT_STREQ( 
		exception_diagnostic::get_collector_instance().info().c_str(), 
		"120" );

	// Test empty after clear.
	exception_diagnostic::get_collector_instance().clear();

	EXPECT_STREQ( 
		exception_diagnostic::get_collector_instance().info().c_str(), 
		"" );
}

// Test collect, intercept and empty after dump.
TEST(InterceptInfo, EmptyAfterDump) 
{
	try
	{
		pass_function();

		// pass_function must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		exception_diagnostic::get_collector_instance().dump();
	}

	// Collector must be fill after get in catch (there are no clear() or dump() ).
	EXPECT_STREQ( 
		exception_diagnostic::get_collector_instance().info().c_str(), 
		"" );
}

int 
main( int argc, char ** argv ) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
