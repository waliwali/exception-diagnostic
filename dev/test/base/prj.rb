
require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	implib_path 'lib'

	target 'test.base'

	required_prj "ex_diag/prj.rb" 
	required_prj 'gtest/prj.rb'

	cpp_source 'base.cpp'
}
