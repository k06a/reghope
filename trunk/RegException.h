#ifndef REGEXCEPTION_H
#define REGEXCEPTION_H

#include <QString>

namespace RegHope
{
   class RegException
   {
      int errorPosition;
      QString errorMesage;
      QString marker;

   public:
      RegException(int pos, QString str, QString mark = "^")
      {
         errorPosition = pos;
         errorMesage = str;
         marker = mark;
      }

      int getErrorPosition()
      {
         return errorPosition;
      }

      QString getErrorMesage()
      {
         return errorMesage;
      }

      QString getErrorMarker()
      {
         return marker;
      }
   };
}

#endif // REGEXCEPTION_H
