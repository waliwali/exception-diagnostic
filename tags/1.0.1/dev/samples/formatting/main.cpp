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
	\brief This example shows format tools.

	\detail 

	Showed features:
	* Special comments for instances.
	* Delimiters of group dumping.
	* Registration of received by function instances.

	Delimiter can be set at any time of runtime.

	We can register any instance at any point.

	Comments can be used or not. Empty comment is equal 'no comment'.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>

#include <stdexcept>

using ex_diag::reg;

//! Route class of diagnostic exceptions.
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

//! Some deep funtion, under the pass function.
void
process_one( 
	//! Value for processing.
	unsigned int value )
{
	if ( value == 3 )
		throw general_ex_t( "Boom!" );
}

//! Pass function. 
/*!
	This function have some instances which need 
	to dump information at failure.
*/
void
process_all( unsigned int number )
{
	// Registration of received instance.
	reg<unsigned int> reg_number( number, "Overall numbers of task" );

	// Internal counter.
	unsigned int count = 0;
	reg<unsigned int> reg_count( count, "Count of precessed numbers" );

	// Process part.
	for( unsigned int i = 0; i < number; ++i )
	{
		process_one( i );
		++count;
	}
}

int main()
{
	// Set delimiter for sequence of dump pieces.
	ex_diag::get_collector_instance().set_delimiter( "; " );

	try
	{
		process_all( 5 );
	}
	catch ( const ex_diag::ex_t & ex )
	{
		// Print collected info into cout stream.
		std::cout << ex.info() << std::endl;
	}

	return 0;
}
