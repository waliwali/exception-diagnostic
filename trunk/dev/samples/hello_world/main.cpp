/*!
	\file main.cpp
	\brief This is simple example of exeption diagnostic.
		Nothing superfluous.
*/

#include <exception_diagnostic/h/pub.hpp>

#include <iostream>

#include <stdexcept>

//! Some deep funtion, under the pass function.
void
deep_function()
{
	throw exception_diagnostic::ex_t();
}

//! Pass function. 
/*!
	This function have objects which need 
	to dump information at failure.
*/
void
pass_function()
{
	//! Work instance.
	std::string message( "Hello World!" );
	//! Auto-diagnostic instance.
	exception_diagnostic::reg<std::string> reg_message( message );

	deep_function();
}

int main()
{
	try
	{
		pass_function();
	}
	catch ( const exception_diagnostic::ex_t & ex )
	{
		// Print collected info into cout stream.
		std::cout << ex.info() << std::endl;
	}

	return 0;
}
