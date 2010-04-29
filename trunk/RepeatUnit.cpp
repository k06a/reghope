#include "RepeatUnit.h"
#include "RepeatConst.h"
#include "RepeatRange.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RepeatUnit::info = NULL;

//----------------------------------------------------------------

RepeatUnit::RepeatUnit(int a_, int b_, bool haveMax_)
{
   a = a_;
   b = b_;
   haveMax = haveMax_;
   makeFirstValue();
}

//----------------------------------------------------------------

// RepeatUnit  = ("?" | "+" | "*" | RepeatConst | RepeatRange)

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
IUnit<int> * RepeatUnit::tryRecognize(QString str, int & pos)
{
   int value_from = 0;
   int value_to = 0;
   bool haveMaximum = true;

   if (str[pos] == '?')
   {
      value_from = 0;
      value_to = 1;
      haveMaximum = true;
      pos++;
      return new RepeatUnit(value_from, value_to, haveMaximum);
   }

   if (str[pos] == '+')
   {
      value_from = 1;
      haveMaximum = false;
      pos++;
      return new RepeatUnit(value_from, value_to, haveMaximum);
   }

   if (str[pos] == '*')
   {
      value_from = 0;
      haveMaximum = false;
      pos++;
      return new RepeatUnit(value_from, value_to, haveMaximum);
   }

   // Check for { x }
   RepeatConst * repeatConstUnit = RepeatConst::tryRecognize(str, pos);
   if (repeatConstUnit != NULL)
      return repeatConstUnit;

   // Check for { x , y }
   RepeatRange * repeatRangeUnit = RepeatRange::tryRecognize(str, pos);
   if (repeatRangeUnit != NULL)
      return repeatRangeUnit;

   return NULL;
}

//----------------------------------------------------------------
// Min and Max bounds

int RepeatUnit::getFirstValue()
{
   return a;
}

int RepeatUnit::getLastValue()
{
   return b;
}

int RepeatUnit::getCurrentValue()
{
   return current;
}

//----------------------------------------------------------------
// Iterative make

int RepeatUnit::makeFirstValue()
{
   current = a;
   return current;
}

int RepeatUnit::makeNextValue()
{
   if (current < b)
      current++;
   return current;
}

bool RepeatUnit::atEnd()
{
   return (current == b);
}

//----------------------------------------------------------------

QString RepeatUnit::print()
{
   if ((a == b) && (a == 1)) return QString("");

   if ((a == 0) && (b == 1)) return "?";
   if ((a == 1) && !haveMax) return "+";
   if ((a == 0) && !haveMax) return "*";

   if (a == b) return QString("{%1}").arg(a);

   QString str = QString("{%1,").arg(a);
   if (haveMax)
      str += QString("%2").arg(b);
   return str + "}";
}
