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
	\brief This is simple example of exeption diagnostic.
		Nothing superfluous.

	\detail 

	Showed features:
	* Syntax of registration of instance.
	* Intercepting of information.
	* Receiving of collected information.
*/

#include <ex_diag/h/pub.hpp>

#include <iostream>

#include <stdexcept>

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
	// Work instance.
	std::string message( "Hello World!" );
	// Auto-diagnostic instance.
	ex_diag::reg<std::string> reg_message( message );

	deep_function();
}

int main()
{
	try
	{
		pass_function();
	}
	catch ( const std::exception & ex )
	{
		// Print collected info in cout stream.
		std::cout << 
			ex_diag::
			get_collector_instance().info() << std::endl;
	}

	return 0;
}
