#include "cache.h" 
#include "utility.h"

extern vector<vector<int>> DB;

/* Implement O(1) access LFU cache, using two types of node, frequency node and list node,
   refer to paper: An O(1) algorithm for implementing the LFU cache eviction scheme
   Prof. Ketan Shah Anirban Mitra Dhruv Matani, August 16, 2010 */

/* put a new node in frequecy 1 queue, and update the hash table */
void LFUCache::PutNode(int frameid, int value) {
    LFUListNode* listnode = new LFUListNode(frameid, value);
    if(!Free)
        DeleteNode();

    /* case 1: if Head is null || case 2: if Head->next is not the frequency 1 node*/
    if(!(FreqHead->Next) || FreqHead->Next->Freq != 1) {
	FreqNode* nextfreq = new FreqNode(1);
	/* connect frequency node */
	if(FreqHead->Next) {
	    nextfreq->Next =  FreqHead->Next;
	    FreqHead->Next->Prev = nextfreq;
	    }
	FreqHead->Next = nextfreq;
	nextfreq->Prev = FreqHead;
	InsertNode(listnode, nextfreq);
        }
        /* case 3: if Head->next is the frequency 1 node*/
        else
	    InsertNode(listnode, FreqHead->Next);
	    
	/* insert to hash table */
	LFUHash.insert({frameid, listnode});
	Free++;
	return;
}
    
/* get the frame from the existing cache, return NULL if it is missing */
bool LFUCache::GetNode(int frameid, int& result) {
    /* if hit some node*/
    if (LFUHash.find(frameid)!=LFUHash.end()) {
        /* update the cache */
        LFUListNode* listnode = LFUHash[frameid]; /* hit LFU list node */
	UpdateNode(listnode);
	result = listnode->Value;
	return true;
    }

    /* if not hit any node */
    else {
        PutNode(frameid, DB[frameid][VALUE]);
        return false;
    }
}

/* Delete the least frequency node */
void LFUCache::DeleteNode(){
    if(!FreqHead->Next)
	return;
    else {
    	LFUListNode* listnode = FreqHead->Next->HeadNode;
    	IsolateNode(listnode);
    	delete(LFUHash[listnode->FrameID]);
    	LFUHash.erase(listnode->FrameID);
    	delete(listnode);  	
    	Free--;
    }
    return;
}

/* update node to next frequency */
void LFUCache::UpdateNode(LFUListNode*& listnode) {
	FreqNode* freqnode = listnode->FreqNodeQ; /* current frequency node */
        int frequency = freqnode->Freq; /* current frequency */
        
        /* if listnode is the node node in current frequency queue, PrevFreq
        is the previous frequency node, otherwise, is the current one. */
        FreqNode* prevfreq = IsolateNode(listnode); 
        FreqNode* nextfreq;

        /* case 1, the next FreqNode is null */
        if(!freqnode->Next) 
	    nextfreq = new FreqNode(frequency+1);

        /* case 2, the next FreqNode exists, and it is continuous */
        else if (frequency + 1 == freqnode->Next->Freq) 
	    nextfreq = freqnode->Next;

	/* case 3, the next FreqNode exists, and it is not continuous */
	else
	    FreqNode* nextfreq = new FreqNode(frequency+1);
	    
	/* connect the frequency node */
	 prevfreq->Next = nextfreq;
	 nextfreq->Prev = prevfreq;

	 /* insert the list node */
	 InsertNode(listnode, nextfreq);
	 return;
	
}


/* insert the listnode into frequency queque */
void LFUCache::InsertNode(LFUListNode*& listnode, FreqNode*& freqnode) {
    /*case 1: if freqnode queue is empty */
    if (!freqnode->HeadNode) {
	freqnode->HeadNode = listnode;
	listnode->FreqNodeQ = freqnode;
    }
    /* case 2: if freqnode queue is not empty, insert listnode at the head */
    else {
	LFUListNode* head_temp = freqnode->HeadNode;
	freqnode->HeadNode = listnode;
	listnode->Next = head_temp;
	head_temp->Prev = listnode;
	listnode->FreqNodeQ = freqnode;
    }
    return;
}


/* isolate the node, i.e. delete the list node in the current frequence queue, 
   the input listnode will be clean, i.e. next, prev, freq_node are reset to be null
   return the current frequence node if the queue is not empty,
   otherwise, delete the current frequence node, and return the previous frequence node */

FreqNode* LFUCache::IsolateNode(LFUListNode*& listnode) {

    FreqNode* result = listnode->FreqNodeQ;
    
    /* case 1, this is the only node in current frequence queue */
    if(!listnode->Prev && !listnode->Next) {
	result = listnode->FreqNodeQ->Prev;

	/* connect the frequency list */
	result->Next = listnode->FreqNodeQ->Next;
	listnode->FreqNodeQ->Next->Prev = result;

	/* delete the list node and frequence node */
	delete(listnode->FreqNodeQ);
	/* clean up the list node */
	listnode->FreqNodeQ = NULL;
    }
    
    /* case 2, this is not the only node */
    else {
    	/* listnode is at the end */
	if(!listnode->Next) {
		listnode->Prev->Next = NULL;
		listnode->Prev = NULL;
		listnode->FreqNodeQ = NULL;
	}
	/* listnode is at the head */
	else if (!listnode->Prev){
		listnode->FreqNodeQ->HeadNode = listnode->Next;
		listnode->Next->Prev = NULL;
		listnode->Next = NULL;
		listnode->FreqNodeQ = NULL;
	}
	/* listnode is in the middle */
	else{
		listnode->Prev->Next = listnode->Next;
		listnode->Next->Prev = listnode->Prev;
		listnode->Next = NULL;
		listnode->Prev = NULL;
		listnode->FreqNodeQ = NULL;
	}
    }
    return result;
}
