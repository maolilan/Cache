#include "cache.h" 
#include "utility.h"

extern vector<vector<int>> DB;

/* when hit the cache, update the position of the node */
void LRUCache::UpdateNode(LRUListNode*& listnode) {
    /* this is the tail */
    if(listnode == End);
    /* this is the head node */
    else if(!listnode->Prev) {
	Head = listnode->Next;
	End->Next = listnode;
	listnode->Prev = End;
	listnode->Next = NULL;
	End = listnode;
    }
    /* this is the middle node */
    else {
	listnode->Prev->Next = listnode->Next;
	listnode->Next->Prev = listnode->Prev;
	listnode->Next = End->Next;
	if(End->Next) End->Next->Prev = listnode;
	listnode->Prev = End;
	End->Next = listnode;
	End = listnode;
    } 
    return;
}

/* get the value from the existing cache, if hit, return true,
 * if not hit, get the value from DB, and return false */
bool LRUCache::GetNode(int frameid, int& result) {
    /* if hit the cache */
    if (LRUHash.find(frameid)!= LRUHash.end()) {
	/* update the cache */
	LRUListNode* listnode = LRUHash[frameid];
	result = LRUHash[frameid]->Value; 
	UpdateNode(listnode);
	return true;
    }
    else {
	result = DB[frameid][VALUE];
	PutNode(frameid, result);
	return false;
    }
}

/* put a new frame
   idea, use a ring double linked list:
   A<->B<->C<->D<->A, move head and end pointer.
   process:
   if head is null, creat a new node, and set head,end;
   if free is not 0, creat a new node, and put it in the end;
   if free is 0, put new value in the head, and move the head/end pointer;
*/

void LRUCache::PutNode(int frameid, int value) {
    /* if there is no space */
   if (!Free) {
	/* update the hash table */
	LRUHash.erase(Head->FrameID);
        Head->Value = value;
        Head->FrameID = frameid;
	    /* creat a ring double linked list */
	if(!End->Next) {
	    End->Next = Head;
	    Head->Prev = End;
	}
	End = Head;
	Head = Head->Next;
   }
    
    else {
        /* if this is the first element */
        if(!Head) {
	    Head = new LRUListNode(frameid, value);
	    End = Head;
        }
        else {
	    LRUListNode* listnode = new LRUListNode(frameid, value);
            End->Next = listnode;
            listnode->Prev = End;
            End = listnode;
        }
        Free--;
    }
     
     /* update the hash table */
     LRUHash.insert({frameid, End});
     return;
}
