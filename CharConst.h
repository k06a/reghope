#ifndef CHARCONST_H
#define CHARCONST_H

#include "IUnit.h"

//----------------------------------------------------------------
// CharConst = ( "\\" | "\." | "\-" | "\?" | "\+" | "\*" |
//               "\(" | "\)" | "\[" | "\]" | "\{" | "\}" |
//               "\d{1,3}" | "\xHH" | "\oOOO" | "\bBBBBBBBB" | *)
//----------------------------------------------------------------

namespace RegHope
{
   class CommonUnitInfo;

   class CharConst : public IUnit<QString>
   {
      QChar value;

   public:
      static CommonUnitInfo * info;

   public:
      CharConst(QChar value_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static CharConst * tryRecognize(QString str, int & pos);

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

#endif // CHARCONST_H
