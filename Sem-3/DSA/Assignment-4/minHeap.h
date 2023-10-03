#ifndef MINHEAP_H
#define MINHEAP_H

#include "graph.h"
#include <queue>

// Class describing a MinHeap Node, as in the question.
class MinHeapNode{
public:
	Person* m_person;
	EVENT m_event;
	int m_timeStamp;

	// Constructor
	MinHeapNode(Person* person, EVENT event, int timeStamp):
		m_person(person),
		m_event(event),
		m_timeStamp(timeStamp)
	{
		if(event == EVENT::INFECTION)
			m_person->m_infection_TimeStamp = timeStamp;
		else
			m_person->m_recovery_TimeStamp = timeStamp;
	}
};

// Operator overloading for comparisions
bool operator> (const MinHeapNode& node1, const MinHeapNode node2){
	return node1.m_timeStamp > node2.m_timeStamp;
}
bool operator< (const MinHeapNode& node1, const MinHeapNode node2){
	return node1.m_timeStamp < node2.m_timeStamp;
}
bool operator== (const MinHeapNode& node1, const MinHeapNode node2){
	return node1.m_timeStamp == node2.m_timeStamp;
}

// Using the standard library's priority queue, MinHeap data structure can hence be easily used.
// Last template parameter lets us set the comparing function(Hencce getting MinHeap, not MaxHeap)
using MinHeap = std::priority_queue<MinHeapNode, std::vector<MinHeapNode>, std::greater<MinHeapNode>>;

#endif