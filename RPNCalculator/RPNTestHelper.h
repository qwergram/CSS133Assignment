//----------------------------------------------------------------------
// file: RPNTestHelper.h
//----------------------------------------------------------------------
#ifndef RPNTESTHELP_H
#define RPNTESTHELP_H
#include <string>
#include <sstream>
#include <iostream> 
#include "RPNCalc.h"

//-----------------------------------------------------------------------------
// Title: RPNTestHelper
// Description: A helper class for running tests on RPNCalc class.
// Programmer: Tabitha Roemish, Cecilia Tong, Norton Pengra, Antonio Castelli -
//		see github link for individual contributions
//		
// Date: June 2017
// Version: 1.10
// Environment: 
//      Intel i7
//		Software: MS Windows 10 for execution;
//		Compiles under Microsoft Visual C++.Net 2015
// Classes:
//		class RPNTestHelper:
//			 
//			Public Methods Inline:
//				bool expectedOutput(string input, string output) -
//					takes string input and output and returns true if 
//					output of last command matches calculator output
//				string getStackOutput(string input)
//					returns string containing the output of the item
//					on the top of the RPNCalc stack.
//				bool expectedStackOutput(string input, string output)				
//					returns true if the first item of the stack is
//					equal to the output plan parameter. check is done
//					after input operation is completed.
//				string getOutput(string input)
//					returns the string representation of the first
//					item on the stack. Operation occurs after the
//					input operation.
//				bool expectError(string input)
//					return true if the input parameter returns
//					"<<error>>" and false otherwise.
//			Private:
//				CRPNCalc calc;
//				
// History Log:
//		https://github.com/qwergram/CS133Assignment/pull/7
//--------------------------------------------------------------------
namespace P4_RPNCALC
{
	class RPNTestHelper
	{
	public:
		RPNTestHelper() : calc(false) {  };
		bool expectedOutput(string input, string output) {
			return getOutput(input) == output;
		}

		string getStackOutput(string input);

		bool expectedStackOutput(string input, string output) {
			return getStackOutput(input) == output;
		}

		string getOutput(string input);

		bool expectError(string input) {
			return expectedOutput(input, "<<error>>");
		}

	private:
		CRPNCalc calc;
	};
}
#endif
