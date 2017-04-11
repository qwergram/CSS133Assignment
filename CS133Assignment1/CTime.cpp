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
	void CTime::setHour(short hour)
	{
		if (hour >= 0 && hour < HOURS_IN_DAY) {
			m_hour = hour;
		}
		else {
			m_hour = 0;
		}
	}

	void CTime::setMinute(short minute)
	{
		if (minute >= 0 && minute < SEXAGESIMAL_RATE) {
			m_minute = minute;
		}
		else {
			m_minute = 0;
		}
	}

	void CTime::setSecond(short second)
	{
		if (second >= 0 && second < SEXAGESIMAL_RATE) {
			m_second = second;
		}
		else {
			m_second = 0;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//			method:		setCurrentTime()
	//
	//    description:	sets the time from the system clock
	//
	//    Called By:	constructor, mutators
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
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
	CTime::CTime(void)
	{
		this->setCurrentTime();
	}

	CTime::CTime(int hour, int minute, int second)
	{
		this->setHour(hour);
		this->setMinute(minute);
		this->setSecond(second);
	}

	void CTime::input(istream & sin)
	{
		bool reset = false;
		short hour, minute, second;
		char c;

		sin >> hour;
		sin.get(c);
		if (c != ':') { reset = true; }

		sin >> minute;
		sin.get(c);
		if (c != ':') { reset = true; }

		sin >> second;

		if (reset) {
			hour = 0;
			minute = 0;
			second = 0;
		}
		else {

			if (hour < 0 || hour >= HOURS_IN_DAY) {
				hour = 0;
			}

			if (minute < 0 || minute >= SEXAGESIMAL_RATE) {
				minute = 0;
			}

			if (second < 0 || second >= SEXAGESIMAL_RATE) {
				second = 0;
			}

		}
		setHour(hour);
		setMinute(minute);
		setSecond(second);
			
	}

	void CTime::print(ostream & sout) const
	{
		sout << m_hour << ':' << m_minute << ':' << m_second;
	}

	bool CTime::operator==(const Comparable & other) const
	{
		bool returnValue = false;
		try
		{
			CTime otherTime = dynamic_cast<const CTime&>(other);
			if (	
				m_hour == otherTime.getHour() &&
				m_minute == otherTime.getMinute() &&
				m_second == otherTime.getSecond()
				)
				returnValue = true;
		}
		catch (bad_cast e)
		{
			// Should something happen here?
		}
		return returnValue;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		operator < (const Comparable& other) const
	//
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//    Called By:	main, >=, <=
	// 
	//    Returns:          true if the two objects are exactly the same;
	//				false otherwise
	//    History Log:
	//			5/8/16  PB  completed version 1.1
	//-----------------------------------------------------------------------------
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

			if (hourIsLT)
				isLT = true;
			else if (hourIsEq && minIsLT)
				isLT = true;
			else if (hourIsEq && minIsEq && secIsLT)
				isLT = true;
		}
		catch (bad_cast e) {
			throw new invalid_argument("CTime can only be compared to CTime objects");
		}

		return isLT;
	}

	ostream & operator << (ostream & sout, const CTime & time)
	{
		time.print(sout);
		return sout;
	}

	istream & operator >> (istream & sin, CTime & time)
	{
		time.input(sin);
		return sin;
	}

}
