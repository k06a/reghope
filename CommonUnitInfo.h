#ifndef COMMONUNITINFO_H
#define COMMONUNITINFO_H

#include <QTextEncoder>

namespace RegHope
{
   class CommonUnitInfo
   {
   public:
      QTextCodec * codec;
      int length;

      char getByte(QChar value)
      {
         QByteArray arr = codec->fromUnicode(&value, 1);
         return arr[0];
      }

      QChar getChar(char value)
      {
         QString str = codec->toUnicode(&value, 1);
         return str[0];
      }
   };
}

#endif // COMMONUNITINFO_H
