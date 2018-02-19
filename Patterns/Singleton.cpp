#include "Singleton.h"


LazySingleton* LazySingleton::instance_ = nullptr;

HungrySingleton* HungrySingleton::instance_ = new HungrySingleton();