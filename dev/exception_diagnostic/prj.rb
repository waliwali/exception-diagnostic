require 'rubygems'

require 'mxx_ru/cpp'

MxxRu::Cpp::lib_target {

	target "exception_diagnostic"

	implib_path 'lib'

	cpp_source "err_stream.cpp" 
	cpp_source "ex.cpp" 
	cpp_source "collector.cpp" 
}
