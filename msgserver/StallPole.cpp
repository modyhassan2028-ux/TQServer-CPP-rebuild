#include "StallPole.h"

CStallManager& CStallManager::Instance() {
    static CStallManager s;
    return s;
}

CPoleManager& CPoleManager::Instance() {
    static CPoleManager s;
    return s;
}
