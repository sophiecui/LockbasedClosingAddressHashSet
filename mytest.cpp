// Name:Beiming CUI
// Loginid:beimingc@usc.edu
// EE599
// Spring 2017
#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <array>
#include "hashset.hpp"
#include <sys/time.h>
using namespace std;

LockHashSet* set = new LockHashSet();
LockHashSet* set1 = new LockHashSet();
LockHashSet* set2 = new LockHashSet();


struct timeval system_start, test_start, now_time;

/* ----------------------- Time Helper Functions ----------------------- */
//To change the timeval into unsigned int value(in us form)
unsigned int changeTimevaltoIntUs(struct timeval t){
    
    return (t.tv_sec * 1000000) + t.tv_usec ;
}
//get a period of time (in us form)
unsigned int getPeriodTime(struct timeval t1, struct timeval t0){
    
    return changeTimevaltoIntUs(t1) - changeTimevaltoIntUs(t0);
}

//To display the time (in ms form) 
double displayNowTime(){
    
    unsigned int temp = 0;
    struct timeval temp_now_time;
    gettimeofday(&temp_now_time, 0);
    temp = changeTimevaltoIntUs(temp_now_time) - changeTimevaltoIntUs(system_start);
    return ((double)temp)/1000;
}
//To display period of time in ms form
// double displayPeriod(unsigned int period){
    
//     return ((double)period)/1000;
// }

//To display the time (in ms form) 
// double displayTime(struct timeval t){

//     unsigned int temp = 0;
//     temp = changeTimevaltoIntUs(t) - changeTimevaltoIntUs(system_start);
//     return ((double)temp)/1000;
// }

/*********************************************************************/

// void printOnTerminal(int threadID, string const& msg, int num){
    
//     set->getPrintMutex()->lock();
//     cout<<"thread ID#"<< threadID << ":"<< msg << num << endl;
//     set->getPrintMutex()->unlock();
// }

// void printOnTerminal(int threadID, string const& msg){
    
//     set->getPrintMutex()->lock();
//     cout<<"thread ID#"<< threadID << ":"<< msg << endl;
//     set->getPrintMutex()->unlock();
// }

void TestAdd(int threadID, int numTestInt){

  for(int i = 1; i <= numTestInt; i++){
    set->add(i);
    // if(set->add(i)) {
    //   printOnTerminal(threadID, "successfully add: ", i);
    // } else {
    //   printOnTerminal(threadID, "failed to add: ", i);
    // }
  }
}

void testCorrectAdd(){
  cout<<"/************************************************************/"<<endl;
  cout<<"Starting test add(), here 3 threads add from 1 to 20" <<endl;
  gettimeofday(&test_start,0);
  thread threads[3];
  for (int i = 0; i < 3; i++) {
    threads[i] = thread(TestAdd, i + 1, 20);
  }
  for (int i = 0; i < 3; i++) {
    threads[i].join();
  }

  gettimeofday(&now_time,0);
  set->printWholeSet();
  cout<<"Total test time is (in us form): " << getPeriodTime(now_time, test_start)<<endl;
  cout<<"End the test add()" <<endl;
  return;

}

void TestContains(int threadID, int numTestInt){

  for(int i = 1; i <= numTestInt/2; i++){
    set->contains(i);
    // if(set->contains(i)) {
    //   printOnTerminal(threadID, "contains ", i);
    // } else {
    //   printOnTerminal(threadID, "does not contains ", i);
    // }
  }
  for(int i = 1; i <= numTestInt/2; i++){
    set->contains(-1 * i);
    // if(set->contains(-1 * i)) {
    //   printOnTerminal(threadID, "contains ", -1 * i);
    // } else {
    //   printOnTerminal(threadID, "does not contains ", -1 * i);
    // }
  }
}

void testCorrectContains(){

  cout<<"/**********************************************************/"<<endl;
  cout<<"Starting test contains(), here 3 threads, test 10 exist element and 10 did not exit element" <<endl;
  gettimeofday(&test_start,0);
  thread threads[3];
  for (int i = 0; i < 3; i++) {
    threads[i] = thread(TestContains, i + 1, 20);
  }
  for (int i = 0; i < 3; i++) {
    threads[i].join();
  }

  gettimeofday(&now_time,0);
  set->printWholeSet();
  cout<<"Total test time is (in us form): " << getPeriodTime(now_time, test_start)<<endl;
  cout<<"End the test contains()" <<endl;
  return;

}

void TestRemove(int threadID, int numTestInt){

  for(int i = 1; i <= numTestInt/2; i++){
    set->remove(i);
    // if(set->remove(i)) {
    //   printOnTerminal(threadID, "successfully remove: ", i);
    // } else {
    //   printOnTerminal(threadID, "failed to remove", i);
    // }
  }
}

void testCorrectRemove(){

  cout<<"/**********************************************************/"<<endl;
  cout<<"Starting test remove(), here 3 threads, test remove 10 exist element and 10 did not exit element" <<endl;
  gettimeofday(&test_start,0);
  int numThreads = 3;
  thread threads[3];
  for (int i = 0; i < numThreads; i++) {
    threads[i] = thread(TestRemove, i + 1, 20);
  }
  for (int i = 0; i < numThreads; i++) {
    threads[i].join();
  }

  gettimeofday(&now_time,0);
  set->printWholeSet();
  cout<<"Total test time is (in us form): " << getPeriodTime(now_time, test_start)<<endl;
  cout<<"End the test remove()" <<endl;
  return;

}

void TestResize(int threadID, int numTestInt){

  for(int i = 0; i < numTestInt; i++){
    int current_element = rand() % 100;
    set1->add(current_element);
  }
}

void testCorrectResize(){

  cout<<"/**********************************************************/"<<endl;
  cout<<"Starting test resize()"<<endl;
  cout<<"3 threads add 20 elements random generated from 1 to 100"<<endl;
  cout<<"Num of Bucket is initialized to be 4"<<endl;
  gettimeofday(&test_start,0);
  int numThreads = 3;
  thread threads[3];
  for (int i = 0; i < numThreads; i++) {
    threads[i] = thread(TestResize, i + 1, 20);
  }
  for (int i = 0; i < numThreads; i++) {
    threads[i].join();
  }

  gettimeofday(&now_time,0);
  set1->printWholeSet();
  cout<<"Total test time is (in us form): " << getPeriodTime(now_time, test_start)<<endl;
  cout<<"End the test resize()" <<endl;
  return;
}

void BasicTest(int threadID, int testNum) {

  for(int i = 0; i < testNum; i++){
    int current_element = rand() % 1000;
    set2->add(current_element);
  }
  for(int i = 0; i < testNum; i++){
    int current_element = rand() % 1000;
    set2->contains(current_element);
  }
  for(int i = 0; i < testNum/2; i++){
    int current_element = rand() % 1000;
    set2->remove(current_element);
  }
  return;
}
void testLargeOperations(){
  
  cout<<"/**********************************************************/"<<endl;
  cout<<"Starting test large num of operations"<<endl;
  cout<<"Each threads do 100 times add, 100 times contains, 50 times remove"<<endl;
  gettimeofday(&test_start,0);
  int numThreads = 10;
  thread threads[10];
  for (int i = 0; i < numThreads; i++) {
    threads[i] = thread(BasicTest, i + 1, 100);
  }
  for (int i = 0; i < numThreads; i++) {
    threads[i].join();
  }

  gettimeofday(&now_time,0);
  set2->printWholeSet();
  cout<<"Total test time is (in us form): " << getPeriodTime(now_time, test_start)<<endl;
  cout<<"End the test large num of operations" <<endl;
  return;
}

int main() {

  gettimeofday(&system_start,0);
  cout<<"/***********************Start Test Program*************************/"<<endl;
  cout<<"Start Time is: "<< displayNowTime() <<endl;
  testCorrectAdd();
  testCorrectContains();
  testCorrectRemove();
  testCorrectResize();
  testLargeOperations();  
  return 0;
}

 



