#include "ObjectListIterator.h"

namespace df{

	ObjectListIterator::ObjectListIterator() {

	}

	// Create List over given iterator
	ObjectListIterator::ObjectListIterator(const ObjectList* p_l) {
		m_p_list = p_l;
		first();
	}

	// Set iterator to first element
	void ObjectListIterator::first() {
		m_index = 0;
	}

	// Set iterator to next element
	void ObjectListIterator::next() {
		if (m_index < m_p_list->getCount())
			m_index++;
	}

	// Return true if at end of the list
	bool ObjectListIterator::isDone() const {
		return (m_index >= m_p_list->getCount());
	}


	// Return pointer to current object
	Object* ObjectListIterator::currentObject() const {
		if (isDone())
			return NULL;
		return m_p_list->m_p_obj[m_index];
	}
}
