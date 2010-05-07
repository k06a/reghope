#ifndef CHARRANGE_H
#define CHARRANGE_H

#include "IUnit.h"

//----------------------------------------------------------------
// CharRange = ("." | (CharConst "-" CharConst))
//----------------------------------------------------------------

namespace RegHope
{
	class CharConst;
	class CommonUnitInfo;

	class CharRange : public IUnit<QString>
	{
		CharConst * value_1;
		CharConst * value_2;

	public:
		static CommonUnitInfo * info;

	public:
		CharRange(CharConst * value_1_, CharConst * value_2_);

		// Try to create reg.exp. unit from \str on position \pos.
		// Returns new object or null, and moves \pos after reg.exp.
      static CharRange * tryRecognize(QString str, int & pos);

		// Iterative make
      virtual QString makeFirstValue();
      virtual QString makeNextValue();
      virtual bool atEnd();
      virtual QString getRandValue();

      virtual QString print();
      virtual quint64 count();
	};
}

#endif // CHARRANGE_H
