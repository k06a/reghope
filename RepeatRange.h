#ifndef REPEATRANGE_H
#define REPEATRANGE_H

#include "IUnit.h"

//----------------------------------------------------------------
// RepeatRange = ("?" | "+" | "*" | ("{" int ("," int?)? "}"))
//----------------------------------------------------------------

namespace RegHope
{
   class CommonUnitInfo;

   class RepeatRange : public IUnit<int>
   {
      int a, b;
      bool haveMax;
      int current;

   public:
      static CommonUnitInfo * info;

   public:
      RepeatRange(int a_, int b_, bool haveMax_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RepeatRange * tryRecognize(QString str, int & pos);

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

#endif // REPEATRANGE_H
