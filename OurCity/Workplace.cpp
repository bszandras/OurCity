#include "Workplace.h"

/// <summary>
/// Munkahely konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a munkahelyet építjük</param>
Workplace::Workplace(Tile* tile) : Building(tile)
{
    this->tile = tile;
    tile->building = this;
    capacity = 0;
}

/// <summary>
/// Megadja a munkahely kapacitását (mennyien dolgozhatnak ott)
/// </summary>
/// <returns>A munkahely kapacitása</returns>
unsigned short Workplace::getCapacity() const
{
    return capacity;
}

/// <summary>
/// Beállítja a munkahely kapacitását.
/// </summary>
/// <param name="cap">A munkahely kapacitása (mennyien dolgozhatnak ott)</param>
void Workplace::setCapacity(unsigned short cap)
{
    capacity = cap;
}

/// <summary>
/// Megmondja, hogy lehet-e még dolgozni a munkahelyen.
/// </summary>
/// <returns>true, ha van még szabad hely, false, ha nincs</returns>
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
/// Hozzáad egy munkást a munkahelyhez
/// </summary>
/// <param name="id">A lakos ID-ja</param>
void Workplace::addWorker(int id)
{
    this->workers.push_back(id);

    if (workers.size() == capacity)
    {
        // akkor betelik a munkahely, új sprite
        tile->texId -= 3;
    }
}

/// <summary>
/// Eltávolítja a munkást a munkahelyrõl
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
        // akkor lejjeb lép egy szinttel az épület
        tile->texId += 3;
    }
}

/// <summary>
/// Törli az összes lakost a munkahelyrõl
/// </summary>
void Workplace::clearWorkers()
{
    workers.clear();
}

/// <summary>
/// Visszaadja a munkahelyen dolgozó lakosokat
/// </summary>
/// <returns>A munkahelyen dolgozó lakosok ID-ja</returns>
std::vector<int> Workplace::getWorkers()
{
	return workers;
}