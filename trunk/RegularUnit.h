#ifndef REGULARUNIT_H
#define REGULARUNIT_H

#include "IUnit.h"

//----------------------------------------------------------------
// RegularUnit = (CharSet | CharConst) (RepeatRange)?
//----------------------------------------------------------------

namespace RegHope
{
   class CharUnit;
   class RepeatRange;
   class CommonUnitInfo;

   class RegularUnit : public IUnit<QString>
   {
      IUnit<QString> * charUnit;
      RepeatRange * repeatRange;

   public:
      static CommonUnitInfo * info;

   public:
      RegularUnit(IUnit<QString> *charUnit_, RepeatRange *repeatRange_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static RegularUnit * tryRecognize(QString str, int & pos);

      // Iterative make
      virtual QString makeFirstValue();
      virtual QString makeNextValue();
      virtual bool atEnd();
   private:
      QString makeNextValue_();
   public:
      virtual QString getRandValue();

      virtual QString print();
      virtual quint64 count();
      virtual void setMaxLength(int length);
   };
}

#endif // REGULARUNIT_H
