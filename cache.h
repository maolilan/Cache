#ifndef _CACHE_H
#define _CACHE_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class ListNode {
    public:
        int FrameID;
        int Value;

};

class LRUListNode:public ListNode {
    public:
	LRUListNode* Prev;
	LRUListNode* Next;
        LFUListNode(int x, int y) {
    	    FrameID = x;
    	    Value = y;
    	    Next = NULL;
    	    Prev = NULL;
        }	
};

class FreqNode;

class LFUListNode:public ListNode {
    public:
        FreqNode* FreqNodeQ;
	LFUListNode* Next;
	LFUListNode* Prev;
        LFUListNode(int x, int y) {
    	    FrameID = x;
    	    Value = y;
    	    Next = NULL;
    	    Prev = NULL;
    	    FreqNodeQ = NULL;
        }
};

class FreqNode {
    public:
        int Freq;
        FreqNode* Next;
        FreqNode* Prev;
        LFUListNode* HeadNode;
        //LFUListNode* tail;  
	FreqNode(int x) {
	    Freq = x;
	    Next = NULL;
	    Prev = NULL;
	    HeadNode = NULL;
	}  
};


class Cache {
    public:
        int Capacity;
        int Free;

        virtual void PutNode(int frameid, int value){return;};
        virtual bool GetNode(int frameid, int& result){return true;};
};

class LRUCache:public Cache {
    public:
        LRUListNode* Head;
        LRUListNode* End;
        unordered_map<int, LRUListNode*> LRUHash;
    
        LRUCache(int x) {
    	    Capacity = x;
    	    Free = x;
    	    Head = NULL;
    	    End = NULL;
        }
    void PutNode(int frameid, int value);
    bool GetNode(int frameid, int& result);
};


class LFUCache:public Cache {
    public:
        unordered_map<int, LFUListNode*> LFUHash;
        FreqNode* FreqHead;
    
        LFUCache(int x) {
    	    Capacity = x;
    	    Free = x;
    	    FreqHead = new FreqNode(0);
        }
        void PutNode(int frameid, int value);
        bool GetNode(int frameid, int& result);
    private:
        void DeleteNode();
        void UpdateNode(LFUListNode*& listnode);
        void InsertNode(LFUListNode*& listnode, FreqNode*& freqnode);
        FreqNode* IsolateNode(LFUListNode*& listnode);
};
#endif
