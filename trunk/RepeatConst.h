#ifndef REPEATCONST_H
#define REPEATCONST_H

#include "IUnit.h"

//----------------------------------------------------------------
// RepeatConst = "{" int "}"
//----------------------------------------------------------------

namespace RegHope
{
   class CommonUnitInfo;

   class RepeatConst : public IUnit<int>
   {
      int value;

   public:
      static CommonUnitInfo * info;

   public:
      RepeatConst(int value_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RepeatConst * tryRecognize(QString str, int & pos);

      // Min and Max bounds
      int getFirstValue();
      int getLastValue();
      int getCurrentValue();

      // Iterative make
      int makeFirstValue();
      int makeNextValue();
      bool atEnd();

      virtual QString print();
   };
}

#endif // REPEATCONST_H
