#include "RegularUnit.h"
#include "CharUnit.h"
#include "RepeatUnit.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RegularUnit::info = NULL;

//----------------------------------------------------------------

RegularUnit::RegularUnit(CharUnit *charUnit_, RepeatUnit *repeatUnit_)
{
   charUnit = charUnit_;
   repeatUnit = repeatUnit_;
   makeFirstValue();
}

//----------------------------------------------------------------

// RegularUnit = CharUnit (RepeatUnit)?

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RegularUnit * RegularUnit::tryRecognize(QString str, int & pos)
{
   IUnit<QString> * ptr1 = CharUnit::tryRecognize(str, pos);
   if (ptr1 == NULL)
      return NULL;

   IUnit<int> * ptr2 = RepeatUnit::tryRecognize(str, pos);
   if (ptr2 == NULL)
      ptr2 = (IUnit<int> *)new RepeatUnit(1, 1, true);

   return new RegularUnit((CharUnit*)ptr1, (RepeatUnit*)ptr2);
}

//----------------------------------------------------------------
// Min and Max bounds

QString RegularUnit::getFirstValue()
{
   int len = repeatUnit->getFirstValue();
   QString sum;

   for (int i=0; i<len; i++)
      sum += charUnit->getFirstValue();

   return sum;
}

QString RegularUnit::getLastValue()
{
   int len = repeatUnit->getLastValue();
   QString sum;

   for (int i=0; i<len; i++)
      sum += charUnit->getLastValue();

   return sum;
}

QString RegularUnit::getCurrentValue()
{
   return current;
}

//----------------------------------------------------------------
// Iterative make

QString RegularUnit::makeFirstValue()
{
   charUnit->makeFirstValue();
   int len = repeatUnit->makeFirstValue();
   current = "";

   for (int i=0; i<len; i++)
      current += charUnit->getLastValue();

   return current;
}

QString RegularUnit::makeNextValue()
{
   if (charUnit->atEnd())
   {
      if (repeatUnit->atEnd())
         return current;
      else
         repeatUnit->makeNextValue();

      charUnit->makeFirstValue();
   }


   int len = repeatUnit->makeNextValue();
   current = "";

   for (int i=0; i<len; i++)
      current += charUnit->getLastValue();

   return current;
}

bool RegularUnit::atEnd()
{
   return (charUnit->atEnd() && repeatUnit->atEnd());
}

//----------------------------------------------------------------

QString RegularUnit::print()
{
   return charUnit->print() + repeatUnit->print();
}
