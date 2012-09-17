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

#include <exception_diagnostic/h/collector.hpp>
#include <exception_diagnostic/h/err_stream.hpp>

namespace exception_diagnostic {

collector_t::collector_t() 
:	m_info( "" ), 
	m_delimiter( "\n" ), 
	m_have_actual_info( false )
{
}

void
collector_t::add( const std::string & info )
{
	m_have_actual_info = true;

	if ( !m_info.empty() )
		m_info += m_delimiter + info;
	else
		m_info = info;
}

std::string
collector_t::info()
{
	m_have_actual_info = false;
	return m_info;
}

bool
collector_t::have_actual_info() const
{
	return m_have_actual_info;
}

void
collector_t::clear()
{
	m_have_actual_info = false;
	m_info = "";
}

void
collector_t::set_delimiter( const std::string & delimiter )
{
	m_delimiter = delimiter;
}

void
collector_t::dump()
{
	get_err_stream_instance().stream() << info();
	clear();
}

bool
collector_t::empty() const
{
	return m_info.empty();
}

collector_t &
get_collector_instance()
{
	static collector_t collector;
	return collector;
}

} /* namespace exception_diagnostic */
