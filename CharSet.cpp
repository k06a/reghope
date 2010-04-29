#include "CharSet.h"
#include "CommonUnitInfo.h"
#include "CharConst.h"
#include "CharRange.h"

using namespace RegHope;

CommonUnitInfo * CharSet::info = NULL;

//----------------------------------------------------------------

CharSet::CharSet(QSet<QString> values_)
{
   values = values_.values();
	makeFirstValue();
}

//----------------------------------------------------------------

// CharSet = "[" ("^")? (CharConst | CharRange)+ "]"

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
CharSet * CharSet::tryRecognize(QString str, int & pos)
{
	int original = pos;
	QList<IUnit<QString> *> list;

   if (pos + 1 == str.size()) return NULL;

	// First character
	if (str[pos++] != '[')
	{
		pos = original;
		return NULL;
	}

   if (pos + 1 == str.size())
      throw new RegException(pos, QObject::tr("Unexpected end of file"));

	// Inversion set character
	bool inverse = false;
	if (str[pos] == '^')
	{
		inverse = true;
		pos++;
	}

   if (pos + 1 == str.size())
      throw RegException(pos, QObject::tr("Unexpected end of file"));

	// Search all CharConst and CharRanges in set
	for( ; ; )
	{
      if (pos + 1 == str.size())
         throw RegException(pos, "Backet \"]\" expected");

		if (str[pos] == ']') break;

		IUnit<QString> * unit = CharRange::tryRecognize(str, pos);

      if (unit == NULL)
		{
			unit = CharConst::tryRecognize(str, pos);

			if (unit == NULL)
				break;
			else
				list.append(unit);
		}
		else
			list.append(unit);
	}

	if (!inverse && list.size() == 0)
		throw RegException(pos, "Set of characters can not be empty");

	// Unition of sets
	QSet<QString> set;
	foreach (IUnit<QString> * item, list)
	{
		set.insert(item->makeFirstValue());
		while (!item->atEnd())
			set.insert(item->makeNextValue());
	}

	if (inverse)
	{
		// Set inversion
		QSet<QString> inv_set;
		for (int code=0; code<256; code++)
		{
			QString str = info->getChar(code);
			if (!set.contains(str))
				inv_set.insert(str);
		}
		set = inv_set;
	}

	foreach(IUnit<QString> *unit, list)
		delete unit;

	return new CharSet(set);
}

//----------------------------------------------------------------
// Min and Max bounds

QString CharSet::getFirstValue()
{
   return values.first();
}

QString CharSet::getLastValue()
{
   return values.last();
}

QString CharSet::getCurrentValue()
{
	return currentValue;
}

//----------------------------------------------------------------
// Iterative make

QString CharSet::makeFirstValue()
{
   currentIndex = 0;
   currentValue = values[0];
   return currentValue;
}

QString CharSet::makeNextValue()
{
   if (currentIndex < values.size()-1)
      currentIndex++;
   currentValue = values[currentIndex];
   return currentValue;
}

bool CharSet::atEnd()
{
   return (currentIndex == values.size()-1);
}

//----------------------------------------------------------------

QString CharSet::print()
{
   QString str = "[";

   for(int i=0; i<values.size(); i++)
      str += values[i];

   return str + "]";
}
