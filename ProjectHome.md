# Introduction #

This library allows to use simple cpp-constructions for diagnostic different exception crashes in the future.

It's only C++ tool.

# Details #

Whereas an application works fine these wrappers are not active. However, if the application or sublibrary throws an exception, and the application catches it, the library tools allow to get all diagnostic information about objects which had been destroyed.

Like stack trace it's an instance trace of the failure.

The library provides some special easy-using tools of the functionality.

Look at the [Quick General Description](QuickGeneralDescription.md). This page shows general features quickly and graphically.

The next guide page [Example Of Advantages](ExampleOfAdvantages.md) can help you understand usefulness of the library quickly and completely.

Besides, samples are present (see [subversion trunk/tags](http://code.google.com/p/exception-diagnostic/source/browse/)).

Also Doxygen [documentation](http://exception-diagnostic.googlecode.com/svn/tags/1.0.2/html/index.html) is available.

## Compile ##

The library has been compiled and built on different operating systems.

It has been tested with Microsoft Visual C++ 7.0/9.0 and GCC 4.1.2 compilers.

## Features ##

All types of instances can be wrapped and diagnosed by this library.

The diagnostic result can be sent to any std::ostream instance.

Cross-compile.

Minimal syntax and run-time resource using.