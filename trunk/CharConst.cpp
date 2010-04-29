#include "CharConst.h"
#include "CommonUnitInfo.h"
#include <QString>
#include <QObject>

using namespace RegHope;

CommonUnitInfo * CharConst::info = NULL;

//----------------------------------------------------------------

CharConst::CharConst(QChar value_)
{
	value = value_;
}

//----------------------------------------------------------------

// CharConst = ( "\\" | "\." | "\-" | "\?" | "\+" | "\*" |
//               "\(" | "\)" | "\[" | "\]" | "\{" | "\}" |
//               "\{1,3}" | "\xHH" | "\oOOO" | "\bBBBBBBBB" | *)

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
CharConst * CharConst::tryRecognize(QString str, int & pos)
{
   if (pos + 1 == str.size()) return NULL;

	// Not-escaped character
	if (str[pos] != '\\')
		return new CharConst(str[pos++]);
   pos++;

   if (pos + 1 == str.size())
      throw RegException(pos, QObject::tr("Unexpected end of expression"));

	// Simple escaped character
   if (QString("\\.-?+*()[]{}").indexOf(str[pos]) != -1)
	{
      pos++;
		return new CharConst(str[pos-1]);
	}

	// Code of character

	pos++;
	int len = 0;
	int base = 0;

	int value = info->getByte(str[pos]);
	switch(value)
	{
		case 'x':
			base = 16;
			len = 2;
			break;

		case 'o':
			base = 8;
			len = 3;
			break;

		case 'b':
			base = 2;
			len = 8;
			break;

		default:
			base = 10;
			while(str[pos+len].isDigit() && (len <= 3))
				len++;
			break;
	}

	if (len == 0)
		throw RegException(pos, QObject::tr("This character can not be escaped"));

   if (pos + len >= str.size())
      throw RegException(pos+len, QObject::tr("Unexpected end of expression"));

	bool res;
	int code = str.mid(pos, len).toInt(&res, base);

	if (res == false)
		throw RegException(pos, QObject::tr("Invalid chacter code"));

	if (code >= 256)
      throw RegException(pos, QObject::tr("Too big chacter code. Must be less than \\o400."));

	return new CharConst(info->getChar(code));
}

//----------------------------------------------------------------
// Min and Max bounds

QString CharConst::getFirstValue()
{
	return value;
}

QString CharConst::getLastValue()
{
	return value;
}

QString CharConst::getCurrentValue()
{
	return value;
}

//----------------------------------------------------------------
// Iterative make

QString CharConst::makeFirstValue()
{
	return value;
}

QString CharConst::makeNextValue()
{
	return value;
}

bool CharConst::atEnd()
{
	return true;
}

//----------------------------------------------------------------

QString CharConst::print()
{
   return value;
}
