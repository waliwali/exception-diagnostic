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
	\file main.cpp
	\brief This example show using of several simple features.

	\detail 

	Showed features:
	* Several levels and sequence of diagnostic dump.
	* Several instances in one function and their sequence.
	* User instances.
	* User exceptions.
	* Simple way of using exception_diagnostic::ex_t class.

	System control actual state of instance: 
	diagnostic get only value which was at exception moment.

	Diagnostic info of instances will be printed in reverse order,
		according to the dtor calls.

	For diagnose our class objects it's require 
		overloading of << operator. 
*/

#include <exception_diagnostic/h/pub.hpp>

#include <iostream>

#include <stdexcept>

using exception_diagnostic::reg;

//! Route class of diagnostic exceptions.
class general_ex_t : 
	public std::runtime_error, 
	public exception_diagnostic::ex_t
{
	public:
		explicit general_ex_t( const std::string & what ) : 
			std::runtime_error( what ), exception_diagnostic::ex_t()
		{}

		virtual ~general_ex_t() throw() {}

};

//! Special user class.
/*!
	To diagnostic that we need to overload << operator.
*/
class foo_t
{
};

//! Dumping into stream o info about instance f.
std::ostream &
operator << ( std::ostream & o, const foo_t & f )
{
	return ( o << "foo" );
}

//! Some very deep funtion, under the deep function.
void
very_deep_function()
{
	throw general_ex_t( "Boom!" );
}

//! Some deep funtion, under the pass function.
/*!
	This function have some instance which need 
	to dump information at failure.
*/
void
deep_function()
{
	// Const instance.
	const std::string const_string( "const_string" );
	reg<const std::string> reg_const_string( const_string );

	// Using a user class instance.
	foo_t foo;
	reg<foo_t> reg_foo( foo );

	very_deep_function();
}

//! Pass function. 
/*!
	This function have some instances which need 
	to dump information at failure.
*/
void
pass_function()
{
	// Basic-type instance.
	int x = 100;
	reg<int> reg_x( x );

	// System control actual state of instance.
	float y = 10;
	reg<float> reg_y( y );
	y /= 100;

	deep_function();

	// This instance will not be diagnosed.
	std::string no_print( "no_print" );
	reg<std::string> reg_no_print( no_print );
}

int main()
{
	try
	{
		pass_function();
	}
	catch ( const exception_diagnostic::ex_t & ex )
	{
		// Print collected info in cout stream.
		std::cout << ex.info() << std::endl;
	}

	return 0;
}
