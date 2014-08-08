#include "cache.h"
#include "utility.h"

extern vector<vector<int>> DB;

//utility functions

bool Read(int frameid, int& result, Cache* cache_obj) {
    int flag = cache_obj->GetNode(frameid, result);
    if(!flag) return false;
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
		cout << "same frameid as previous " << frameid << endl;
	    return frameid;
	}
	else {
		int newid=random()%DBMAX;
		cout << "frameID " << newid<<endl; 
	    return newid;
	 }
}

void SimulateLFU(int count, int pattern, LFUCache* cache_obj) {
    int hit = 0;
    int miss = 0;
    
    srand((int)time(NULL));
    int frameid = random()%DBMAX;
    cout << "frameid " << frameid <<endl;
    int value = 0;
 

    for(int i=0; i<count; i++) {		
	    if(Read(frameid, value, cache_obj)) 
		    hit++;
	    else
		    miss++;
		    
		PrintLFUCacheStatus(cache_obj);
		cout<< endl << endl;
	    switch(pattern) {
	        case 1:
		        frameid = Pattern1(frameid);
		        break;
	        default:
	            frameid = random()%DBMAX;
	            break;
	    }
    }

    cout << "The hitting/missing ratio is: " << double(hit)/double(miss) << endl;
    return;
}

void SimulateLRU(int count, int pattern, LRUCache* cache_obj) {
    int hit = 0;
    int miss = 0;
    
    srand((int)time(NULL));
    int frameid = random()%DBMAX;
    cout << "frameid " << frameid <<endl;
    int value = 0;
 

    for(int i=0; i<count; i++) {		
	    if(Read(frameid, value, cache_obj)) 
		    hit++;
	    else
		    miss++;
		    
		PrintLRUCacheStatus(cache_obj);
		cout<< endl << endl;
	    switch(pattern) {
	        case 1:
		        frameid = Pattern1(frameid);
		        break;
	        default:
	            frameid = random()%DBMAX;
	            break;
	    }
    }
    cout << "The hitting/missing ratio is: " << double(hit)/double(miss) << endl;
    return;
}

void PrintLFUCacheStatus(LFUCache* lfucache) {
    FreqNode* freqnode = lfucache->FreqHead->Next;

    while (freqnode) {
        cout<<"frequency "<<freqnode->Freq<<":";
        LFUListNode* listnode = freqnode->HeadNode;
        while(listnode) {
            cout<<listnode->Value<<", ";
            listnode = listnode->Next;
        }
        cout<<endl;
        freqnode = freqnode->Next;
    }
        return;
}

void PrintLRUCacheStatus(LRUCache* lrucache) {
	LRUListNode* listnode = lrucache->Head;
	
	while(listnode) {
		cout<<listnode->Value<<", ";
		if(listnode==lrucache->End) break;
		listnode = listnode->Next;
    }
    cout<<endl;
}
