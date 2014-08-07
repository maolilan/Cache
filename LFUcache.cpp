include "cache.h"

//get the frame from the existing cache, return NULL if it is missing
bool LFUCache:Get(int FrameID, int& result) {
    
    if (Hash.find(FrameId)!=Hash.end()) {

        /* update the cache */
        LFUListNode* list_temp = Hash[FrameId]; /* temp LFU list node */
	FreqNode* freq_temp = temp->freq_node; /* temp frequency node */
        int frequency = freq_temp->freq; /* current frequency */
	

        /* case 1, the next FreqNode is null */
        if(!freq_temp->next) {
	    FreqNode* PrevFreq = DeleteNode(list_temp);
	    FreqNode* NextFreq = new FreqNode(frequency+1);

	    /* connect the frequency node */
	    PrevFreq->next = NextFreq;
	    NextFreq->prev = PrevFreq;

	    /* insert the list node */
	    NextFreq->head = list_temp;
	    list_temp->freq_node = NextFreq;
	
        } // case 1

        /* case 2, the next FreqNode exists, and it is continuous */
        else if (frequency + 1 == freq_temp->next->freq) {
	    FreqNode* NextFreq = freq_temp->next;
	    FreqNode* PrevFreq = DeleteNode(temp);
	    
	    /* connect the frequency node */
	    PrevFreq->next = NextFreq;
	    freq_temp->prev = PrevFreq;

	    /* insert the list node */
	    LFUListNode* head_temp = NextFreq->head;
	    NextFreq->head = list_temp;
	    list_temp->next = head_temp;
	    list_temp->freq_node = NextFreq;
	    head_temp->prev = temp;
        } //case 2

	/* case 3, the next FreqNode exists, and it is not continuous */
	else {
	    FreqNode* NextFreq = new FreqNode(frequency+1);

	    /* connect the new frequency node with the next one */
	    NextFreq->next = freq_temp->next;
	    freq_temp->next->prev = NextFreq; 
	    FreqNode* PrevFreq = DeleteNode(temp);

	    /* connect the frequency node */
	    PrevFreq->next = NextFreq;
	    NextFreq->prev = PrevFreq;

	    /* insert the list node */
	    NextFreq->head = list_temp;
	    list_temp->freq_node = NextFreq;

	} //case 3

	result = list_temp->value;
	return true;

    }// if hit some node

    /* if not hit any node */
    else {
	/* case 1: if Head is null || case 2: if Head->next is not the frequency 1 node*/
	if(!(Head->next) || Head->next->freq != 1) {

	    FreqNode* NextFreq = new FreqNode(1);

	    /* connect frequency noed */
	    if(Head->next) {
		NextFreq->next =  Head->next;
		Head->next->prev = NextFreq;
	    }

	    Head->next = NextFreq;
	    NextFreq->prev = Head;
	    InsertNodeEmp(list_temp, NextFreq);
	    
	}

	/* case 3: if Head->next is the frequency 1 node*/
	else
	    InsertNode(list_temp, Head->next);	    
	
    }//if not hit any node
    
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
	
    }
}