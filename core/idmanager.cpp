#include "idmanager.h"
#include <cstdlib>

namespace Core {

IdManager::IdManager() {}

ID &IdManager::generateId()
{
    ID id;
    id.value = generateRandom();
    // Ensure pseudo unique value has not previously been used.
    while (exists(id)) {
        id.value = generateRandom();
    }
    addID(id);
    return IDs.at(IDs.size() - 1);
}

bool IdManager::exists(ID id)
{
    bool exists = false;
    for (int i =0; i< IDs.size(); i++) {
        exists = id.value == IDs[i].value;
        if (exists) break;
    }
    return exists;
}

void IdManager::addID(ID id)
{
    IDs.push_back(id);
}

IdManager &IdManager::instance()
{
    static IdManager idManager;
    return idManager;
}

std::string IdManager::generateRandom()
{
    size_t maxIndex = available.length();
    std::string tempString = "";
    for(int i=0; i < m_stringLength; i++ ) {
        size_t index = rand() % maxIndex;
        tempString += available[index];
    }
    return tempString;
}

} // namespace Core
