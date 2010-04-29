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

   public:
      static CommonUnitInfo * info;

   public:
      CharSet(QSet<QChar> values_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static CharSet * tryRecognize(QString str, int & pos);

      // Iterative make
      virtual QString makeFirstValue();
      virtual QString makeNextValue();
      virtual bool atEnd();

      virtual QString print();
      virtual quint64 count();
   };
}

#endif // CHARSET_H
