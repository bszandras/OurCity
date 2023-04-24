#include "Workplace.h"

Workplace::Workplace(Tile* tile) : Building(tile)
{
    this->tile = tile;
    tile->building = this;
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

bool Workplace::canWorkHere()
{
    unsigned int resSize = this->workers.size();
    unsigned short capacity = this->capacity;
    if(resSize < capacity)
    {
        return true;
    }
    return false;
}

void Workplace::setTax(unsigned short tax)
{
    this->tax = tax;
}

void Workplace::addWorker(int id)
{
    this->workers.push_back(id);
}

std::vector<int> Workplace::getWorkers()
{
	return workers;
}