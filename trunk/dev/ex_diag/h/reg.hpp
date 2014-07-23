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
	\file reg.hpp class reg_t<T>.
*/


#ifndef __EX_DIAG__REG_HPP__INCLUDED
#define __EX_DIAG__REG_HPP__INCLUDED

#include <ex_diag/h/collector.hpp>

#include <string>
#include <sstream>

namespace ex_diag {

//! Separates comment and value by default.
const std::string default_comment_separator = ":";

//! Class for registration an instance to diagnostic.
template <class T>
class reg
{
	public:
		//! Save link to the instance.
		/*!
			\note object automatically dumps the collector if it's not empty.
		*/
		reg( 
			//! The instance to take over diagnostic control.
			const T & instance, 
			//! Comment to this instance. Default - no comment.
			const std::string & comment = "" ) 
		:
			m_instance( instance ),
			m_comment( comment )
		{
			if ( !get_collector_instance().empty() )
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
					{
						std::stringstream buf;
						buf << 
							m_comment << 
							default_comment_separator << 
							m_instance;

						get_collector_instance() << buf.str();
					}
				}
				catch ( ... )
				{
					// Defense of the d'tor.
				}
			}
		}

	private:
		//! Link to the diagnostic object.
		const T & m_instance;
		//! Comment to this point.
		const std::string m_comment;
};

} /* namespace ex_diag */

#endif
