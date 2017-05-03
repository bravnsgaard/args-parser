
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2013-2017 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// UnitTest include.
#include <UnitTest/unit_test.hpp>

// Args include.
#include <Args/all.hpp>


using namespace Args;


TEST( ArgTestCase, TestAllIsOk )
{
	const int argc = 7;
	const char * argv[ argc ] = { "program.exe",
		"-t", "100",
		"--port", "4545",
		"--host", "any" };

	CmdLine cmd( argc, argv );

	Arg timeout( 't', String( "timeout" ), true );
	Arg port( 'p', String( "port" ), true );
	Arg host( 'h', String( "host" ), true );

	cmd.addArg( &timeout );
	cmd.addArg( &port );
	cmd.addArg( &host );

	cmd.parse();

	CHECK_CONDITION( timeout.isDefined() == true )
	CHECK_CONDITION( timeout.value() == "100" )

	CHECK_CONDITION( port.isDefined() == true )
	CHECK_CONDITION( port.value() == "4545" )

	CHECK_CONDITION( host.isDefined() == true )
	CHECK_CONDITION( host.value() == "any" )
}

TEST( ArgTestCase, TestUndefinedArg )
{
	const int argc = 7;
	const char * argv[ argc ] = { "program.exe",
		"-t", "100",
		"--port", "4545",
		"--host", "any" };

	CmdLine cmd( argc, argv );

	Arg timeout( 't', String( "timeout" ), true );
	Arg host( String( "host" ), true );

	cmd.addArg( &timeout );
	cmd.addArg( &host );

	try {
		cmd.parse();
	}
	catch( const BaseException & x )
	{
#ifdef ARGS_QSTRING_BUILD
		CHECK_CONDITION(
			x.whatAsQString() == String( "Unknown argument \"--port\"." ) )
#else
		CHECK_CONDITION(
			x.what() == String( "Unknown argument \"--port\"." ) )
#endif

		return;
	}

	CHECK_CONDITION( false )
}

TEST( ArgTestCase, TestUndefinedRequiredArg )
{
	const int argc = 5;
	const char * argv[ argc ] = { "program.exe",
		"-t", "100",
		"--host", "any" };

	CmdLine cmd( argc, argv );

	Arg timeout( 't', String( "timeout" ), true );
	Arg port( 'p', String( "port" ), true, true );
	Arg host( 'h', String( "host" ), true );

	cmd.addArg( &timeout );
	cmd.addArg( &port );
	cmd.addArg( &host );

	try {
		cmd.parse();
	}
	catch( const BaseException & x )
	{
#ifdef ARGS_QSTRING_BUILD
		CHECK_CONDITION(
			x.whatAsQString() ==
				String( "Undefined required argument \"--port\"." ) )
#else
		CHECK_CONDITION(
			x.what() == String( "Undefined required argument \"--port\"." ) )
#endif

		return;
	}

	CHECK_CONDITION( false )
}


int main()
{
	RUN_ALL_TESTS()

	return 0;
}
