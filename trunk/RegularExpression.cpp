#include "RegularExpression.h"
#include "RegularVector.h"
#include "RegularUnit.h"
#include "CommonUnitInfo.h"
#include <QDebug>

using namespace RegHope;

CommonUnitInfo * RegularExpression::info = NULL;

//----------------------------------------------------------------

RegularExpression::RegularExpression(QList<IUnit<QString> *> unitList_)
{
   unitList = unitList_;

   firstValue = makeFirstValue();

   foreach(IUnit<QString> *unit, unitList)
      lastValue += unit->getLastValue();
   
   minLength = 0;
   foreach(IUnit<QString> *unit, unitList)
      minLength += unit->getMinLength();

   maxLength = 1000000;
}

//----------------------------------------------------------------

// RegularExpression = (GroupUnit | RegularUnit)+

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
IUnit<QString> * RegularExpression::tryRecognize(QString str, int & pos)
{
   QList<IUnit<QString>*> list;

   while (pos < str.size())
   {
      IUnit<QString> * unit = RegularVector::tryRecognize(str, pos);
      if (unit == NULL)
         unit = RegularUnit::tryRecognize(str, pos);

      if (unit == NULL) break;

      list.append(unit);
   }

   if (list.size() == 0)
      return NULL;

   return new RegularExpression(list);
}

RegularExpression * RegularExpression::parse(QString str, int maximumLength)
{
   int pos = 0;

   RegularExpression *expr = (RegularExpression*)tryRecognize(str, pos);
   expr->setMaxLength(maximumLength);

   return expr;
}

//----------------------------------------------------------------
// Iterative make

QString RegularExpression::makeFirstValue()
{
   currentValue = "";

   foreach(IUnit<QString>* unit, unitList)
      currentValue += unit->makeFirstValue();

   return currentValue;
}

QString RegularExpression::makeNextValue_()
{
   bool ended = true;
   for(int i = unitList.size()-1; i >= 0; i--)
   {
      ended &= unitList[i]->atEnd();

      // Find leftest not ended element
      if (!ended)
      {
         unitList[i]->makeNextValue();
         i++;

         while (i < unitList.size())
         {
            unitList[i]->makeFirstValue();
            i++;
         }

         break;
      }
   }

   if (ended)
      return currentValue;

   currentValue = "";
   foreach(IUnit<QString>* unit, unitList)
      currentValue += unit->getCurrentValue();

   return currentValue;
}

QString RegularExpression::makeNextValue()
{
   while (makeNextValue_().length() > maxLength)
   {
      //qDebug() << currentValue;
      if (atEnd()) break;
   }

   return (currentValue.length() > maxLength) ? "" : currentValue;
}

bool RegularExpression::atEnd()
{
   bool ended = true;

   foreach(IUnit<QString> *unit, unitList)
   {
      ended &= unit->atEnd();
      if (!ended)
         return false;
   }

   return true;
}

QString RegularExpression::getRandValue()
{
   QString tmpStr = "";
   foreach(IUnit<QString>* unit, unitList)
      tmpStr += unit->getRandValue();

   return tmpStr;
}

//----------------------------------------------------------------

QString RegularExpression::print()
{
   QString str = "";

   foreach(IUnit<QString> *unit, unitList)
      str += unit->print();

   return str;
}

quint64 RegularExpression::count()
{
   quint64 tmpCount = 1;

   foreach(IUnit<QString> *unit, unitList)
      tmpCount *= unit->count();

   return tmpCount;
}

void RegularExpression::setMaxLength(int length)
{
   maxLength = length;
   
   int zapas = maxLength - minLength;

   if (zapas < 0)
      throw RegException(minLength, QObject::tr("Invalid maximum length"));

   foreach(IUnit<QString> *unit, unitList)
      unit->setMaxLength(unit->getMinLength() + zapas);
}
