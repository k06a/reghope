#ifndef IUNIT_H
#define IUNIT_H

// Regular Expression Rules:
//
//----------------------------------------------------------------
// CharConst = ( "\\" | "\." | "\-" | "\?" | "\+" | "\*" |
//               "\(" | "\)" | "\[" | "\]" | "\{" | "\}" |
//               "\d{1,3}" | "\xHH" | "\oOOO" | "\bBBBBBBBB" | *)
//----------------------------------------------------------------
// CharRange = ("." | (CharConst "-" CharConst))
//----------------------------------------------------------------
// CharSet   = "[" ("^")? (CharRange | CharConst)+ "]"
//----------------------------------------------------------------
//
//----------------------------------------------------------------
// RepeatRange = ("?" | "+" | "*" | ("{" int ("," int?)? "}"))
//----------------------------------------------------------------
//
//----------------------------------------------------------------
// RegularUnit       = (CharSet | CharConst) (RepeatRange)?
//----------------------------------------------------------------
// RegularVector     = "(" (RegularUnit | RegularVector)+ ")" (RepeatRange)?
//----------------------------------------------------------------
// RegularExpression = (RegularVector | RegularUnit)+
//----------------------------------------------------------------
//

#include "RegException.h"

class QString;

namespace RegHope
{
	template<typename T>
	class IUnit
	{
	public:
		virtual ~IUnit() {}

		// Try to create reg.exp. unit from \str on position \pos.
		// Returns new object or null, and moves \pos after reg.exp.
		static IUnit * tryRecognize(QString str, int & pos);

		// Min and Max bounds
		virtual T getFirstValue() = 0;
		virtual T getLastValue() = 0;
		virtual T getCurrentValue() = 0;

		// Iterative make
		virtual T makeFirstValue() = 0;
		virtual T makeNextValue() = 0;
		virtual bool atEnd() = 0;

      virtual QString print() = 0;
	};

	bool tryReadInt(QString str, int & pos, int & value);
}

#endif // IUNIT_H
