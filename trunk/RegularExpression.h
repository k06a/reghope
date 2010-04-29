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

      static RegularExpression * parse(QString str);

      // Iterative make
      QString makeFirstValue();
      QString makeNextValue();
      bool atEnd();

      virtual QString print();
      virtual quint64 count();
   };
}

#endif // REGULAREXPRESSION_H
