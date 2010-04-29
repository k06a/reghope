#include "CharUnit.h"
#include "CharConst.h"
#include "CharSet.h"
#include "CommonUnitInfo.h"

using namespace RegHope;

CommonUnitInfo * CharUnit::info = NULL;

//----------------------------------------------------------------

CharUnit::CharUnit(IUnit<QString> * unit_)
{
   unit = unit_;
}

//----------------------------------------------------------------

// CharUnit  = (CharSet | CharConst)

// Try to create reg.exp. unit from \str on position \pos.
// Returns new object or null, and moves \pos after reg.exp.
IUnit<QString> * CharUnit::tryRecognize(QString str, int & pos)
{
   IUnit<QString> * ptr = CharSet::tryRecognize(str, pos);

   if (ptr == NULL)
      return CharConst::tryRecognize(str, pos);

   return ptr;
}

//----------------------------------------------------------------
// Min and Max bounds

QString CharUnit::getFirstValue()
{
   return unit->getFirstValue();
}

QString CharUnit::getLastValue()
{
   return unit->getLastValue();
}

QString CharUnit::getCurrentValue()
{
   return unit->getCurrentValue();
}

//----------------------------------------------------------------
// Iterative make

QString CharUnit::makeFirstValue()
{
   return unit->makeFirstValue();
}

QString CharUnit::makeNextValue()
{
   return unit->makeNextValue();
}

bool CharUnit::atEnd()
{
   return unit->atEnd();
}

//----------------------------------------------------------------

QString CharUnit::print()
{
   return unit->print();
}
