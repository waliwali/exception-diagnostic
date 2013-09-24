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
	\file err_stream.hpp class err_stream_t.
*/

#ifndef __EX_DIAG__ERR_STREAM_HPP__INCLUDED
#define __EX_DIAG__ERR_STREAM_HPP__INCLUDED

#include <ostream>

namespace ex_diag {

//! Controller of the diagnostic stream.
/*!
	Provide opportunity to change the diagnostic stream at failures.
*/
class err_stream_t
{
	public:
		//! Default stream is std::cerr.
		err_stream_t();

		//! Set a new stream.
		void
		set_stream( 
			//! This stream will use after set.
			std::ostream & o );

		//! Get the actual stream.
		/*!
			\return object of the actual stream.
		*/
		std::ostream &
		stream();

	private:
		//! Stream of the unexpected diagnostic.
		std::ostream * m_stream;
};

//! Get default error stream instance.
/*!
	\return object of providing default error stream.
*/
err_stream_t &
get_err_stream_instance();

} /* namespace ex_diag */

#endif
