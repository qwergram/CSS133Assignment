//--------------------------------------------------
//  file: RPN_UnitTests.cpp
//-------------------------------------------------

#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "RPNCalc.h"
#include "RPNTestHelper.h"

using namespace P4_RPNCALC;

TEST_CASE("Operation Methods")
{
	RPNTestHelper test;

	// Assert the last thing pushed is the last thing on the stack
	SECTION("Sanity Tests") {
		for (int n = 0; n < 100; n++) {
			REQUIRE(test.expectedStackOutput(to_string(n), to_string(n)));
		}
	}

	// assert clearing works, no matter what is punched in
	SECTION("Method: clearAll()")
	{
		REQUIRE(test.expectedStackOutput("50", "50"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("50", "50"));
		REQUIRE(test.expectedOutput("C", ""));
		REQUIRE(test.expectedStackOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("C", ""));
		REQUIRE(test.expectedStackOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedOutput("C", ""));
	}

	// assert entry clearing works, no matter what is punched in
	SECTION("Method: clearEntry()")
	{
		REQUIRE(test.expectedStackOutput("50", "50"));
		REQUIRE(test.expectedOutput("ce", ""));
		REQUIRE(test.expectedStackOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("ce", ""));
		REQUIRE(test.expectedStackOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedStackOutput("ce", "150"));
		REQUIRE(test.expectedOutput("ce", ""));

		REQUIRE(test.expectedStackOutput("50", "50"));
		REQUIRE(test.expectedOutput("CE", ""));
		REQUIRE(test.expectedStackOutput("50 100 +", "150"));
		REQUIRE(test.expectedOutput("CE", ""));
		REQUIRE(test.expectedStackOutput("50 100 + 200", "200"));
		REQUIRE(test.expectedStackOutput("CE", "150"));
		REQUIRE(test.expectedOutput("CE", ""));
	}

	// assert addition works w/ or without spaces
	SECTION("Method: add()")
	{
		REQUIRE(test.expectedStackOutput("3 5+", "8"));
		REQUIRE(test.expectedStackOutput("2 4 3 +", "7"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("3 4 + 6", "6"));
		REQUIRE(test.expectedStackOutput("4 +", "10"));
		REQUIRE(test.expectedStackOutput("-12 +", "-2"));
		REQUIRE(test.expectedStackOutput("5 +", "3"));
		REQUIRE(test.expectedStackOutput("3 +", "6"));
		REQUIRE(test.getStackOutput("10 100 +") == "110");
		REQUIRE(test.getStackOutput("10 100+") == "110");
	}

	// assert subtraction/addition combinations works w/ or without spaces
	SECTION("Method: combinations of add() & subtract()")
	{
		REQUIRE(test.getStackOutput("4.4 5.5 + 60 -") == "-50.1");
		REQUIRE(test.expectedStackOutput("4.4 5.5 - 60 +", "58.9"));
		REQUIRE(test.expectedStackOutput("40 50 + 60 -", "30"));
		REQUIRE(test.expectedStackOutput("40 50 - 60 +", "50"));
		REQUIRE(test.expectedStackOutput("40 50 60 + -", "-70"));
		REQUIRE(test.expectedStackOutput("40 50 60 - +", "30"));
		REQUIRE(test.expectedStackOutput("-40 -50 + 60 -", "-150"));
		REQUIRE(test.expectedStackOutput("-40 -50 + -60 -", "-30"));
		REQUIRE(test.expectedStackOutput("-40 -50 - 60 +", "70"));
		REQUIRE(test.expectedStackOutput("-40 -50 - -60 +", "-50"));
	}

	// assert subtaction works w/ or without spaces
	// and ensure it doesn't conflict with negative numbers
	SECTION("Method: subtract()")
	{
		REQUIRE(test.expectedStackOutput("5 6 -", "-1"));
		REQUIRE(test.expectedStackOutput("3 9 4 -", "5"));
		REQUIRE(test.expectedStackOutput("-", "-2"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("-1 5 -", "-6"));
		REQUIRE(test.expectedStackOutput("10 100 -", "-90"));
		REQUIRE(test.expectedStackOutput("10 100-", "-90"));
		REQUIRE(test.expectedStackOutput("-", "0"));
	}

	// assert multiplication works w/ or without spaces
	// espeicially with negative numbers
	SECTION("Method: multiply()")
	{
		REQUIRE(test.expectedStackOutput("3 9 7 2 4 *", "8"));
		REQUIRE(test.expectedStackOutput("*", "56"));
		REQUIRE(test.expectedStackOutput("*", "504"));
		REQUIRE(test.expectedStackOutput("*", "1512"));
		REQUIRE(test.expectError("*"));
		REQUIRE(test.getOutput("c") == "");
		REQUIRE(test.expectedStackOutput("-4 -6 *", "24"));
		REQUIRE(test.expectedStackOutput("-2 *", "-48"));
		REQUIRE(test.expectedStackOutput("10 100 *", "1000"));
		REQUIRE(test.expectedStackOutput("10 100*", "1000"));
		REQUIRE(test.expectedStackOutput("5.5 2.2*", "12.1"));
	}

	// assert division works w/ or without spaces
	// espeicially with negative numbers
	SECTION("Method: divide()")
	{
		REQUIRE(test.expectedStackOutput("16 4 2 /", "2"));
		REQUIRE(test.expectedStackOutput("/", "8"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("2 5 /", "0.4"));
		REQUIRE(test.expectedStackOutput("9 3 7 /", "0.428571"));
		REQUIRE(test.expectedStackOutput("-1 /", "-0.428571"));
		REQUIRE(test.expectedStackOutput("-1 / ", "0.428571"));
		REQUIRE(test.expectedStackOutput("100 10 /", "10"));
		REQUIRE(test.expectedStackOutput("100 10/", "10"));
		REQUIRE(test.expectedStackOutput("/", "1"));
		REQUIRE(test.expectedStackOutput("/", "0.428571"));
		REQUIRE(test.expectedStackOutput("/", "21"));
		REQUIRE(test.expectedStackOutput("/", "0.0190476"));
		REQUIRE(test.expectedStackOutput("/", "0.0190476"));
		REQUIRE(test.expectError("/"));
	}

	// assert modulo operations works w/ or without spaces
	SECTION("Method: mod()")
	{
		REQUIRE(test.expectedStackOutput("16 8 6 %", "2"));
		REQUIRE(test.expectedStackOutput("%", "0"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectError("%"));
		REQUIRE(test.expectedStackOutput("10 1 %", "0"));
		REQUIRE(test.expectedStackOutput("10 2 %", "0"));
		REQUIRE(test.expectedStackOutput("10 3 %", "1"));
		REQUIRE(test.expectedStackOutput("10 4 %", "2"));
		REQUIRE(test.expectedStackOutput("10 5 %", "0"));
		REQUIRE(test.expectedStackOutput("10 6 %", "4"));
		REQUIRE(test.expectedStackOutput("10 7 %", "3"));
		REQUIRE(test.expectedStackOutput("10 8 %", "2"));
		REQUIRE(test.expectedStackOutput("10 9 %", "1"));
		REQUIRE(test.expectedStackOutput("10 10 %", "0"));
		REQUIRE(test.expectedStackOutput("100 70 %", "30"));
		REQUIRE(test.expectedStackOutput("100 70%", "30"));
	}

	// assert exponents operations works w/ or without spaces
	// including with negative numbers as the exponent or base
	SECTION("Method: exp()")
	{
		REQUIRE(test.expectedStackOutput("10 2 ^", "100"));
		REQUIRE(test.expectedStackOutput("10 2 2 ^", "4"));
		REQUIRE(test.expectedStackOutput("^", "10000"));
		REQUIRE(test.expectedStackOutput("-10 2 ^", "100"));
		REQUIRE(test.expectedStackOutput("-10 3 ^", "-1000"));
		REQUIRE(test.expectedStackOutput("-10 3^", "-1000"));
		REQUIRE(test.expectedStackOutput("0^", "1"));
		REQUIRE(test.expectedStackOutput("^", "-1000"));
		REQUIRE(test.expectedStackOutput("^", "0"));
		REQUIRE(test.expectedStackOutput("^", "1"));
		REQUIRE(test.expectedStackOutput("^", "100"));
		REQUIRE(test.expectError("^"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectError("^"));
		REQUIRE(test.expectedStackOutput("10 -1 ^", "0.1"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectedStackOutput("100 100^", "1e+200"));
	}

	// assert negations operations works w/ or without spaces
	SECTION("Method: neg()")
	{
		REQUIRE(test.expectedStackOutput("-1000", "-1000"));
		REQUIRE(test.expectedStackOutput("M", "1000"));
		REQUIRE(test.getStackOutput("-1000 -1*") == "1000");
		REQUIRE(test.expectedStackOutput("M", "-1000"));
		REQUIRE(test.expectedStackOutput("-4/", "250"));
		REQUIRE(test.expectedStackOutput("m", "-250"));
		REQUIRE(test.expectedStackOutput("-2*", "500"));
		REQUIRE(test.expectedStackOutput("m", "-500"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectError("m"));
		REQUIRE(test.expectError("M"));
	}

	// assert rotations work
	SECTION("Method: rotateDown()")
	{
		REQUIRE(test.expectedStackOutput("100 200", "200"));
		REQUIRE(test.expectedStackOutput("D", "100"));
		REQUIRE(test.expectedStackOutput("D", "200"));
		REQUIRE(test.expectedStackOutput("d", "100"));
		REQUIRE(test.expectedStackOutput("d", "200"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectError("D"));
		REQUIRE(test.expectError("d"));
	}

	// assert rotations work
	SECTION("Method: rotateUp()")
	{
		REQUIRE(test.expectedStackOutput("300 500", "500"));
		REQUIRE(test.expectedStackOutput("U", "300"));
		REQUIRE(test.expectedStackOutput("U", "500"));
		REQUIRE(test.expectedStackOutput("u", "300"));
		REQUIRE(test.expectedStackOutput("u", "500"));
		REQUIRE(test.expectedOutput("c", ""));
		REQUIRE(test.expectError("U"));
		REQUIRE(test.expectError("u"));
	}

	// Without time to write dependency injection, the following tests
	// have been conducted manually. See following link:
	// https://github.com/qwergram/CS133Assignment/blob/Tabitha/Notes/project4.md#testing

	/*
	SECTION("Methods: saveToFile(), loadProgram(), recordProgram(), runProgram()")
	{
	REQUIRE(test.expectedInputOutput("R", "<<error>>"));
	REQUIRE(test.expectedInputOutput("F", "<<error>>"));
	REQUIRE(test.expectedInputOutput("p", "0>"));
	REQUIRE(test.expectedInputOutput("5 10 +", "1>"));
	REQUIRE(test.expectedInputOutput("20 30 -", "2>"));
	//REQUIRE(test.expectedInputOutput("P", ""));
	//REQUIRE(test.expectedInputOutput("f", "Enter a filename:"));
	REQUIRE(test.expectedInputOutput("test1", ""));
	//REQUIRE(test.expectedInputOutput("l", "Enter a filename:"));
	REQUIRE(test.expectedInputOutput("test", "error"));
	//REQUIRE(test.expectedInputOutput("L", "Enter a filename:"));
	REQUIRE(test.expectedInputOutput("test1", ""));
	REQUIRE(test.expectedInputOutput("r", "-10"));
	REQUIRE(test.expectedInputOutput("c", ""));
	}

	SECTION("Methods: getReg(), setReg()")
	{
	REQUIRE(test.expectedInputOutput("s0", "<<error>>"));
	REQUIRE(test.expectedInputOutput("S1", "<<error>>"));
	REQUIRE(test.expectedInputOutput("s5", "<<error>>"));
	REQUIRE(test.expectedInputOutput("G0", "0"));
	REQUIRE(test.expectedInputOutput("g1", "0"));
	REQUIRE(test.expectedInputOutput("G5", "0"));
	REQUIRE(test.expectedInputOutput("1000", "1000"));
	REQUIRE(test.expectedInputOutput("s5", "1000"));
	REQUIRE(test.expectedInputOutput("2.5", "2.5"));
	REQUIRE(test.expectedInputOutput("S0", "2.5"));
	REQUIRE(test.expectedInputOutput("G5", "1000"));
	REQUIRE(test.expectedInputOutput("g0", "2.5"));
	}
	// */
}
