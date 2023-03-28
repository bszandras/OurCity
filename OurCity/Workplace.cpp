#include "Workplace.h"

Workplace::Workplace(Tile* tile) : Building(tile)
{
    this->tile = tile;
    capacity = 0;
    tax = 0;
}

int Workplace::getCapacity() const
{
    return capacity;
}

int Workplace::getTax() const
{
    return tax;
}

void Workplace::setTax(int tax)
{
    this->tax = tax;
}
