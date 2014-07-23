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
	\brief
	\file ex.hpp class ex_t.
*/

#ifndef __EX_DIAG__EX_HPP__INCLUDED
#define __EX_DIAG__EX_HPP__INCLUDED

#include <string>

namespace ex_diag {

//! The root class of exception using.
/*!
	All of information about failure will be available with the method info().
	If its method doesn't called then the application automatically sends 
	the information to the error stream. It's the std::cerr by default 
	and can be changed by the err_stream_t instance.

	\see err_stream_t
*/
class ex_t
{
	public:
		//! Default c'tor.
		/*!
			ex_t will use the default collector.
		*/
		ex_t();

		/*!
			\note if someone doesn't get all of information about failure, 
			this d'tor dumps the information into the error stream.

		*/

		virtual
		~ex_t() throw() ;

		//! Get information about the failure.
		/*!
			Return all of collected information about the failure.
		*/
		std::string
		info() const;
};

} /* namespace ex_diag */

#endif
