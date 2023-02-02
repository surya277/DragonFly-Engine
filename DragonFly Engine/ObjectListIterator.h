#pragma once

#include "Object.h"
#include "ObjectList.h"

namespace df {

	class ObjectList;

	class ObjectListIterator
	{
	private:
		ObjectListIterator();				// Given List when created
		int m_index;						// Index to list
		const ObjectList* m_p_list;			// List

	public:
		// Create iterator over given list
		ObjectListIterator(const ObjectList* p_l);

		void first();						// Set iterator to first item in list
		void next();						// Set iterator to next item in list
		bool isDone() const;				// Return true if at end of list

		// Return pointer to current Object, Null if done/empty
		Object* currentObject() const;
	};
}

