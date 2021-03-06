//-----------------------------------------------------------------------------
//	File: CTime.cpp
//
//	class: CTime
//	methods:
//		void CTime::setCurrentTime()
//
//
//-----------------------------------------------------------------------------
#include "CTime.h"
namespace NP_DATETIME
{

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		hour mutator
	//
	//    description:	sets hour to valid hour or 0
	// 
	//    Parameters:	short hour
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	void CTime::setHour(short hour)
	{
		if (hour >= 0 && hour < HOURS_IN_DAY) {
			m_hour = hour;
		}
		else {
			m_hour = 0;
		}
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		minute mutator
	//
	//    description:	sets minute to valid minute or 0
	// 
	//    Parameters:	short minute
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	void CTime::setMinute(short minute)
	{
		if (minute >= 0 && minute < SEXAGESIMAL_RATE) {
			m_minute = minute;
		}
		else {
			m_minute = 0;
		}
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		second mutator
	//
	//    description:	sets second to valid second or 0
	// 
	//    Parameters:	short second
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	void CTime::setSecond(short second)
	{
		if (second >= 0 && second < SEXAGESIMAL_RATE) {
			m_second = second;
		}
		else {
			m_second = 0;
		}
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:		setCurrentTime()
	//
	//    description:	sets the time from the system clock
	//
	//    Called By:	constructor, mutators
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		constructor
	//
	//    description:	builds time object from current time
	// 
	//    Parameters:	
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		Mutators of CTime
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	CTime::CTime(void)
	{
		this->setCurrentTime();
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		constructor
	//
	//    description:	builds time object from specified values
	// 
	//    Parameters:	int hour, int minute, int second
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	
	// 
	//	  Calls:		Mutators of CTime
	//
	//    Returns:      
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	CTime::CTime(int hour, int minute, int second)
	{
		this->setHour(hour);
		this->setMinute(minute);
		this->setSecond(second);
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		input(istream & sin)
	//
	//    description:	reads HH:MM:SS from istream and sets values in CTime object
	// 
	//    Parameters:	istream & sin  -- the istream to read from
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	istream & operator >>
	// 
	//	  Calls:		Mutators of CTime
	//
	//    Returns:      void
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	void CTime::input(istream & sin)
	{
		// Assume best scenario: we don't have reset everything to 0.
		bool proceed = false;

		// Store our hour, minute and second as a short.
		short hour = 0, minute = 0, second = 0;

		// this is the character we'll read to.
		char c;

		// Format is number:number:number, so let's read in the first
		// hour to hour. It will automatically stop once it finds a non
		// integer. 
		sin >> hour;

		// Grab the next character, it should be a ':'
		c = sin.peek();
		// But if it's not a ':', set the reset flag to true
		if (c == ':') { proceed = true; sin.get(); }

		// Do the same thing for minute
		if (proceed) {
			proceed = false;
			sin >> minute;
			c = sin.peek();
			if (c == ':') { proceed = true; sin.get(); }
		}
		

		// Lastly, grab the second
		if (proceed)
			sin >> second;

		// If a reset was called (e.g. user typed something wrong)
		// set everything to 0
		/*if (proceed) {
			hour = 0;
			minute = 0;
			second = 0;
		}*/
		//else {
		// Now make sure the user typed in something valid
		if (hour < 0 || hour >= HOURS_IN_DAY)
			hour = 0;
		if (minute < 0 || minute >= SEXAGESIMAL_RATE)
			minute = 0;
		if (second < 0 || second >= SEXAGESIMAL_RATE)
			second = 0;
		//}
		// the values with the mutators
		setHour(hour);
		setMinute(minute);
		setSecond(second);

	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		print(ostream & sout) const
	//
	//    description:	prints text in HH:MM:SS to specified ostream
	// 
	//    Parameters:	ostream & sout  -- the ostream to print to
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	ostream & operator <<
	// 
	//	  Calls:		Accesors of CTime
	//
	//    Returns:      void
	//					
	//
	//    Exceptions:   
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	void CTime::print(ostream & sout) const
	{
		const int DOUBLE_DIGIT_THRESHOLD = 10;
		string min = "";
		string sec = "";
		string hour = "";

		if (getMinute() < DOUBLE_DIGIT_THRESHOLD)
			min = "0";
		if (getSecond() < DOUBLE_DIGIT_THRESHOLD)
			sec = "0";
		if (getHour() < DOUBLE_DIGIT_THRESHOLD)
			hour = "0";
		
		sout << hour << getHour() << ':' << min << getMinute() 
			 << ':' << sec << getSecond();
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		operator==(const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	main, >=, <=
	//
	//	  Calls:		Accesors of CTime
	// 
	//    Returns:      true if the two objects are exactly the same;
	//					false otherwise
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	bool CTime::operator==(const Comparable & other) const
	{
		bool returnValue = false;
		try
		{
			CTime otherTime = dynamic_cast<const CTime&>(other);
			returnValue = (
				m_hour == otherTime.getHour() &&
				m_minute == otherTime.getMinute() &&
				m_second == otherTime.getSecond()
				);
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		operator < (const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other CTime to compare
	//
	//	  Programmers:  Norton Pengra && Paul Bladek
	//
	//    Called By:	main, >=, <=
	// 
	//	  Calls:		Accesors of CTime
	//
	//    Returns:      true if the the current object is less than the other.
	//					false otherwise
	//
	//    Exceptions:   Throws invalid_argument if other isn't CTime object
	//
	//    History Log:
	//			05/08/16  PB  completed version 1.1
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	bool CTime::operator<(const Comparable & other) const
	{
		bool isLT = false;

		try {
			CTime otherTime = dynamic_cast<const CTime&>(other);

			bool hourIsLT = m_hour < otherTime.getHour();
			bool hourIsEq = m_hour == otherTime.getHour();
			bool minIsLT = m_minute < otherTime.getMinute();
			bool minIsEq = m_minute == otherTime.getMinute();
			bool secIsLT = m_second < otherTime.getSecond();

			isLT = (hourIsLT || hourIsEq && minIsLT || hourIsEq && minIsEq && secIsLT);
		}
		catch (bad_cast e) {
			throw invalid_argument("CTime can only be compared to CTime objects");
		}

		return isLT;
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		ostream & operator << (ostream & sout, const CTime & time)
	//
	//    description:	print the time to the specified ostream
	// 
	//    Parameters:	ostream & sout -- ostream you'd like to use
	//					const CTime & time -- time object to print
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		CTime::print()
	// 
	//    Returns:      the ostream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	ostream & operator << (ostream & sout, const CTime & time)
	{
		time.print(sout);
		return sout;
	}

 //-------------------------------------------------------------------------
	//    Class:		CTime
	//    method:		ostream & operator >> (istream & sin, CTime & time)
	//
	//    description:	read from the specified input stream and write to time obj
	// 
	//    Parameters:	istream & sin -- istream you'd like to read from
	//					CTime & time -- time object you'd like to write to
	//
	//	  Programmers:  Norton Pengra
	//
	//    Called By:	main
	//
	//	  Calls:		CTime::input
	// 
	//    Returns:      the istream reference initially passed in
	//
	//    History Log:
	//			04/11/17  NP  appended to version 1.1
 //-------------------------------------------------------------------------
	istream & operator >> (istream & sin, CTime & time)
	{
		time.input(sin);
		return sin;
	}

}
