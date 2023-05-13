#include "Workplace.h"

/// <summary>
/// Munkahely konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a munkahelyet �p�tj�k</param>
Workplace::Workplace(Tile* tile) : Building(tile)
{
    this->tile = tile;
    tile->building = this;
    capacity = 0;
}

/// <summary>
/// Megadja a munkahely kapacit�s�t (mennyien dolgozhatnak ott)
/// </summary>
/// <returns>A munkahely kapacit�sa</returns>
unsigned short Workplace::getCapacity() const
{
    return capacity;
}

/// <summary>
/// Be�ll�tja a munkahely kapacit�s�t.
/// </summary>
/// <param name="cap">A munkahely kapacit�sa (mennyien dolgozhatnak ott)</param>
void Workplace::setCapacity(unsigned short cap)
{
    capacity = cap;
}

/// <summary>
/// Megmondja, hogy lehet-e m�g dolgozni a munkahelyen.
/// </summary>
/// <returns>true, ha van m�g szabad hely, false, ha nincs</returns>
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

/// <summary>
/// Hozz�ad egy munk�st a munkahelyhez
/// </summary>
/// <param name="id">A lakos ID-ja</param>
void Workplace::addWorker(int id)
{
    this->workers.push_back(id);

    if (workers.size() == capacity)
    {
        // akkor betelik a munkahely, �j sprite
        tile->texId -= 3;
    }
}

/// <summary>
/// Elt�vol�tja a munk�st a munkahelyr�l
/// </summary>
/// <param name="id">A lakos ID-ja</param>
void Workplace::removeWorker(int id)
{
    //std::vector<int>::iterator new_end;
    //new_end = remove(this->workers.begin(), this->workers.end(), id);
    bool fullbefore = workers.size() == capacity;
    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i] == id)
        {
            workers.erase(workers.begin() + i);
        }
    }

    if (workers.size() < capacity && fullbefore)
    {
        // akkor lejjeb l�p egy szinttel az �p�let
        tile->texId += 3;
    }
}

/// <summary>
/// T�rli az �sszes lakost a munkahelyr�l
/// </summary>
void Workplace::clearWorkers()
{
    workers.clear();
}

/// <summary>
/// Visszaadja a munkahelyen dolgoz� lakosokat
/// </summary>
/// <returns>A munkahelyen dolgoz� lakosok ID-ja</returns>
std::vector<int> Workplace::getWorkers()
{
	return workers;
}