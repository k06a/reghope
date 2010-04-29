#ifndef COMMONUNITINFO_H
#define COMMONUNITINFO_H

#include "CharConst.h"
#include "CharRange.h"
#include "CharSet.h"
#include "RepeatRange.h"
#include "RegularUnit.h"
#include "RegularVector.h"
#include "RegularExpression.h"

#include <QTextEncoder>

namespace RegHope
{
   class CommonUnitInfo
   {
   public:
      QTextCodec * codec;
      int length;

      CommonUnitInfo(QTextCodec *codec_, int maxLength_)
      {
         codec = codec_;
         length = maxLength_;
      }

      static void Init(CommonUnitInfo *cui)
      {
         CharConst::info = cui;
         CharRange::info = cui;
         CharSet::info = cui;
         RepeatRange::info = cui;
         RegularUnit::info = cui;
         RegularVector::info = cui;
         RegularExpression::info = cui;
      }

      unsigned int getByte(QChar value)
      {
         QByteArray arr = codec->fromUnicode(&value, 1);
         return (unsigned int)arr[0];
      }

      QChar getChar(char value)
      {
         QString str = codec->toUnicode(&value, 1);
         return str[0];
      }
   };
}

#endif // COMMONUNITINFO_H
