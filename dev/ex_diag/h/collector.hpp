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

//! Default divide between different object dumps.
const std::string default_delimiter = "\n";

//! Collects info about failure.
class collector_t
{
	public:
		//! Default c'tor.
		/*! 
			Info empty, delimiter is "\n".
		*/
		collector_t();

		/*! 
			Trying to dump() if not empty.
		*/
		~collector_t() throw();

		//! Add info to the collector.
		/*!
			\note usually one piece of the info.
		*/
		void
		add( 
			//! One piece of the information to collect.
			const std::string & info );

		//! Get collected info.
		/*!
			\return all collected info.
		*/
		std::string
		info();

		//! Clear collected info.
		void
		clear();

		//! collector_t has smth new info or not.
		/*!
			\retval true add() was, but subsequently info() was not called.
		*/
		bool
		have_actual_info() const;

		//! Set the delimiter at adding.
		void
		set_delimiter( 
			//! Delimiter of the collecting.
			const std::string & delimiter );

		//! Get info from this collector and dump according to the actual options.
		/*!
			\note clear internal info of the collector.
		*/
		void
		dump();

		//! Empty collector or not.
		/*!
			\retval true empty.
		*/
		bool
		empty() const;

	private:
		//! All info was got or not.
		bool m_have_actual_info;
		//! All collected info.
		std::string m_info;
		//! Delimiter between pieces of the collection.
		std::string m_delimiter;
};

//! Inserting into collector an info about the object.
/*!
	The collector can use any instance to diagnostic 
		which overload this << operator.
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
	\return object of providing collecting information about failure.
*/
collector_t &
get_collector_instance();

} /* namespace ex_diag */

#endif
