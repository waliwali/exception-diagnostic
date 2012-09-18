
require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	implib_path 'lib'

	target 'test.sequence'

	required_prj "exception_diagnostic/prj.rb" 
	required_prj 'gtest/prj.rb'

	cpp_source 'sequence.cpp'
}
