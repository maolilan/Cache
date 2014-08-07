include "cache.h"

/* Implement O(1) access LFU cache, using two types of node, frequency node and list node,
   refer to paper: An O(1) algorithm for implementing the LFU cache eviction scheme
   Prof. Ketan Shah Anirban Mitra Dhruv Matani, August 16, 2010 */

/* update node to next frequency */
void LFUCache:UpdateNode(LFUListNode*& listnode) {
	FreqNode* freqnode = listnode->freq_node; /* current frequency node */
        int frequency = freqnode->freq; /* current frequency */
        
        /* if listnode is the node node in current frequency queue, PrevFreq
        is the previous frequency node, otherwise, is the current one. */
        FreqNode* PrevFreq = DeleteNode(listnode); 
        FreqNode* NextFreq;

        /* case 1, the next FreqNode is null */
        if(!freqnode->next) 
	    FreqNode* NextFreq = new FreqNode(frequency+1);

        /* case 2, the next FreqNode exists, and it is continuous */
        else if (frequency + 1 == freqnode->next->freq) 
	    FreqNode* NextFreq = freqnode->next;

	/* case 3, the next FreqNode exists, and it is not continuous */
	else
	    FreqNode* NextFreq = new FreqNode(frequency+1);
	    
	/* connect the frequency node */
	 PrevFreq->next = NextFreq;
	 NextFreq->prev = PrevFreq;

	 /* insert the list node */
	 InsertNode(listnode, NextFreq);
	
}


/* insert the listnode into frequency queque */
void LFUCache:InsertNode(LFUListNode*& listnode, FreqNode*& freqnode) {
    /*case 1: if freqnode queue is empty */
    if (!freqnode->head) {
	freqnode->head = listnode;
	listnode->freq_node = freqnode;
    }
    /* case 2: if freqnode queue is not empty, insert listnode at the head */
    else {
	LFUListNode* head_temp = freqnode->head;
	freqnode->head = listnode;
	listnode->next = head_temp;
	head_temp->prev = listnode;
	listnode->freq_node = freqnode;
    }
	
}

/* put a new node in frequecy 1 queue */
PutNode(LFUListNode*& listnode) {
    /* case 1: if Head is null || case 2: if Head->next is not the frequency 1 node*/
    if(!(Head->next) || Head->next->freq != 1) {
	FreqNode* NextFreq = new FreqNode(1);
	/* connect frequency node */
	if(Head->next) {
	    NextFreq->next =  Head->next;
	    Head->next->prev = NextFreq;
	 }
	 Head->next = NextFreq;
	 NextFreq->prev = Head;
	 InsertNode(listnode, NextFreq);
    }
    /* case 3: if Head->next is the frequency 1 node*/
    else
	InsertNode(listnode, Head->next);	    
}
    
//get the frame from the existing cache, return NULL if it is missing
bool LFUCache:GetNode(int FrameID, int& result) {
    /* if hit some node*/
    if (Hash.find(FrameId)!=Hash.end()) {
        /* update the cache */
        LFUListNode* list_temp = Hash[FrameId]; /* hit LFU list node */
	UpdateNode(list_temp);
	result = list_temp->value;
	return true;
    }

    /* if not hit any node */
    else
        PutNode(list_temp);
}


/* delete the list node in the current frequence queue, the input listnode
   will be clean, i.e. next, prev, freq_node are reset to be null
   return the current frequence node if the queue is not empty,
   otherwise, delete the current frequence node, and return the previous frequence node */

FreqNode* LFUCache:DeleteNode(LFUListNode*& listnode) {

    FreqNode* result = listnode->freq_node;
    
    /* case 1, this is the only node in current frequence queue */
    if(!listnode->prev && !listnode->next) {
	result = listnode->freq_node->prev;

	/* connect the frequency list */
	result->next = listnode->freq_node->next;
	listnode->freq_node->next->prev = result;

	/* delete the list node and frequence node */
	delete(listnode->freq_node);
	/* clean up the list node */
	listnode->freq_node = NULL;
    }
    
    /* case 2, this is not the only node */
    else {
    	/* listnode is at the end */
	if(!listnode->next) {
		listnode->prev->next = null;
		listnode->prev = null;
		listnode->freq_node = null;
	}
	/* listnode is at the head */
	else if (!listnode->prev){
		listnode->freq_node->head = listnode->next;
		listnode->next->prev = null;
		listnode->next = null;
		listnode->freq_node = null
	}
	/* listnode is in the middle */
	else{
		listnode->prev->next = listnode->next;
		listnode->next->prev = listnode->prev;
		listnode->next = null;
		listnode->prev = null;
		listnode->freq_node = null;
	}
    }
}
