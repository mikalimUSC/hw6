#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

int main()
{
    // Create a hash table with low resize threshold to trigger resizing quickly
    DoubleHashProber<std::string, MyStringHash> dh;
    HashTable<
        std::string,
        int,
        DoubleHashProber<std::string, MyStringHash>,
        std::hash<std::string>,
        std::equal_to<std::string> > ht(0.4, dh);

    cout << "--- Inserting elements ---" << endl;
    for (size_t i = 0; i < 15; i++) {
        std::stringstream ss;
        ss << "key" << i;
        ht.insert({ss.str(), static_cast<int>(i * 10)});
        cout << "Inserted: " << ss.str() << " -> " << i * 10 << endl;
    }

    cout << "--- Finding existing keys ---" << endl;
    for (int i : {0, 5, 10}) {
        std::stringstream ss;
        ss << "key" << i;
        auto* item = ht.find(ss.str());
        if (item) {
            cout << "Found " << ss.str() << " with value: " << item->second << endl;
        } else {
            cout << "Did not find " << ss.str() << endl;
        }
    }

    cout << "--- Testing operator[] access ---" << endl;
    ht["key5"] += 100;
    cout << "Updated key5 to: " << ht["key5"] << endl;

    cout << "--- Removing some keys ---" << endl;
    ht.remove("key3");
    ht.remove("key12");
    cout << "Removed key3 and key12." << endl;

    cout << "--- Trying to find deleted keys ---" << endl;
    cout << (ht.find("key3") ? "Found key3" : "Did not find key3") << endl;
    cout << (ht.find("key12") ? "Found key12" : "Did not find key12") << endl;

    cout << "--- Reinserting deleted key ---" << endl;
    ht.insert({"key3", 300});
    cout << "Inserted key3 -> 300" << endl;
    cout << "key3 now has value: " << ht["key3"] << endl;

    cout << "--- Testing size() and empty() ---" << endl;
    cout << "Is empty? " << (ht.empty() ? "Yes" : "No") << endl;
    cout << "Current size: " << ht.size() << endl;

    cout << "--- Reporting all elements ---" << endl;
    ht.reportAll(cout);

    return 0;
}



// #include "ht.h"
// #include "hash.h"
// #include <unordered_map>
// #include <iostream>
// #include <utility>
// #include <string>
// #include <sstream>
// #include <functional>
// using namespace std;
// int main()
// {
//     DoubleHashProber<std::string, MyStringHash > dh;
//     HashTable<
//         std::string, 
//         int, 
//         DoubleHashProber<std::string, MyStringHash >, 
//         std::hash<std::string>, 
//         std::equal_to<std::string> > ht(0.7, dh);

//     // This is just arbitrary code. Change it to test whatever you like about your 
//     // hash table implementation.
//     for(size_t i = 0; i < 10; i++){
//         std::stringstream ss;
//         ss << "hi" << i;
//         ht.insert({ss.str(), i});
//     }
//     if( ht.find("hi1") != nullptr ){
//         cout << "Found hi1" << endl;
//         ht["hi1"] += 1;
//         cout << "Incremented hi1's value to: " << ht["hi1"] << endl;
//     }
//     if( ht.find("doesnotexist") == nullptr ){
//         cout << "Did not find: doesnotexist" << endl;
//     }
//     cout << "HT size: " << ht.size() << endl;
//     ht.remove("hi7");
//     ht.remove("hi9");
//     cout << "HT size: " << ht.size() << endl;
//     if( ht.find("hi9") != nullptr ){
//         cout << "Found hi9" << endl;
//     }
//     else {
//         cout << "Did not find hi9" << endl;
//     }
//     ht.insert({"hi7",17});
//     cout << "size: " << ht.size() << endl;
//     return 0;
// }
