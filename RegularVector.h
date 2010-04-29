#ifndef REGULARVECTOR_H
#define REGULARVECTOR_H

#include "IUnit.h"
#include <QObject>
#include <QList>

//----------------------------------------------------------------
// GroupUnit = "(" (RegularUnit | GroupUnit)+ ")" (RepeatUnit)?
//----------------------------------------------------------------

namespace RegHope
{
   class GroupUnit;
   class RepeatUnit;
   class RegularUnit;
   class CommonUnitInfo;

   class RegularVector : public IUnit<QString>
   {
      QList<IUnit<QString>*> unitList;
      RepeatUnit *repeatUnit;
      QString currentValue;

   public:
      static CommonUnitInfo * info;

   public:
      RegularVector(QList<IUnit<QString>*> unitList_, RepeatUnit *repeatUnit_);

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
