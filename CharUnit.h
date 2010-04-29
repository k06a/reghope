#ifndef CHARUNIT_H
#define CHARUNIT_H

#include "IUnit.h"

//----------------------------------------------------------------
// CharUnit  = (CharSet | CharConst)
//----------------------------------------------------------------

namespace RegHope
{
   class CharConst;
   class CharSet;
   class CommonUnitInfo;

   class CharUnit : public IUnit<QString>
   {
      IUnit<QString> * unit;

   public:
      static CommonUnitInfo * info;

   public:
      CharUnit(IUnit<QString> * unit_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static IUnit<QString> * tryRecognize(QString str, int & pos);

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

#endif // CHARUNIT_H
