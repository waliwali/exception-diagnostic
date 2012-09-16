require 'rubygems'

require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj "exception_diagnostic/prj.rb" 

	implib_path 'lib'

	target( "sample.hello_world" )

	cpp_source( "main.cpp" )
}
