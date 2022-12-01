#include "DisjointSets.h"

DisjointSets::DisjointSets(const unsigned int numElements)
{
	m_sets.resize(numElements);
	for (unsigned int i = 0; i < numElements; i++)
		m_sets[i] = -1;

	m_numElements = numElements;
}

void DisjointSets::performUnion(const unsigned int setIndexOne, const unsigned int setIndexTwo)
{
	if ((setIndexOne >= m_sets.size()) || (setIndexTwo >= m_sets.size()))
		return;

	//Find the roots.
	int root1 = find(setIndexOne);
	int root2 = find(setIndexTwo);

	if (m_sets[root2] < m_sets[root1])
	{
		//Root 2 is deeper
		m_sets[root1] = root2;
	}
	else
	{
		//Update height if same
		if (m_sets[root1] == m_sets[root2])
			m_sets[root1]--;

		m_sets[root2] = root1;
	}

	m_numElements--;
}

int DisjointSets::find(const unsigned int index)
{
	if (index >= m_sets.size())
		return -1;

	if (m_sets[index] < 0)
		return index;
	else
		return m_sets[index] = find(m_sets[index]);
}

unsigned int DisjointSets::getSize() const
{
	return m_numElements;
}