//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Martin Pentrak <xpentr00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Pentrak
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
	m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
	Element_t *actP;
	while (m_pHead != NULL)
	{
		actP = m_pHead->pNext;
		delete m_pHead;
		m_pHead = actP;
	}

}

void PriorityQueue::Insert(int value)
{
	if (m_pHead == NULL)
	{
		m_pHead = new Element_t[2*sizeof(Element_t)];
		m_pHead->pNext = NULL;
		m_pHead->value = value;
	}
	else
	{
		if (m_pHead->value < value)
		{	
			Element_t *nextP;
			nextP = m_pHead;
			m_pHead = new Element_t[2 * sizeof(Element_t)];
			m_pHead->pNext = nextP;
			m_pHead->value = value;
		}
		else
		{
			Element_t *actP;
			for (actP = m_pHead; actP->pNext != NULL; actP = actP->pNext)
			{
				if (actP->pNext->value < value)
				{
					break;
				}
			}
			Element_t *nextP;
			nextP= actP->pNext;
			actP->pNext = new Element_t[2 * sizeof(Element_t)];
			actP->pNext->value = value;
			actP->pNext->pNext = nextP;
		}
	}
}

bool PriorityQueue::Remove(int value)
{
	if (m_pHead == NULL)
	{
		return false;

	}
	if (m_pHead->value == value)
	{
		Element_t *nextP;
		nextP = m_pHead->pNext;
		delete m_pHead;
		m_pHead = nextP;
		return true;
	}
	else
	{
		Element_t *actP;
		actP = m_pHead;

		for (actP; actP->pNext != NULL; actP = actP->pNext)
		{
			if (actP->pNext->value == value)
			{
				Element_t *nextP;
				nextP = actP->pNext->pNext;
				delete actP->pNext;
				actP->pNext = nextP;
				return true;
			}
		}
		return false;
	}
	
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
	if ((m_pHead == NULL) || (m_pHead->value==value))
	{
		return m_pHead;
	}
	else
	{
		Element_t *actP;
		actP = m_pHead;

		for (actP;actP->pNext!=NULL; actP=actP->pNext)
		{
			if (actP->pNext->value == value)
				return actP->pNext;
		}
		return actP->pNext;
	}
}

size_t PriorityQueue::Length()
{
	Element_t *actP;
	actP = m_pHead;
	int i;
	for (i=0; actP != NULL; i++)
	{
		actP = actP->pNext;
	}
	return i;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
	return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
