#include "cache.h" 
#include "utility.h"

extern vector<vector<int>> DB;

/* get the value from the existing cache, if hit, return true,
 * if not hit, get the value from DB, and return false */
bool LRUCache::GetNode(int frameid, int& result) {
	/* if hit the cache */
    if (LRUHash.find(frameid)!= LRUHash.end()) {
	/* update the cache */
	LRUListNode* listnode = LRUHash[frameid];
	listnode->Prev->Next = listnode->Next;
	listnode->Next->Prev = listnode->Prev;
	listnode->Next = End->Next;
	listnode->Prev = End;
	End->Next = listnode;
	End = listnode;

	Free --;
	result = LRUHash[frameid]->Value; 

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
        Head->Value = value;
	    /* creat a ring double linked list */
	    if(!End->Next) {
	        End->Next = Head;
	        Head->Prev = End;
	    }
	    Head = Head->Next;
	    End = End->Next;
	    return;
   }
    
    /* if this is the first element */
    if(!Head) {
	    Head = new LRUListNode(frameid, value);
	end = head;
	return;
    }

    ListNode* temp = new ListNode(frameid, value);
    end->next = temp;
    temp->prev = end;
    temp->next = null;
    end = temp;
    free--;
    return;
	
}
