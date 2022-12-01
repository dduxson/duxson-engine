#pragma once
/*!********************************************************************
* File:	DisjointSets.h
*
* \brief	A Disjoint sets class.
* \details A Disjoint sets class works by
*			first setting all the elements to -1. A union can then
*			be achieved between two elements so they are connected.
*			We use the height heuristic here. The Find function
*			will find what root element an element belongs to.
* 			Adapted from the book Data structures and algorithm
*			anaylsis in Java.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include <vector>

class DisjointSets
{
public:
	/*!
	*	\brief	Constructor for disjoint sets.
	*	\param[in] numElements	The number of dijoint sets there
	*							should be.
	*/
	DisjointSets(const unsigned int numElements);

	/*!
	*	\brief	Perform a union between 2 disjoint sets.
	*	\param[in]	setIndexOne	The index of the first set.
	*	\param[in]  setIndexTwo	The index of the second set.
	*	\remark The height heuristic is used.
	*/
	void performUnion(const unsigned int setIndexOne, const unsigned int setIndexTwo);

	/*!
	*	\brief	Find the index of sets root. Perfoms path find with
	*			path compression.
	*	\param[in]	index	The index of the set you wish to find the root
	*						for.
	*	\remark  Returns -1 if the index supplied is invalid.
	*	\return	The index of the root of the set with the index supplied.
	*/
	int find(const unsigned int index);

	/*!
	* \brief	Returns the number of sets that are disjoint.
	* \return	The number of sets that are disjoint.
	*/
	unsigned int getSize() const;

private:
	std::vector<int>	m_sets;			///< The sets that are initially all disjoint.
	int					m_numElements;	///< The number of sets that are disjoint.
};