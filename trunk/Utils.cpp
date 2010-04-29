#include "IUnit.h"

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
