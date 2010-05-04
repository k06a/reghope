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

   public:
      static CommonUnitInfo * info;

   public:
      RepeatRange(int a_, int b_, bool haveMax_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RepeatRange * tryRecognize(QString str, int & pos);

      // Iterative make
      int makeFirstValue();
      int makeNextValue();
      bool atEnd();

      virtual QString print();
      virtual quint64 count();
      virtual void setMaxLength(int length);
   };
}

#endif // REPEATRANGE_H
