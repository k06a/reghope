#include "CharArray.h"
#include "CommonUnitInfo.h"
#include "CharConst.h"
#include "CharRange.h"
#include "CharSet.h"

using namespace RegHope;

CommonUnitInfo * CharArray::info = NULL;

//----------------------------------------------------------------

CharArray::CharArray(CharSet * set_)
{
   set = set_;
}

//----------------------------------------------------------------

// Character = (CharSet | CharRange | CharConst)+

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
IUnit<QString> * CharArray::tryRecognize(QString str, int & pos)
{
   IUnit<QString> * unit = CharSet::tryRecognize(str, pos);
   if (unit != NULL)
      return unit;

   unit = CharRange::tryRecognize(str, pos);
   if (unit != NULL)
   {
      int from = info->getByte( unit->getFirstValue()[0] );
      int to = info->getByte( unit->getLastValue()[0] );

      QSet<QString> set;
      for (int code=from; code<to; code++)
         set.insert( info->getChar(code) );

      delete unit;
      return new CharSet(set);
   }

   unit = CharConst::tryRecognize(str, pos);
   if (unit != NULL)
   {
      QSet<QString> set;
      set.insert( unit->getFirstValue() );

      delete unit;
      return new CharSet(set);
   }

   return NULL;
}

//----------------------------------------------------------------
// Min and Max bounds

QString CharArray::getFirstValue()
{
   return set->getFirstValue();
}

QString CharArray::getLastValue()
{
   return set->getLastValue();
}

//----------------------------------------------------------------
// Iterative make

QString CharArray::makeFirstValue()
{
   return set->makeFirstValue();
}

QString CharArray::makeNextValue()
{
   return set->makeNextValue();
}

bool CharArray::atEnd()
{
   return set->atEnd();
}

//----------------------------------------------------------------
