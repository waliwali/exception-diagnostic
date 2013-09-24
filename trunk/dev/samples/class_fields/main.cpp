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
	\brief This example shows the diagnosis of class fields.

	\detail 

	Showed features:
	* The registration of class fields.
	* Auto dump if user forgot to get dump the information 
		at the ex_diag::ex_t using.

	Instances 'reg' have to be after their undercontrol instances.

	Developer can get the info from the colletor or not. 
	However, if this info wasn't got, the system automatically dump the info 
		according to the actual options. 
	This is showed for the ex_diag::ex_t behaviour.
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

//! Simple person class.
class person_t
{
	public:
		person_t( 
			const std::string & name, 
			unsigned int age )
		:	
			m_name( name ), 
			m_age( age ), 
			m_reg_age( m_age, name + " age" ), 
			m_number( get_new_number() ), 
			m_reg_number( m_number, name + " number" )
		{}

		std::string
		name() const
		{
			return m_name;
		}

		unsigned int
		age() const
		{
			return m_age;
		}

		static unsigned int
		get_new_number()
		{
			static unsigned int number = 0;
			++number;
			return number;

		}

	private:
		//! Person age.
		unsigned int m_age;
		reg<unsigned int> m_reg_age;

		//! Person name.
		const std::string m_name;

		//! Person number.
		unsigned int m_number;
		reg<unsigned int> m_reg_number;
};

//! Some very deep funtion, under the deep function.
void
deep_function()
{
	throw general_ex_t( "Boom!" );
}

//! Pass function. 
/*!
	This function has some instances which need 
	to dump information at the failure.
*/
void
pass_function()
{
	person_t first( "John Smith", 34 );
	person_t second( "Jessica Golden", 25 );

	deep_function();
}

int main()
{
	try
	{
		pass_function();
	}
	catch ( const ex_diag::ex_t & ex )
	{
		// User forgot the dump.
		// The system automatically dumps into the std::cerr 
		// according to actual options.
	}

	return 0;
}
