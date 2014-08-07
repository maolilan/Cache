//utility functions

bool Read(int FrameID, int& result, Cache* cache_obj) {
    int flag = cache_obj->Get(FrameID, result);
    if(!flag) {
	result = DB[FrameID];
	cache_obj->Put(FrameID, result);
	return false;
    }
    return true;
}

void Write(int FrameID, int x, int y) {
    
}


void initialize(vector<vector<int>>& A) {
    for(int i=0; i<DBMAX; i++) {
	A[i][0] = random()%ValueLimit;
	A[i][1] = random()%ValueLimit;
	A[i][2] = i;
    }
}

int Pattern1(int frameid) {
	int num = random()%10;
	if(num<8)
	    return frameid;
	else
	    return random()%DBMax;
}

void Simulate(int count, int pattern, Cache* cache_obj) {
    int hit = 0;
    int miss = 0;
    
    int frameid = random()%DBMax;
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
	        frameid = random()%DBMax;
	}
    }

    cout << "The hitting/missing ratio is: " << hit/miss << endl;
    return;
}
