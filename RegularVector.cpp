#include "RegularVector.h"
#include "RegularUnit.h"
#include "RepeatRange.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RegularVector::info = NULL;

//----------------------------------------------------------------

RegularVector::RegularVector(QList<IUnit<QString> *> unitList_, RepeatRange *repeatRange_)
{
   unitList = unitList_;
   repeatRange = repeatRange_;

   firstValue = makeFirstValue();

   int tmpLen = repeatRange->getLastValue();
   for(int i = 0; i < tmpLen; i++)
      foreach(IUnit<QString>* unit, unitList)
         lastValue += unit->getLastValue();
}

//----------------------------------------------------------------

// GroupUnit = "(" (RegularUnit | GroupUnit)+ ")" (RepeatUnit)?

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RegularVector * RegularVector::tryRecognize(QString str, int & pos)
{
   if (pos == str.size()) return NULL;
   int origin = pos;

   // Check for "("
   if (str[pos++] != '(')
   {
      pos = origin;
      return NULL;
   }

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Vector values expected"));

   QList<IUnit<QString>*> list;
   while (true)
   {
      if (pos == str.size())
         throw RegException(pos, QObject::tr("Symbol \")\" expected"));

      if (str[pos] == ')') break;

      IUnit<QString> *unit = RegularVector::tryRecognize(str, pos);
      if (unit == NULL)
         unit = RegularUnit::tryRecognize(str, pos);

      if (unit == NULL)
         break;

      list.append(unit);
   }
   pos++;

   if (list.size() == 0)
      throw RegException(pos-2, QObject::tr("Brackets can not be empty"), "^^");

   // Repeater
   RepeatRange *repeatRange = (RepeatRange*)RepeatRange::tryRecognize(str, pos);
   if (repeatRange == NULL)
      repeatRange = new RepeatRange(1, 1, true);

   return new RegularVector(list, repeatRange);
}

//----------------------------------------------------------------
// Iterative make

QString RegularVector::makeFirstValue()
{
   currentValue = "";
   int n = repeatRange->makeFirstValue();

   for(int i = 0; i < n; i++)
      foreach(IUnit<QString>* unit, unitList)
         currentValue += unit->makeFirstValue();

   return currentValue;
}

QString RegularVector::makeNextValue()
{
   currentValue = "";

   bool ended = true;
   for(int i = unitList.size()-1; i >= 0; i--)
   {
      ended &= unitList[i]->atEnd();
      if (!ended)
      {
         unitList[i++]->makeNextValue();

         while (i < unitList.size())
            unitList[i++]->makeFirstValue();
      }
   }

   if (ended)
   {
      if (repeatRange->atEnd())
         return currentValue;

      repeatRange->makeNextValue();

      foreach(IUnit<QString> *unit, unitList)
         unit->makeFirstValue();
   }

   return currentValue;
}

bool RegularVector::atEnd()
{
   bool ended = repeatRange->atEnd();

   foreach(IUnit<QString> *unit, unitList)
   {
      ended &= unit->atEnd();
      if (!ended)
         return false;
   }

   return true;
}

//----------------------------------------------------------------

QString RegularVector::print()
{
   QString str = "(";

   foreach(IUnit<QString> *unit, unitList)
      str += unit->print();

   return str + ")" + repeatRange->print();
}

quint64 RegularVector::count()
{
   quint64 tmpCount = 1;

   foreach(IUnit<QString> *unit, unitList)
      tmpCount *= unit->count();

   if (repeatRange->getFirstValue() != 0)
      return tmpCount * repeatRange->count();

   return tmpCount * (repeatRange->count() - 1) + 1;
}
