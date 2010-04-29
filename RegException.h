#ifndef REGEXCEPTION_H
#define REGEXCEPTION_H

#include <QString>

namespace RegHope
{
   class RegException
   {
      int errorPosition;
      QString errorMesage;

   public:
      RegException(int pos, QString str)
      {
         errorPosition = pos;
         errorMesage = str;
      }

      int getErrorPosition()
      {
         return errorPosition;
      }

      QString getErrorMesage()
      {
         return errorMesage;
      }
   };
}

#endif // REGEXCEPTION_H
