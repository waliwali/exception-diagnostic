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
	\brief This example shows changing of diagnostic stream.

	\detail 

	Showed features:
	* Changing of diagnostic stream.
	* Auto dump if user forgot to get dump information 
		at the ex_diag::ex_t using.
	* Process dump info by hand.

	If stack unwinding happened, the diagnostic system automatically dumps 
	info at the first registration try.

	If developer doesn't use ex_diag::ex_t, 
		he can process info by hand.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>
#include <fstream>

#include <stdexcept>

using ex_diag::reg;

//! Some very deep funtion, under the deep function.
void
deep_function()
{
	throw std::runtime_error( "Boom!" );
}

//! Pass function. 
/*!
	This function has some instances which need 
	to dump information at the failure.
*/
void
pass_function()
{
	std::string text( "Some simple text" );

	// Twice at this point (second and third run_at_once) 
	// system automatically dumps the internal info.
	reg<std::string> reg_text( text );

	deep_function();
}

//! One run of main function.
void
run_at_once()
{
	try
	{
		pass_function();
	}
	catch ( const std::exception & ex )
	{
		// User forgot dump in some stream.
		// User doesn't use diagnostic exception type, 
		// and auto-dumping is off.

		// However, first try of registration (after such stack 
		// unwiding) will automatically dump info.
	}
}

int main()
{
	// Dump into log_file.
	std::ofstream log_file( "log_file" );
	ex_diag::get_err_stream_instance().set_stream( log_file );

	// Three runs.
	// Only two of them will dump automatically.
	run_at_once();
	run_at_once();
	run_at_once();

	// We can pull down info by ourself.
	// Check collector info.
	if ( !ex_diag::get_collector_instance().empty() )
	{
		// Smth in the collector.
		// Change dump stream and dump.
		ex_diag::get_err_stream_instance().set_stream( std::cout );
		ex_diag::get_collector_instance().dump();
	}

	return 0;
}
