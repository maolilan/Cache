#ifndef _UTILITY_H
#define _UTILITY_H

#define DBMAX 100
#define ValueLimit 10
#define VALUE 2
#define CAPACITY 10

bool Read(int frameid, int& result, Cache* cache_obj);
void Write(int frameid, int x, int y);
void initialize(vector<vector<int> >& A);
int Pattern1(int frameid);
void Simulate(int count, int pattern, Cache* cache_obj);
#endif
