#include "RegularVector.h"
#include "RegularUnit.h"
#include "RepeatUnit.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RegularVector::info = NULL;

//----------------------------------------------------------------

RegularVector::RegularVector(QList<IUnit<QString> *> unitList_, RepeatUnit *repeatUnit_)
{
   unitList = unitList_;
   repeatUnit = repeatUnit_;
   makeFirstValue();
}

//----------------------------------------------------------------

// GroupUnit = "(" (RegularUnit | GroupUnit)+ ")" (RepeatUnit)?

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RegularVector * RegularVector::tryRecognize(QString str, int & pos)
{
   int origin = pos;

   // Check for "("
   if (str[pos++] != '(')
   {
      pos = origin;
      return NULL;
   }

   QList<IUnit<QString>*> list;
   while (true)
   {
      if (str[pos] == ')')
         break;

      RegularVector *groupUnit = RegularVector::tryRecognize(str, pos);
      if (groupUnit == NULL)
      {
         RegularUnit *regularUnit = RegularUnit::tryRecognize(str, pos);
         if (regularUnit == NULL)
            break;

         list.append(regularUnit);
         continue;
      }

      list.append(groupUnit);
   }

   if (list.size() == 0)
      throw new RegException(pos, QObject::tr("Brackets can not be empty"));

   // Check for ")"
   if (str[pos++] != ')')
      throw new RegException(pos, QObject::tr("Expected \")\" character"));

   // Repeater
   RepeatUnit *repeatUnit = (RepeatUnit*)RepeatUnit::tryRecognize(str, pos);
   if (repeatUnit == NULL)
      repeatUnit = new RepeatUnit(1, 1, true);

   return new RegularVector(list, repeatUnit);
}

//----------------------------------------------------------------
// Min and Max bounds

QString RegularVector::getFirstValue()
{
   QString str;
   for(int i = 0; i < repeatUnit->getFirstValue(); i++)
      foreach(IUnit<QString>* unit, unitList)
         str += unit->getFirstValue();
   return str;
}

QString RegularVector::getLastValue()
{
   QString str;
   for(int i = 0; i < repeatUnit->getLastValue(); i++)
      foreach(IUnit<QString>* unit, unitList)
         str += unit->getLastValue();
   return str;
}

QString RegularVector::getCurrentValue()
{
   return currentValue;
}

//----------------------------------------------------------------
// Iterative make

QString RegularVector::makeFirstValue()
{
   currentValue = "";
   int n = repeatUnit->makeFirstValue();

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
      if (repeatUnit->atEnd())
         return currentValue;

      repeatUnit->makeNextValue();

      foreach(IUnit<QString> *unit, unitList)
         unit->makeFirstValue();
   }

   return currentValue;
}

bool RegularVector::atEnd()
{
   bool ended = repeatUnit->atEnd();

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

   return str + ")" + repeatUnit->print();
}
