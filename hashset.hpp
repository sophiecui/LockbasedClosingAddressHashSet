// Name:Beiming CUI
// Loginid:beimingc@usc.edu
// EE599
// Spring 2017
#ifndef HashSet_HPP
#define HashSet_HPP
#include <vector>
#include <mutex>
#include <array>
using namespace std;

const int BUCKET_NUM = 4;
class LockHashSet {
public:
	vector< vector<int> > table;
    array<mutex, BUCKET_NUM> mutexes;
    int set_size;
    int bucket_num;
    LockHashSet();
    bool contains(int element);
    bool add(int element);
    bool remove(int element);
    bool policy();
    void resize();
    void acquire(int element);
    void release(int element);
    int getHashCode(int element);
    void printWholeSet();
    uint32_t hash(uint32_t a);
};

#endif



