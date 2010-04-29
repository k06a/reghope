#ifndef COMMONUNITINFO_H
#define COMMONUNITINFO_H

#include "CharConst.h"
#include "CharRange.h"
#include "CharSet.h"
#include "RepeatRange.h"
#include "RegularUnit.h"
#include "RegularVector.h"
#include "RegularExpression.h"

class QTextCodec;

namespace RegHope
{
   class CommonUnitInfo
   {
   public:
      QTextCodec * codec;
      int length;

      CommonUnitInfo(QTextCodec *codec_, int maxLength_);

      static void Init(CommonUnitInfo *cui);

      unsigned int getByte(QChar value);

      QChar getChar(char value);
   };

   bool tryReadInt(QString str, int & pos, int & value);
}

#endif // COMMONUNITINFO_H
