#ifndef REGULARUNIT_H
#define REGULARUNIT_H

#include "IUnit.h"

//----------------------------------------------------------------
// RegularUnit = (CharSet | CharConst) (RepeatRange)?
//----------------------------------------------------------------

namespace RegHope
{
   class CharUnit;
   class RepeatRange;
   class CommonUnitInfo;

   class RegularUnit : public IUnit<QString>
   {
      IUnit<QString> * charUnit;
      RepeatRange * repeatRange;
      QString current;

   public:
      static CommonUnitInfo * info;

   public:
      RegularUnit(IUnit<QString> *charUnit_, RepeatRange *repeatRange_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RegularUnit * tryRecognize(QString str, int & pos);

      // Min and Max bounds
      QString getFirstValue();
      QString getLastValue();
      QString getCurrentValue();

      // Iterative make
      QString makeFirstValue();
      QString makeNextValue();
      bool atEnd();

      virtual QString print();
   };
}

#endif // REGULARUNIT_H
