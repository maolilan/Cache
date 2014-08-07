include "cache.h"

//get the frame from the existing cache, return NULL if it is missing
bool LRUCache:Get(int FrameID, int& result) {
    if (Hash.find(FrameID)!=Hash.end()) {
	//update the cache
	ListNode* temp = Hash[FrameID];
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->next = end->next;
	temp->prev = end;
	end->next = temp;
	end = temp;

	free --;
	result = Hash[FrameID]->value; 

	return true;
    }
    else
	return false;
}

/* put a new frame
   idea, use a ring double linked list:
   A<->B<->C<->D<->A, move head and end pointer.
   process:
   if head is null, creat a new node, and set head,end;
   if free is not 0, creat a new node, and put it in the end;
   if free is 0, put new value in the head, and move the head/end pointer;
*/

void LRUCache:Put(int FrameID, int value_t) {

   if (!free) {
	head->value = value_t;
	//creat a ring double linked list
	if(!end->next) {
	    end->next = head;
	    head->prev = end;
	}
	head = head->next;
	end = end->next;
	free--;
	return;
   }
    
    if(!head) {
	head = new ListNode(FrameID, 1, value_t);
	end = head;
	return;
    }

    ListNode* temp = new ListNode(FrameID, 1, value_t);
    end->next = temp;
    temp->prev = end;
    temp->next = null;
    end = temp;
    free--;
    return;
	
}