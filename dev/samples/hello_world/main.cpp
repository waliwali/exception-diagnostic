#include <exception_diagnostic/h/pub.hpp>

#include <iostream>

//! Route class of diagnostic exceptions.
class general_ex_t : 
	public std::runtime_error, 
	public exception_diagnostic::ex_t
{
	public:
		explicit general_ex_t( const std::string & what ) : 
			std::runtime_error( what )
		{}
};

//! Some deep funtion, under the pass function.
void
deep_function()
{
	throw general_ex_t( "Boom!" );
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
	catch ( exception_diagnostic::ex_t & ex )
	{
		// Print collected info into cout stream.
		std::cout << ex.info() << std::endl;
	}

	return 0;
}
