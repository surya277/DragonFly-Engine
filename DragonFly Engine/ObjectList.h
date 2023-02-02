#pragma once

#include "Object.h"
#include "ObjectListIterator.h"

const int MAX_OBJECTS = 5000;

namespace df {

	class ObjectListIterator;

	class ObjectList
	{
	private:
		int m_count;							// Count of objects in list
		Object* m_p_obj[MAX_OBJECTS];			// Array of pointers to the objects

	public:
		friend class ObjectListIterator;

		ObjectList();

		// Insert Object Pointer into List
		int insert(Object* p_o);
		
		// Remove Object pointer from List
		int remove(Object* p_o);

		// Clear the List
		void clear();

		// Return count of number of objects in list
		int getCount() const;

		// Return true if list is empty
		bool isEmpty() const;

		// Return ture if list is full
		bool isFull() const;
	};

}

