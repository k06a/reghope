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
   protected:
      T firstValue;
      T currentValue;
      T lastValue;

	public:
		virtual ~IUnit() {}

		// Try to create reg.exp. unit from \str on position \pos.
		// Returns new object or null, and moves \pos after reg.exp.
		static IUnit * tryRecognize(QString str, int & pos);

		// Min and Max bounds
      T getFirstValue()
      {
         return firstValue;
      }

      T getCurrentValue()
      {
         return currentValue;
      }

      T getLastValue()
      {
         return lastValue;
      }

		// Iterative make
		virtual T makeFirstValue() = 0;
		virtual T makeNextValue() = 0;
		virtual bool atEnd() = 0;

      virtual QString print() = 0;
      virtual quint64 count() = 0;
	};
}

#endif // IUNIT_H
