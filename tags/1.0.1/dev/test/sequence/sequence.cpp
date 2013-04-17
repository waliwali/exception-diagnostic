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
	\brief Test sequence of registration and dumping.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

#include <limits.h>
#include "gtest/1.6.0/include/gtest/gtest.h"

const std::string default_delimiter = "\n";

using ex_diag::reg;

//! One stack test function. 
void
one_stack_test()
{
	std::string value1 = "abc";
	reg<std::string> reg_value1( value1 );

	std::string value2 = "XYZ";
	reg<std::string> reg_value2( value2 );

	std::string value3 = "109";
	reg<std::string> reg_value3( value3 );

	throw std::runtime_error( "Boom!" );
}

// Test stack of one function.
TEST(Sequence, FunctionStack) 
{
	try
	{
		one_stack_test();

		// one_stack_test must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	(
			"109" + ex_diag::default_delimiter + 
			"XYZ" + ex_diag::default_delimiter + 
			"abc").c_str() 
		);
	}

	ex_diag::get_collector_instance().clear();
}

void
deep_function_stack()
{
	std::string value = "123";
	reg<std::string> reg_value( value );

	throw std::runtime_error( "Boom!" );
}

//! First function of stack.
void
function_stack()
{
	std::string value = "qwe";
	reg<std::string> reg_value( value );

	deep_function_stack();
}

// Test stack of one function.
TEST(Sequence, DeepFunctionStack) 
{
	try
	{
		function_stack();

		// function_stack must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	("123" + default_delimiter + "qwe").c_str() 
		);
	}

	ex_diag::get_collector_instance().clear();
}

//! Class with some fields.
class foo_t
{
	public:
		foo_t() : 
			m_field_b( "B" ), reg_field_b( m_field_b ), 
			m_field_a( "A" ), reg_field_a( m_field_a )
		{}
	private:
		//! First created, last destroyed and dumped.
		std::string m_field_a;
		reg<std::string> reg_field_a;

		//! Last created, first destriyed and dumped.
		std::string m_field_b;
		reg<std::string> reg_field_b;
};

void
class_fields_test()
{
	foo_t a;
	foo_t b;

	throw std::runtime_error( "Boom!" );
}

// Test stack of one function.
TEST(Sequence, ClassFields) 
{
	try
	{
		class_fields_test();

		// class_fields_test must throw exception.
		FAIL();
	}
	catch ( const std::exception & ex )
	{
		EXPECT_STREQ( 
			ex_diag::get_collector_instance().info().c_str()
		,	("B" + default_delimiter + 
			"A" + default_delimiter + 
			"B" + default_delimiter + "A").c_str() 
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
