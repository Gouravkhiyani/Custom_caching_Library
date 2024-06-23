#include <bits/stdc++.h>
#include "cache.h"

int main()
{
    /* Uncomment any eviction policy to test */

    MapDataStore<std::string, int> MapDataStore(4);

    // FIFO<std::string> fifoPolicy;
    LIFO<std::string> lifoPolicy;
    // LRU<std::string> lruPolicy;

    
    // Cache<std::string, int> test(fifoPolicy, MapDataStore);
    Cache<std::string, int> test(lifoPolicy, MapDataStore);
    // Cache<std::string, int> test(lruPolicy, MapDataStore);

    test.put("A",5);
    test.put("B",6);
    test.put("C",10);
    test.put("D",100);
    test.put("F",100);
    std::cout<<test.get("B")<<"\n";
    test.put("E",19);
    std::cout<<test.get("C")<<"\n";
    std::cout<<test.get("F")<<"\n";
    test.put("ABC",100);

    return 0;
}