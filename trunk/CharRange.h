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
      unsigned char a;
      unsigned char b;
      int currentIndex;

   public:
      static CommonUnitInfo * info;

   public:
      CharRange(CharConst * a_, CharConst * b_);

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
