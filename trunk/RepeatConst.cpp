#include "RepeatConst.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RepeatConst::info = NULL;

//----------------------------------------------------------------

RepeatConst::RepeatConst(int value_)
{
   value = value_;
}

//----------------------------------------------------------------

// RepeatRange = "{" int "}"

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RepeatConst * RepeatConst::tryRecognize(QString str, int & pos)
{
   // Check opening bracket
   if (str[pos] != '{')
      return NULL;
   pos++;

   // Check int value
   int value;
   if (!tryReadInt(str, pos, value))
      throw RegException(pos, "Integer expected");

   // Check closing bracket
   if (str[pos] != '}')
      throw RegException(pos, "\"}\" expected");
   pos++;

   return new RepeatConst(value);
}

//----------------------------------------------------------------
// Min and Max bounds

int RepeatConst::getFirstValue()
{
   return value;
}

int RepeatConst::getLastValue()
{
   return value;
}

int RepeatConst::getCurrentValue()
{
   return value;
}

//----------------------------------------------------------------
// Iterative make

int RepeatConst::makeFirstValue()
{
   return value;
}

int RepeatConst::makeNextValue()
{
   return value;
}

bool RepeatConst::atEnd()
{
   return true;
}

//----------------------------------------------------------------

QString RepeatConst::print()
{
   return (value == 1) ? QString("") : QString("{%1}").arg(value);
}
