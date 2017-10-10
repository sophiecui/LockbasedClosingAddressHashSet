// Name:Beiming CUI
// Loginid:beimingc@usc.edu
// EE599
// Spring 2017

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <mutex>
#include <thread>
#include "hashset.hpp"
using namespace std;

LockHashSet::LockHashSet() {

    bucket_num = BUCKET_NUM;
    set_size = 0;
    table.resize(bucket_num);

}

void LockHashSet::printWholeSet(){

    /*print part*/
    cout << "print the whole set" << endl;
    for(int x = 0; x < table.size(); x++){
        cout<< "In Bucket #"<< x << ":"<<endl;
        for(int y = 0; y < table[x].size(); y++){
            cout<< table[x][y] << " ";   
        }
        cout<< endl;
        
    }
    cout << "set size is : " << set_size << endl;
    cout << "print the set finish" << endl;
}

bool LockHashSet::contains(int element){
    
    acquire(element);
    int hash_code = getHashCode(element);
    for(int i = 0; i < table[hash_code].size(); i++){
        if(table[hash_code][i] == element){
            release(element);
            return true;
        }
    }
    release(element);
    return false;
}

bool LockHashSet::add(int element){

    acquire(element);
    int hash_code = getHashCode(element);
    for(int i = 0; i < table[hash_code].size(); i++){
        if(table[hash_code][i] == element){
            release(element);
            return false;
        }
    }
    table[hash_code].push_back(element);
    set_size++;
    
    release(element);

    if (policy()) {
        resize();
    }
    return true;
}

bool LockHashSet::remove(int element){
    
    acquire(element);
    int hash_code = getHashCode(element);
    for(int i = 0; i < table[hash_code].size(); i++){
        if(table[hash_code][i] == element){
            table[hash_code].erase(table[hash_code].begin() + i);
            set_size--;
            release(element);
            return true;
        }
    }
    release(element);
    return false;    
}

bool LockHashSet::policy(){

    return set_size / table.size() > 4 ? true : false;
}

void LockHashSet::resize(){
    
    int oldCapacity = table.size();
    for(int i = 0; i < mutexes.size(); i++){
        mutexes[i].lock();
    }
    if(oldCapacity != table.size()){

        for(int i = 0; i < mutexes.size(); i++){
            mutexes[i].unlock();
        }
        return;
    }
    int newCapacity = 2 * oldCapacity;
    vector<int> temp;
    for(int x = 0; x < table.size(); x++){
        for(int y = 0; y < table[x].size(); y++){
            temp.push_back(table[x][y]);
        }
        table[x].clear();
    }
    table.resize(newCapacity);
    bucket_num = newCapacity;
    for(int i = 0; i < temp.size(); i++){
        int hash_code = getHashCode(temp[i]);
        table[hash_code].push_back(temp[i]);
    }
    temp.clear();
    for(int i = 0; i < mutexes.size(); i++){
            mutexes[i].unlock();
    }
    return;
}

void LockHashSet::acquire(int element){
    
    int lock_num = getHashCode(element) % BUCKET_NUM;
    mutex &m = mutexes[lock_num];
    m.lock();

}
void LockHashSet::release(int element){
    
    int lock_num = getHashCode(element) % BUCKET_NUM;
    mutex &m = mutexes[lock_num];
    m.unlock();

}

int LockHashSet::getHashCode(int element){

    return hash(element) % bucket_num;
}

//jenkins_one_at_a_time_hash
uint32_t LockHashSet::hash(uint32_t a) 
{ 
   a = (a+0x7ed55d16) + (a<<12); 
   a = (a^0xc761c23c) ^ (a>>19); 
   a = (a+0x165667b1) + (a<<5); 
   a = (a+0xd3a2646c) ^ (a<<9); 
   a = (a+0xfd7046c5) + (a<<3);
   a = (a^0xb55a4f09) ^ (a>>16);  
   return a; 
}





