#include "cache.h"
#include "utility.h"

//Data Base
vector<vector<int>> DB(DBMAX, vector<int>(3,0));
//index is ID, the value 1 is the retrieve cost, 
//the value 2 is the size, 
//the value 3 is the value it stores

int main() {
    initialize(DB);
    LFUCache* lfucache = new LFUCache(CAPACITY);
    //LRUCache* lrucache = new LRUCache(CAPACITY);
    int count = 10000;
    int pattern = 1;
    SimulateLFU(count, pattern, lfucache); 
    //SimulateLRU(count, pattern, lrucache);
    return 0;
}
