# Introduction #

The library allows to use simple cpp-constructions to diagnose different exception crashes in the future.

It's only C++ tool.

# Details #

Whereas application works fine these wrappers are not active. However, if application or sublibrary throws an exception, and the application catches it, library tools allow to get all diagnostic information about objects which had been destroyed.

It's like stack trace, but it's the instance trace of the failure.

The library provides some special easy-using tools of described funtionality.

Look at the [Quick General Description](QuickGeneralDescription.md). This page shows general features quickly and graphically.

The next guide page [Example Of Advantages](ExampleOfAdvantages.md) can help you to understand quickly and completely the library usefulness.

Besides, samples are presented (see [subversion trunk/tags](http://code.google.com/p/exception-diagnostic/source/browse/)).

Also Doxygen [documentation](http://exception-diagnostic.googlecode.com/svn/tags/1.0.2/html/index.html) is available.

## Compile ##

The library has been compiled and built on different operating systems.

It has been tested with Microsoft Visual C++ 7/9/11/12 and GCC 4.1.2/4.7.0 compilers.

## Features ##

All types of instances can be wrapped and diagnosed with this library.

A diagnostic result can be sent to any std::ostream instance.

Cross-compile.

Minimal syntax and run-time resource using.