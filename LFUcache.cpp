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
        
    /* case 1: if Head->next is the frequency 1 node*/
    if (FreqHead->Next && FreqHead->Next->Freq == 1) {
		//cout<<listnode<<endl;
		InsertNode(listnode, FreqHead->Next);
	}
		
    /* case 2: if Head is null || case 3: if Head->next is not the frequency 1 node*/
    else {
	    FreqNode* nextfreq = new FreqNode(1);
	    /* connect frequency node */
	    if(FreqHead->Next) {
	        nextfreq->Next =  FreqHead->Next;
	        FreqHead->Next->Prev = nextfreq;
	    }
	    FreqHead->Next = nextfreq;
	    nextfreq->Prev = FreqHead;
	    InsertNode(listnode, nextfreq);
	    cout<<listnode<<endl;
    }    
	/* insert to hash table */
	LFUHash.insert({frameid, listnode});
	Free--;
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
    	IsolateNode(listnode, listnode->FreqNodeQ->Next);
    	//delete(LFUHash[listnode->FrameID]);
    	LFUHash.erase(listnode->FrameID);
    	delete(listnode);  	
    	Free++;
    }
    return;
}

/* update node to next frequency */
void LFUCache::UpdateNode(LFUListNode*& listnode) {
    	FreqNode* freqnode = listnode->FreqNodeQ; /* current frequency node */
        int frequency = freqnode->Freq; /* current frequency */
        
        /* if listnode is the only node in current frequency queue, PrevFreq
        is the previous frequency node, otherwise, is the current one. */
        FreqNode* nextfreq;

        /* case 1, the next FreqNode exists, and it is continuous */
        if (freqnode->Next && frequency + 1 == freqnode->Next->Freq) 
	    nextfreq = freqnode->Next;
	    else {
        /* case 2, the next FreqNode is null */
	/* case 3, the next FreqNode exists, and it is not continuous */
	     nextfreq = new FreqNode(frequency+1);
	    
	   nextfreq->Next = listnode->FreqNodeQ->Next;
	   if(listnode->FreqNodeQ->Next)
		listnode->FreqNodeQ->Next->Prev = nextfreq;
		}
	    FreqNode* prevfreq = IsolateNode(listnode, nextfreq); 
	    
	/* connect the frequency node */
	 prevfreq->Next = nextfreq;
	 nextfreq->Prev = prevfreq;

	 /* insert the list node */
	 InsertNode(listnode, nextfreq);
	 return;
	
}


/* insert the listnode into frequency queque */
void LFUCache::InsertNode(LFUListNode*& listnode, FreqNode*& freqnode) {
	/* case 1: if freqnode queue is not empty, insert listnode at the head */
    if (freqnode->HeadNode) {
	LFUListNode* head_temp = freqnode->HeadNode;
	freqnode->HeadNode = listnode;
	listnode->Next = head_temp;
	head_temp->Prev = listnode;
	listnode->FreqNodeQ = freqnode;
    }
    /*case 2: if freqnode queue is empty */
    else {
	freqnode->HeadNode = listnode;
	listnode->FreqNodeQ = freqnode;
    }
   
    return;
}


/* isolate the node, i.e. delete the list node in the current frequence queue, 
   the input listnode will be clean, i.e. next, prev, freq_node are reset to be null
   return the current frequence node if the queue is not empty,
   otherwise, delete the current frequence node, and return the previous frequence node */

FreqNode* LFUCache::IsolateNode(LFUListNode*& listnode, FreqNode*& nextfreq) {

    FreqNode* result = listnode->FreqNodeQ;
    
    /* case 1, this is the only node in current frequence queue */
    if(!listnode->Prev && !listnode->Next) {
	result = listnode->FreqNodeQ->Prev;

	/* connect the frequency list */
	//result->Next = listnode->FreqNodeQ->Next;
	result->Next = nextfreq;
	//if(listnode->FreqNodeQ->Next)
	  //  listnode->FreqNodeQ->Next->Prev = result;
	  if(nextfreq)
	  nextfreq->Prev = result;
		

	/* delete the frequence node */
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
