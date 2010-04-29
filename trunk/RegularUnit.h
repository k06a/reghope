#ifndef REGULARUNIT_H
#define REGULARUNIT_H

#include "IUnit.h"

//----------------------------------------------------------------
// RegularUnit       = CharUnit (RepeatUnit)?
//----------------------------------------------------------------

namespace RegHope
{
   class CharUnit;
   class RepeatUnit;
   class CommonUnitInfo;

   class RegularUnit : public IUnit<QString>
   {
      CharUnit * charUnit;
      RepeatUnit * repeatUnit;
      QString current;

   public:
      static CommonUnitInfo * info;

   public:
      RegularUnit(CharUnit *charUnit_, RepeatUnit *repeatUnit_);

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
