#ifndef REGULARVECTOR_H
#define REGULARVECTOR_H

#include "IUnit.h"
#include <QObject>
#include <QList>

//----------------------------------------------------------------
// GroupUnit = "(" (RegularUnit | GroupUnit)+ ")" (RepeatRange)?
//----------------------------------------------------------------

namespace RegHope
{
   class GroupUnit;
   class RepeatRange;
   class RegularUnit;
   class CommonUnitInfo;

   class RegularVector : public IUnit<QString>
   {
      QList<IUnit<QString>*> unitList;
      RepeatRange *repeatRange;
      QString currentValue;

   public:
      static CommonUnitInfo * info;

   public:
      RegularVector(QList<IUnit<QString>*> unitList_, RepeatRange *repeatRange_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RegularVector * tryRecognize(QString str, int & pos);

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
#endif // REGULARVECTOR_H
