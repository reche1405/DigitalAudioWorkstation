#ifndef IDMANAGER_H
#define IDMANAGER_H
#include <vector>
#include <string>
namespace Core {

struct ID {
    std::string value;
    bool operator=(ID other) {
        return value == other.value;
    }
};


class IdManager
{
public:
    explicit IdManager();
    ~IdManager() = default;
    // Generates a random string Id
    // Recursively checks if the random value exists.
    // if not adds the id to the id list
    // and returns it.
    ID& generateId();

    bool exists(ID id);
    void addID(ID id);
    static IdManager& instance();

private:
    std::vector<ID> IDs;
    int m_stringLength = 8;
    std::string available = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";
    std::string generateRandom();

    IdManager(const IdManager&) = delete;
    IdManager& operator=(const IdManager&) = delete;
};

} // namespace Core

#endif // IDMANAGER_H
