#include "Workplace.h"

Workplace::Workplace(Tile* tile) : Building(tile)
{
    this->tile = tile;
    capacity = 0;
    tax = 0;
}

unsigned short Workplace::getCapacity() const
{
    return capacity;
}

unsigned short Workplace::getTax() const
{
    return tax;
}

void Workplace::setTax(unsigned short tax)
{
    this->tax = tax;
}
