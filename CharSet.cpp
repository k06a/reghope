#include "CharSet.h"
#include "CommonUnitInfo.h"
#include "CharConst.h"
#include "CharRange.h"

using namespace RegHope;

CommonUnitInfo * CharSet::info = NULL;

//----------------------------------------------------------------

CharSet::CharSet(QSet<QChar> values_)
{
   values = values_.values();
   qSort(values.begin(), values.end());

   firstValue = makeFirstValue();
   lastValue = values.last();

   minLength = 1;
   maxLength = 1;
}

//----------------------------------------------------------------

// CharSet = "[" ("^")? (CharConst | CharRange)+ "]"

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
CharSet * CharSet::tryRecognize(QString str, int & pos)
{
	int original = pos;
	QList<IUnit<QString> *> list;

   if (pos == str.size()) return NULL;

	// First character
	if (str[pos++] != '[')
	{
		pos = original;
		return NULL;
	}

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Unexpected end of file"));

	// Inversion set character
	bool inverse = false;
	if (str[pos] == '^')
	{
		inverse = true;
		pos++;
	}

   if (pos == str.size())
      throw RegException(pos, QObject::tr("Unexpected end of file"));

	// Search all CharConst and CharRanges in set
	for( ; ; )
	{
      if (pos == str.size())
         throw RegException(pos, "Backet \"]\" expected");

      if (str[pos] == ']')
      {
         pos++;
         break;
      }

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
      throw RegException(pos-2, "Set of characters can not be empty", "^^");

	// Unition of sets
   QSet<QChar> set;
	foreach (IUnit<QString> * item, list)
	{
      set.insert(item->makeFirstValue()[0]);
		while (!item->atEnd())
         set.insert(item->makeNextValue()[0]);
	}

	if (inverse)
	{
		// Set inversion
      QSet<QChar> inv_set;
		for (int code=0; code<256; code++)
		{
         QChar chr = info->getChar(code);
         if (!set.contains(chr))
            inv_set.insert(chr);
		}
		set = inv_set;
	}

	foreach(IUnit<QString> *unit, list)
		delete unit;

	return new CharSet(set);
}

//----------------------------------------------------------------
// Iterative make

QString CharSet::makeFirstValue()
{
   iter = values.begin();
   return (currentValue = *iter);
}

QString CharSet::makeNextValue()
{
   ++iter;
   return (currentValue = *iter);
}

bool CharSet::atEnd()
{
   return (iter+1 == values.end());
}

QString CharSet::getRandValue()
{
   int a = 0;
   int b = values.size() - 1;
   return values[qrand()%(b-a+1) + a];
}

//----------------------------------------------------------------

QString CharSet::print()
{
   QString str = "[";

   for(int i=0; i<values.size(); i++)
      str += CharConst(values[i]).print();

   return str + "]";
}

quint64 CharSet::count()
{
   return values.size();
}
