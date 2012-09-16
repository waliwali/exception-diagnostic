require 'rubygems'

gem 'Mxx_ru', '>= 1.5.2'

require 'mxx_ru/cpp'

MxxRu::Cpp::composite_target( MxxRu::BUILD_ROOT ) {

		global_include_path( "." )
		default_runtime_mode( MxxRu::Cpp::RUNTIME_RELEASE )
		MxxRu::enable_show_brief

		implib_path 'lib'

		required_prj "exception_diagnostic/prj.rb" 
		required_prj "samples/hello_world/prj.rb" 
		required_prj "samples/several/prj.rb" 
}