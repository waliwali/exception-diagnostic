require 'rubygems'

require 'mxx_ru/cpp'

MxxRu::Cpp::lib_target {

	target "ex_diag"

	implib_path 'lib'

	cpp_source "err_stream.cpp" 
	cpp_source "ex.cpp" 
	cpp_source "collector.cpp" 
}
