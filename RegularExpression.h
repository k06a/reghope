#ifndef REGULAREXPRESSION_H
#define REGULAREXPRESSION_H

#include "IUnit.h"
#include <QObject>
#include <QList>

//----------------------------------------------------------------
// RegularExpression = (GroupUnit | RegularUnit)+
//----------------------------------------------------------------

namespace RegHope
{
   class GroupUnit;
   class RegularUnit;
   class CommonUnitInfo;

   class RegularExpression : public IUnit<QString>
   {
      QList<IUnit<QString>*> unitList;

   public:
      static CommonUnitInfo * info;

   public:
      RegularExpression(QList<IUnit<QString>*> unitList_);

      // Try to create reg.exp. unit from \str on position \pos.
      // Returns new object or null, and moves \pos after reg.exp.
      static IUnit<QString> * tryRecognize(QString str, int & pos);

      static RegularExpression * parse(QString str, int maximumLength);

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

#endif // REGULAREXPRESSION_H
