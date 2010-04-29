#include "CommonUnitInfo.h"

#include <QTextCodec>

using namespace RegHope;

//----------------------------------------------------------------

CommonUnitInfo::CommonUnitInfo(QTextCodec *codec_, int maxLength_)
{
   codec = codec_;
   length = maxLength_;
}

//----------------------------------------------------------------

void CommonUnitInfo::Init(CommonUnitInfo *cui)
{
   CharConst::info = cui;
   CharRange::info = cui;
   CharSet::info = cui;
   RepeatRange::info = cui;
   RegularUnit::info = cui;
   RegularVector::info = cui;
   RegularExpression::info = cui;
}

//----------------------------------------------------------------

unsigned int CommonUnitInfo::getByte(QChar value)
{
   QByteArray arr = codec->fromUnicode(&value, 1);
   return (unsigned int)arr[0];
}

QChar CommonUnitInfo::getChar(char value)
{
   QString str = codec->toUnicode(&value, 1);
   return str[0];
}

//----------------------------------------------------------------

bool RegHope::tryReadInt(QString str, int & pos, int & value)
{
   // Check digits
   int zeros = 0;
   int digits = 0;
   while(str[pos+zeros+digits] == '0')    zeros++;
   while(str[pos+zeros+digits].isDigit()) digits++;

   // Count digits
   if (zeros+digits == 0)
      return false;

   // Recognize integer
   bool res;
   value = str.mid(pos, zeros+digits).toInt(&res);
   if (!res)
      throw RegException(pos, "Invalid integer value");

   pos += (zeros + digits);
   return true;
}

//----------------------------------------------------------------
