#ifndef CHARSET_H
#define CHARSET_H

#include "IUnit.h"
#include <QSet>

//----------------------------------------------------------------
// CharSet = "[" ("^")? (CharConst | CharRange)+ "]"
//----------------------------------------------------------------

namespace RegHope
{
   class CharConst;
   class CharRange;
   class CommonUnitInfo;

   class CharSet : public IUnit<QString>
   {
      QList<QChar> values;
      int currentIndex;
      QString currentValue;

   public:
      static CommonUnitInfo * info;

   public:
      CharSet(QSet<QChar> values_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static CharSet * tryRecognize(QString str, int & pos);

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

#endif // CHARSET_H
