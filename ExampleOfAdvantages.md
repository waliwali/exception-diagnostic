# Function #

Let's look at the following function. This is an example, and it's a part of an action code.

The function parses some information of a special data-file, checks it and converts into some internal representation.

Only notice, that the function has several sub-functions: get\_utfmarker\_line(), check\_elements(), getline(), check\_and\_union\_ranges().

It's just an example and the function logic doesn't matter.

```
void
parse_file( const std::string & filename ) 
{
	std::ifstream file( filename.c_str() );
 
	if ( !file.good() )
	{
		throw phone_ranges_error_t( 
			"Can't open file '" + filename + "' to parse." );
	}
 
	// Receive first line and cut marker (if it's present).
	elements_t elements = get_utfmarker_line( file );
 
	// Parse all file and collect a map.
	ranges_t ranges;
	while( true )
	{
		check_elements( elements, ranges );
 
		ranges_t::const_iterator it = 
			ranges.find( range_t( elements[0], elements[1] ) );
 
		if ( it == ranges.end() )
			ranges[ range_t( elements[0], elements[1] ) ] = elements[2];
 
		if ( file.eof() )
			break;
 
		elements = getline( file );
	}
 
	check_and_union_ranges( ranges );
 
	m_ranges = ranges;
}
```

# Problem #

Let's imagine that we need to describe the context 'filename' if something wrong happened at the function. In other words, if an exception occurs, we would like to diagnose (log/send/show/..) the filename.

How can we do it?

There are two examples of a conventional solution below.

## First: add information to passing exceptions ##

```
void
parse_file( const std::string & filename ) 
{
	std::ifstream file( filename.c_str() );

	try
	{
		...
	}
	catch( const std::runtime_error & ex )
	{
		throw std::runtime_error( 
			ex.what() + " parse_file filename:" + filename + ";" );
	}
 
}
```

This way has several drawbacks:
  * We need to capture all of exception types. As a result:
    * A lot of catches (it leads to a huge code).
    * We can easy forget some exception type at the catch block.
    * We can't catch unknown types of exceptions.
  * We need to write try (1) and catch (2) - it's two places of control. And we have to add an extra tab to all of that function lines. All of these increases complexity and the code perception.
  * The catch initiates a c'tor of the exception instance (ex).

## Second: pass information to sub-functions ##

One of the ways:

```
void
parse_file( const std::string & filename ) 
{
	std::ifstream file( filename.c_str() );
 
...
 
	elements_t elements = get_utfmarker_line( file, filename );

...
 
		check_elements( elements, ranges, filename );
 
...

		elements = getline( file, filename );

...
 
	check_and_union_ranges( ranges, filename );

...
}
```

There are several disadvantages:
  * One extra parameter to every function:
    * Code will be more complex and support will be painful.
    * We must control every function. And most likely, we'll forget some of them.
    * Besides of passing parameter to the function, we need to add the information about filename to every throw place.
  * We can't control external exceptions.

# Library solution #

The library provide a wrapper, which collects information automatically if an exception occurs.

To do it, we need to add just one line:

```
void
parse_file( const std::string & filename ) 
{
	ex_diag::reg<std::string> reg_file ( filename, "parse filename" );
...

```

At end-points, where we capture exceptions, we can use all of diagnostic information or it will be dumped automatically.

The dumping by hand:

```
	catch ( ... )
	{
		std::cout << 
			ex_diag::get_collector_instance().info() << std::endl;
	}
```

Or do nothing if we have an ex-inheritor instance:

```
	catch ( const ex_diag::ex_t & ex )
	{
		// Dump will be at ex_diag::ex_t d'tor.
	}
```

After a while of wide using, the library allows to quickly understand stack traces of failures and makes development easier at all of its stages.