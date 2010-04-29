#ifndef CHARACTER_H
#define CHARACTER_H

#include "IUnit.h"
#include <QString>
#include <QSet>

//----------------------------------------------------------------
// Character = (CharSet | CharRange | CharConst )+
//----------------------------------------------------------------

namespace RegHope
{
   class CharConst;
   class CharRange;
   class CharSet;
   class CommonUnitInfo;

   class CharArray : public IUnit<QString>
   {
      CharSet * set;

   public:
      static CommonUnitInfo * info;

   public:
      CharArray(CharSet * set_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static IUnit<QString> * tryRecognize(QString str, int & pos);

      // Min and Max bounds
      QString getFirstValue();
      QString getLastValue();

      // Iterative make
      QString makeFirstValue();
      QString makeNextValue();
      bool atEnd();
   };
}

#endif // CHARACTER_H
