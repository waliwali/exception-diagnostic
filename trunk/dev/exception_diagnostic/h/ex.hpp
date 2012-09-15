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

#ifndef __EXCEPTION_DIAGNOSTIC__EX_HPP__INCLUDED
#define __EXCEPTION_DIAGNOSTIC__EX_HPP__INCLUDED

#include <string>

namespace exception_diagnostic {

//! Class of root exceptions using.
/*!
	Information about falure will be available by method info().
	If it mthd don't called then application automatically sent 
	information to the error stream. It's the std::err by default 
	and can be changed by err_stream_t instance (see err_stream.hpp).
*/
class ex_t
{
	public:
		//! Default ctor.
		/*!
			was_got set to false, info to empty.

			Use default collector.

			\note set alert to ON.
		*/
		ex_t();

		/*!
			\note if someone don't get info about failure, 
			this dtor dump info into the error stream.

			Set alert into OFF.
		*/
		virtual 
		~ex_t() throw() ;

		//! Get info about failure.
		/*!
			Return all collected info about failure.
		*/
		std::string
		info();

	private:
		//! Info was got ot not.
		bool m_was_got;
		//! Buffer of collected info.
		std::string m_info;
};

} /* namespace exception_diagnostic */

#endif
