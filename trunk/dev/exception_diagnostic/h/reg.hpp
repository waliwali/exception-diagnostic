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

#ifndef __EXCEPTION_DIAGNOSTIC__REG_HPP__INCLUDED
#define __EXCEPTION_DIAGNOSTIC__REG_HPP__INCLUDED

#include <exception_diagnostic/h/collector.hpp>

#include <string>

namespace exception_diagnostic {

//! Class for registration instance to diagnostic.
template <class T>
class reg
{
	public:
		//! Save link to the instance.
		/*!
			\note automatically dump collector if it not empty.
		*/
		reg( 
			//! Instance under control.
			const T & instance, 
			//! Comment to this instance. Default - no comment.
			const std::string & comment = "" ) 
		:
			m_instance( instance ),
			m_comment( comment )
		{
			if ( !get_collector_instance().is_empty() )
				get_collector_instance().dump();
		}

		/*!
			If default alert, activate diagnostic.
		*/
		~reg() throw()
		{
			if ( std::uncaught_exception() )
			{
				try
				{
					if ( m_comment.empty() )
						get_collector_instance() << m_instance;
					else
						get_collector_instance() << 
							m_comment << ":" << 
							m_instance << ";";
				}
				catch ( ... )
				{
					// Defense of dtor.
				}
			}
		}

	private:
		//! Link to the diagnostic object.
		const T & m_instance;
		//! Comment to this point.
		const std::string m_comment;
};

} /* namespace exception_diagnostic */

#endif
