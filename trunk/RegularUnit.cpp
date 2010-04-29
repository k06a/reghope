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

   firstValue = makeFirstValue();

   int tmpLen = repeatRange->getLastValue();
   QString tmpStr = charUnit->getLastValue();
   for (int i=0; i<tmpLen; i++)
      lastValue += tmpStr;
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
// Iterative make

QString RegularUnit::makeFirstValue()
{
   charUnit->makeFirstValue();

   currentValue = "";
   int tmpLen = repeatRange->makeFirstValue();
   for (int i=0; i<tmpLen; i++)
      currentValue += charUnit->getLastValue();

   return currentValue;
}

QString RegularUnit::makeNextValue()
{
   if (charUnit->atEnd())
   {
      if (repeatRange->atEnd())
         return currentValue;
      else
         repeatRange->makeNextValue();

      charUnit->makeFirstValue();
   }

   currentValue = "";
   int tmpLen = repeatRange->makeNextValue();
   for (int i=0; i<tmpLen; i++)
      currentValue += charUnit->getLastValue();

   return currentValue;
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

quint64 RegularUnit::count()
{
   if (repeatRange->getFirstValue() == 0)
      return charUnit->count() * (repeatRange->count() - 1) + 1;

   return charUnit->count() * repeatRange->count();
}
