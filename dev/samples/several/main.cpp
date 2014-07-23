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
	\brief This example shows using of several simple features.

	\detail 

	Features, which are presented:
	* Several levels and the diagnostic dump sequence.
	* Several instances in one function and their sequence.
	* User instances.
	* User exceptions.
	* A simple way of using ex_diag::ex_t class.

	The system controls actual state of the instance: 
	diagnosis get only a value which was at the exception moment.

	The diagnostic information about instances will be printed in the reverse order,
		according to the d'tor calls.

	\note For class diagnose a overloading of the '<<'-operator is required.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>

#include <stdexcept>

using ex_diag::reg;

//! The root class of diagnostic exceptions.
class general_ex_t : 
	public std::runtime_error, 
	public ex_diag::ex_t
{
	public:
		explicit general_ex_t( const std::string & what ) : 
			std::runtime_error( what ), ex_diag::ex_t()
		{}

		virtual ~general_ex_t() throw() {}

};

//! A special user class.
/*!
	To diag we need to overload '<<' operator.
*/
class foo_t
{
};

//! The dumping into the stream 'o' information about the instance 'f'.
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
	The function has some instance which need 
	to dump the information at the failure.
*/
void
deep_function()
{
	// A 'const' instance.
	const std::string const_string( "const_string" );
	reg<const std::string> reg_const_string( const_string );

	// Using a user class instance.
	foo_t foo;
	reg<foo_t> reg_foo( foo );

	very_deep_function();
}

//! A pass function. 
/*!
	The function has some instances which need 
	to dump the information at the failure.
*/
void
pass_function()
{
	// A basic-cpp-type instance.
	int x = 100;
	reg<int> reg_x( x );

	// The system controls actual state of the instance.
	float y = 10;
	reg<float> reg_y( y );
	y /= 100;

	deep_function();

	// The instance will not be diagnosed.
	std::string no_print( "no_print" );
	reg<std::string> reg_no_print( no_print );
}

int main()
{
	try
	{
		pass_function();
	}
	catch ( const ex_diag::ex_t & ex )
	{
		// Print collected information into the std::cout stream.
		std::cout << ex.info() << std::endl;
	}

	return 0;
}
