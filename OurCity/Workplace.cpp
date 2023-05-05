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

void Workplace::setCapacity(unsigned short cap)
{
    capacity = cap;
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

void Workplace::removeWorker(int id)
{
    //std::vector<int>::iterator new_end;
    //new_end = remove(this->workers.begin(), this->workers.end(), id);
    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i] == id)
        {
            workers.erase(workers.begin() + i);
        }
    }
}

std::vector<int> Workplace::getWorkers()
{
	return workers;
}