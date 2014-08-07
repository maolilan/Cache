#include "cache.h"
#include "utility.h"

extern vector<vector<int>> DB;

//utility functions

bool Read(int frameid, int& result, Cache* cache_obj) {
    int flag = cache_obj->GetNode(frameid, result);
    cout << "Hit? " << flag << endl;
    if(!flag) {
	    result = DB[frameid][VALUE];
	    cache_obj->PutNode(frameid, result);
	    return false;
    }
    return true;
}

void Write(int frameid, int x, int y) {
    
}


void initialize(vector<vector<int> >& A) {
    for(int i=0; i<DBMAX; i++) {
	    A[i][0] = random()%ValueLimit;
	    A[i][1] = random()%ValueLimit;
	    A[i][2] = i;
    }
}

int Pattern1(int frameid) {
	int num = random()%10;
	if(num<8) {
		cout << "frameid " << frameid << endl;
	    return frameid;
	}
	else {
		cout << "frameID " << random()%DBMAX<<endl; 
	    return random()%DBMAX;
	 }
}

void Simulate(int count, int pattern, Cache* cache_obj) {
    int hit = 0;
    int miss = 0;
    
    int frameid = random()%DBMAX;
    int value = 0;
 

    for(int i=0; i<count; i++) {
	    if(Read(frameid, value, cache_obj)) 
		    hit++;
	    else
		    miss++;
	    switch(pattern) {
	        case 1:
		        frameid = Pattern1(frameid);
	        default:
	            frameid = random()%DBMAX;
	    }
    }

    cout << "The hitting/missing ratio is: " << double(hit)/double(miss) << endl;
    return;
}
