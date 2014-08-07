#include <vector>
#include <iostream>
#include <map>
#include <string>


Class ListNode {
    int frameID;
    int freq;
    int value;
    ListNode* next;
    ListNode* prev;
    ListNode(int x, int y, int value_t) {
	frameID = x;
	freq = y;
	next = null;
	prev = null;
	value = value_t;
};

Class Cache {
    int capacity;
    int free;
    ListNode* head;
    ListNode* end;
    unordered_map<int, ListNode*> Hash;

    Cache(int x): capacity(x),free(x),head(null){}
    void Put(int FrameID, int value_t){}=0;
    bool Get(int FrameID, int& result){}=0;
}

Class LRUCache:Cache {

}


Class FreqNode {
    int freq;
    FreqNode* next;
    FreqNode* prev;
    LFUListNode* head;
    //LFUListNode* tail;    
}


Class LFUListNode {
    int frameID;
    int value;
    FreqNode* freq_node;
    LFUListNode* next;
    LFUListNode* prev; 
    
}

Class LFUCache:Cache {
    unordered_map<int, LFUListNode*> Hash;
    FreqNode* Head;
    
}