#include "CharRange.h"
#include "CommonUnitInfo.h"
#include "CharConst.h"

using namespace RegHope;

CommonUnitInfo * CharRange::info = NULL;

//----------------------------------------------------------------

CharRange::CharRange( CharConst * value_1_,
							 CharConst * value_2_ )
{
	value_1 = value_1_;
	value_2 = value_2_;
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
// Min and Max bounds

QString CharRange::getFirstValue()
{
	return value_1->getFirstValue();
}

QString CharRange::getLastValue()
{
	return value_2->getLastValue();
}

QString CharRange::getCurrentValue()
{
	return currentValue;
}

//----------------------------------------------------------------
// Iterative make

QString CharRange::makeFirstValue()
{
	currentValue = value_1->makeFirstValue();
	return currentValue;
}

QString CharRange::makeNextValue()
{
	if (currentValue != value_2->getLastValue())
      currentValue = info->getChar(info->getByte(currentValue[0]) + 1);
	return currentValue;
}

bool CharRange::atEnd()
{
	return (currentValue == value_2->getLastValue());
}

//----------------------------------------------------------------

QString CharRange::print()
{
   return value_1->getFirstValue() + "-" + value_2->getLastValue();
}
