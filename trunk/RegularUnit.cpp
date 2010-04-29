#include "RegularUnit.h"
#include "RepeatRange.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RegularUnit::info = NULL;

//----------------------------------------------------------------

RegularUnit::RegularUnit(IUnit<QString> *charUnit_, RepeatRange *repeatRange_)
{
   charUnit = charUnit_;
   repeatRange = repeatRange_;
   makeFirstValue();
}

//----------------------------------------------------------------

// RegularUnit = (CharSet | CharConst) (RepeatRange)?

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RegularUnit * RegularUnit::tryRecognize(QString str, int & pos)
{
   IUnit<QString> * ptr1 = CharSet::tryRecognize(str, pos);
   if (ptr1 == NULL)
      ptr1 = CharConst::tryRecognize(str, pos);

   if (ptr1 == NULL) return NULL;

   IUnit<int> * ptr2 = RepeatRange::tryRecognize(str, pos);
   if (ptr2 == NULL)
      ptr2 = (IUnit<int> *)new RepeatRange(1, 1, true);

   return new RegularUnit(ptr1, (RepeatRange*)ptr2);
}

//----------------------------------------------------------------
// Min and Max bounds

QString RegularUnit::getFirstValue()
{
   int len = repeatRange->getFirstValue();
   QString sum;

   for (int i=0; i<len; i++)
      sum += charUnit->getFirstValue();

   return sum;
}

QString RegularUnit::getLastValue()
{
   int len = repeatRange->getLastValue();
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
   int len = repeatRange->makeFirstValue();
   current = "";

   for (int i=0; i<len; i++)
      current += charUnit->getLastValue();

   return current;
}

QString RegularUnit::makeNextValue()
{
   if (charUnit->atEnd())
   {
      if (repeatRange->atEnd())
         return current;
      else
         repeatRange->makeNextValue();

      charUnit->makeFirstValue();
   }


   int len = repeatRange->makeNextValue();
   current = "";

   for (int i=0; i<len; i++)
      current += charUnit->getLastValue();

   return current;
}

bool RegularUnit::atEnd()
{
   return (charUnit->atEnd() && repeatRange->atEnd());
}

//----------------------------------------------------------------

QString RegularUnit::print()
{
   return charUnit->print() + repeatRange->print();
}
