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


void Simulate(int count, int pattern, Cach* cache_obj) {
    int hit = 0;
    int miss = 0;
    
    int frameid = random()%DBMax;
    int value_t = 0;
 

    for(int i=0; i<count; i++) {
	if(Read(frameid, value_t, cache_obj)) 
		hit++;
	else
		miss++;

	frameid = pattern1(frameid);
    }

    cout << "The hitting/missing ratio is: " << hit/miss << endl;
}