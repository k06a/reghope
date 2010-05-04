#ifndef REGULARVECTOR_H
#define REGULARVECTOR_H

#include "IUnit.h"
#include <QObject>
#include <QList>

//----------------------------------------------------------------
// RegularVector = "(" (RegularUnit | RegularVector)+ ")" (RepeatRange)?
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

   public:
      static CommonUnitInfo * info;

   public:
      RegularVector(QList<IUnit<QString>*> unitList_, RepeatRange *repeatRange_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RegularVector * tryRecognize(QString str, int & pos);

      // Iterative make
      QString makeFirstValue();
      QString makeNextValue();
      bool atEnd();
   private:
      QString makeNextValue_();
   public:

      virtual QString print();
      virtual quint64 count();
      virtual void setMaxLength(int length);
   };
}
#endif // REGULARVECTOR_H
