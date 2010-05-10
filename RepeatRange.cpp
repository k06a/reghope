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

   firstValue = makeFirstValue();
   lastValue = b;

   minLength = (haveMax) ? b : a;
   maxLength = (haveMax) ? b : 1000000;
}

//----------------------------------------------------------------

// RepeatRange = ("?" | "+" | "*" | ("{" int ("," int?)? "}"))

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
RepeatRange * RepeatRange::tryRecognize(QString str, int & pos)
{
   int value_from = 0;
   int value_to = 0;
   bool haveMaximum = true;

   if (pos == str.size()) return NULL;

   switch (info->getByte(str[pos]))
   {
      case '?': pos++; return new RepeatRange(0, 1, true);
      case '+': pos++; return new RepeatRange(1, -1, false);
      case '*': pos++; return new RepeatRange(0, -1, false);
   }

   // Check opening bracket
   if (str[pos] != '{')
      return NULL;
   pos++;

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Repeat counter start value expected"));

   // Check int value
   if (!tryReadInt(str, pos, value_from))
      throw RegException(pos, QObject::tr("Integer expected"));

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Symbol \",\" or \"}\" expected"));

   // If one value
   if (str[pos] == '}')
   {
      pos++;
      return new RepeatRange(value_from, value_from, haveMaximum);
   }

   // Semicolon
   if (str[pos] != ',')
      throw RegException(pos, QObject::tr("Comma \",\" expected"));
   pos++;

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Repeat counter finish value expected"));

   // Check int value
   haveMaximum = tryReadInt(str, pos, value_to);

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Symbol \"}\" expected"));

   // Check closing bracket
   if (str[pos] != '}')
      throw RegException(pos, QObject::tr("Symbol \"}\" expected"));
   pos++;

   return new RepeatRange(value_from, value_to, haveMaximum);
}

//----------------------------------------------------------------
// Iterative make

int RepeatRange::makeFirstValue()
{
   return (currentValue = a);
}

int RepeatRange::makeNextValue()
{
   if ((currentValue < b) && (currentValue < maxLength))
      currentValue++;
   return currentValue;
}

bool RepeatRange::atEnd()
{
   return ((currentValue == b) && haveMax) ||
          ((currentValue == maxLength) && !haveMax);
}

int RepeatRange::getRandValue()
{
   return (qrand()%(b-a+1) + a);
}

//----------------------------------------------------------------

QString RepeatRange::print()
{
   if ((a == b) && haveMax)
   {
      if (a == 1)
         return QString("");
      else
         return QString("{%1}").arg(a);
   }

   if ((a == 0) && (b == 1)) return QString("?");
   if ((a == 1) && !haveMax) return QString("+");
   if ((a == 0) && !haveMax) return QString("*");

   QString str = QString("{%1,").arg(a);

   if (haveMax) str += QString("%1").arg(b);

   return str + "}";
}

quint64 RepeatRange::count()
{
   if (haveMax)
      return (qMin(b, maxLength) - a + 1);

   return (maxLength - a + 1); //TODO fix counter without haveMax
}

void RepeatRange::setMaxLength(int length)
{
   if (!haveMax) b = length;
   maxLength = length;
   minLength = b;
}
