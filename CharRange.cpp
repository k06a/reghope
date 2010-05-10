#include "CharRange.h"
#include "CommonUnitInfo.h"
#include "CharConst.h"

using namespace RegHope;

CommonUnitInfo * CharRange::info = NULL;

//----------------------------------------------------------------

CharRange::CharRange(CharConst * a_, CharConst * b_)
{
   a = info->getByte(a_->getFirstValue()[0]);
   b = info->getByte(b_->getFirstValue()[0]);

   firstValue = makeFirstValue();
   lastValue = info->getChar(b);

   minLength = 1;
   maxLength = 1;
}

//----------------------------------------------------------------

// CharRange = ("." | (CharConst "-" CharConst))

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
CharRange * CharRange::tryRecognize(QString str, int & pos)
{
   int original = pos;

   if (pos == str.size()) return NULL;

   // Check if dot
   if (str[pos] == '.')
   {
      pos++;
      return new CharRange( new CharConst(info->getChar(0)),
                            new CharConst(info->getChar(255)) );
   }

   // First character
   CharConst *unit_1 = CharConst::tryRecognize(str, pos);
   if (unit_1 == NULL)
   {
      pos = original;
      return NULL;
   }

   if (pos == str.size())
   {
      pos = original;
      delete unit_1;
      return NULL;
   }

   // Character "-" between characters
   if (str[pos++] != '-')
   {
      pos = original;
      delete unit_1;
      return NULL;
   }

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Range ending expected"));

   // Second character
   CharConst * unit_2 = CharConst::tryRecognize(str, pos);
   if (unit_2 == NULL)
   {
      pos = original;
      delete unit_1;
      return NULL;
   }

   if ( (info->getByte(unit_1->getCurrentValue()[0])) >
        (info->getByte(unit_2->getCurrentValue()[0])) )
   {
      throw RegException(pos-3, QObject::tr("Range must be specified by lesser to greater value"), "^^^");
   }

   return new CharRange(unit_1, unit_2);
}

//----------------------------------------------------------------
// Iterative make

QString CharRange::makeFirstValue()
{
   currentValue = info->getChar(currentIndex = a);
   return currentValue;
}

QString CharRange::makeNextValue()
{
   if (currentIndex < b)
      currentIndex++;
   currentValue = info->getChar(currentIndex);
   return currentValue;
}

bool CharRange::atEnd()
{
   return (currentIndex == b);
}

QString CharRange::getRandValue()
{
   return info->getChar(qrand()%(b-a+1) + a);
}

//----------------------------------------------------------------

QString CharRange::print()
{
   return getFirstValue() + "-" + getLastValue();
}

quint64 CharRange::count()
{
   return (b - a + 1);
}
