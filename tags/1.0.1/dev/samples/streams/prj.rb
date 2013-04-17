require 'rubygems'

require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj "ex_diag/prj.rb" 

	implib_path 'lib'

	target( "sample.streams" )

	cpp_source( "main.cpp" )
}
