#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>


Class ListNode {
    public:
        int FrameID;
        int Value;
        ListNode* Next;
        ListNode* Prev;
        ListNode(int x, int y) {
	    FrameID = x;
	    Value = y;
	    Next = NULL;
	    Prev = NULL;
        }
};

Class LRUListNode:ListNode {
	
};

Class LFUListNode:ListNode {
    public:
        FreqNode* FreqNode;
        LFUListNode(int x, int y) {
    	    FrameID = x;
    	    Value = y;
    	    Next = NULL;
    	    Prev = NULL;
    	    FreqNode = NULL;
        }
};

Class FreqNode {
    public:
        int Freq;
        FreqNode* Next;
        FreqNode* Prev;
        LFUListNode* HeadNode;
        //LFUListNode* tail;    
};


Class Cache {
    public:
        int Capacity;
        int Free;
        unordered_map<int, ListNode*> Hash;

        Cache(int x): Capacity(x),Free(x){}
        void PutNode(int FrameID, int value_t){}=0;
        bool GetNode(int FrameID, int& result){}=0;
};

Class LRUCache:Cache {
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
};


Class LFUCache:Cache {
    public:
        unordered_map<int, LFUListNode*> LFUHash;
        FreqNode* FreqHead;
    
        LFUCache(int x) {
    	    Capacity = x;
    	    Free = x;
    	    FreqHead = NULL;
        }
     private:
         void DeleteNode();
         void UpdateNode(LFUListNode*& listnode);
         void InsertNode(LFUListNode*& listnode, FreqNode*& freqnode);
         FreqNode* IsolateNode(LFUListNode*& listnode);
};
