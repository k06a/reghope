#include "RepeatRange.h"
#include "CharConst.h"
#include "CharRange.h"
#include "CharSet.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * RepeatRange::info = NULL;

//----------------------------------------------------------------

RepeatRange::RepeatRange(int a_, int b_, bool haveMax_)
{
   a = a_;
   b = b_;
   haveMax = haveMax_;
   makeFirstValue();
}

//----------------------------------------------------------------

// RepeatRange = "{" int "," int? "}"

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RepeatRange * RepeatRange::tryRecognize(QString str, int & pos)
{
   int value_from = 0;
   int value_to = 0;
   bool haveMaximum = true;

   // Check opening bracket
   if (str[pos] != '{')
      return NULL;
   pos++;

   // Check int value
   if (!tryReadInt(str, pos, value_from))
      throw RegException(pos, "Integer expected");

   // Semicolon
   if (str[pos] != ',')
      throw RegException(pos, "Comma \",\" expected");
   pos++;

   // Check int value
   haveMaximum = tryReadInt(str, pos, value_to);

   // Check closing bracket
   if (str[pos] != '}')
      throw RegException(pos, "\"}\" expected");
   pos++;

   return new RepeatRange(value_from, value_to, haveMaximum);
}

//----------------------------------------------------------------
// Min and Max bounds

int RepeatRange::getFirstValue()
{
   return a;
}

int RepeatRange::getLastValue()
{
   return b;
}

int RepeatRange::getCurrentValue()
{
   return current;
}

//----------------------------------------------------------------
// Iterative make

int RepeatRange::makeFirstValue()
{
   current = a;
   return current;
}

int RepeatRange::makeNextValue()
{
   if (current < b)
      current++;
   return current;
}

bool RepeatRange::atEnd()
{
   return (current == b);
}

//----------------------------------------------------------------

QString RepeatRange::print()
{
   if (a == b && a == 1)
      return QString("");

   QString str = QString("{%1,").arg(a);
   if (haveMax)
      str += QString("%1").arg(b);
   return str + "}";
}
