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
	\file collector.hpp class collector_t.
*/

#ifndef __EX_DIAG__COLLECTOR_HPP__INCLUDED
#define __EX_DIAG__COLLECTOR_HPP__INCLUDED

#include <string>
#include <sstream>

namespace ex_diag {

//! Default separator between different object dumps.
const std::string default_delimiter = "\n";

//! This instance collects information about failure.
class collector_t
{
	public:
		//! Default c'tor.
		/*! 
			Information is absent, delimiter is "\n".
		*/
		collector_t();

		/*! 
			Trying to dump() if it's not empty.
		*/
		~collector_t() throw();

		//! Add information to the collector.
		/*!
			\note usually one piece of the information.
		*/
		void
		add( 
			//! Oneinformation piece to collect.
			const std::string & info );

		//! Get collected information.
		/*!
			\return all of collected information.
		*/
		std::string
		info();

		//! Clear collected information.
		void
		clear();

		//! collector_t has smth new information or not.
		/*!
			\retval true add() was invoked, but subsequently info() was not called.
		*/
		bool
		have_actual_info() const;

		//! Set the delimiter at adding.
		void
		set_delimiter( 
			//! Collecting delimiter.
			const std::string & delimiter );

		//! Get information from the collector and dump according to the actual options.
		/*!
			\note clear internal information of the collector.
		*/
		void
		dump();

		//! The collector is empty or not.
		/*!
			\retval true empty.
		*/
		bool
		empty() const;

	private:
		//! All of information was got or not.
		bool m_have_actual_info;
		//! All of collected information.
		std::string m_info;
		//! The delimiter between pieces of the collection.
		std::string m_delimiter;
};

//! Inserting into the collector some information about the object.
/*!
	The collector can use any instance to diagnostic 
		which overloads this << operator.
*/
template <class T>
collector_t &
operator << ( collector_t & c, const T & v )
{
	std::stringstream buf;
	buf << v;
	c.add( buf.str() );

	return c;
}

//! Get default collector.
/*!
	\return objectm which provides all of collected information about failure.
*/
collector_t &
get_collector_instance();

} /* namespace ex_diag */

#endif
