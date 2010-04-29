#ifndef REPEATUNIT_H
#define REPEATUNIT_H

#include "IUnit.h"

//----------------------------------------------------------------
// RepeatUnit  = ("?" | "+" | "*" | RepeatConst | RepeatRange)
//----------------------------------------------------------------

namespace RegHope
{
   class CommonUnitInfo;

   class RepeatUnit : public IUnit<int>
   {
      int a, b;
      bool haveMax;
      int current;

   public:
      static CommonUnitInfo * info;

   public:
      RepeatUnit(int a_, int b_, bool haveMax_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static IUnit<int> * tryRecognize(QString str, int & pos);

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

#endif // REPEATUNIT_H
