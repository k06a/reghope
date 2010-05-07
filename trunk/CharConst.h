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

      // Iterative make
      virtual QString makeFirstValue();
      virtual QString makeNextValue();
      virtual bool atEnd();
      virtual QString getRandValue();

      virtual QString print();
      virtual quint64 count();
   };
}

#endif // CHARCONST_H
