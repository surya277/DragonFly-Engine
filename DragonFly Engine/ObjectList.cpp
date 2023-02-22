#include "ObjectList.h"

namespace df {

	ObjectList::ObjectList() {
		m_count = 0;

	}

	// Insert object pointer into list
	int ObjectList::insert(Object *p_o) {
		if (m_count >= MAX_OBJECTS)
			return -1;
		m_p_obj[m_count] = p_o;
		m_count++;
		return 0;
	}

	// Remove Object pointer from list
	int ObjectList::remove(Object* p_o) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {
				m_p_obj[i] = m_p_obj[--m_count];
				return 0;
			}
		}
		return -1;
	}

	// Clear the list
	void ObjectList::clear() {
		m_count = 0;
	}

	// Return count of number of objects in list
	int ObjectList::getCount() const {
		return m_count;
	}

	// Return true if list is empty
	bool ObjectList::isEmpty() const {

		if (m_count==0)
			return true;

		return false;
	}
	
	// Return true if list is Full
	bool ObjectList::isFull() const {
		if (m_count >= 5000)
			return true;

		return false;
	}
}