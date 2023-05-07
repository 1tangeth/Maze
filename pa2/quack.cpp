/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    n1 = 0;
    n2 = -1;
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::pushR(T newItem) {
    // adds newItem to the end of the vector
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */

    /**
     * Removes the object at the left of the Quack, and returns it to
     * the caller. You may assume that this function is only called
     * when the Quack is non-empty.
     *
     * To achieve amortized O(1) cost per operation, we will resize
     * the array downward at strategic points of the computation.
     * Specifically, suppose L is the index of the
     * leftmost data element in the quack.
     * If at any point the data will fit into array indices 0..L-1,
     * the array should be reinitialized to hold the data beginning
     * at index 0 and occupying the next num cells, where num is the
     * number of data elements in the structure.
     *
     * @return The item that used to be at the left of the Quack.
     */
template <class T>
T Quack<T>::popL() {
    T value = data[n1];
    n1++;
    if (n2 < n1) {
        data.clear();
        n2 = -1;
        n1 = 0;
    } else if ((n2 - n1) < (data.size() / 2)) {
        vector<T> new_data;
        for (int i = n1; i <= n2; i++) {
            new_data.push_back(data[i]);
        }
        data = new_data;
        n1 = 0;
        n2 = data.size() -1 ;
    }
    return value;
}



/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    T value = data.back();
    data.pop_back(); // shrinks vector by one
    n2--;
    
    if ((n2 - n1) < (data.size() / 2)) {
        vector<T> new_data;
        for (int i = n1; i <= n2; i++) {
            new_data.push_back(data[i]);
        }
        data = new_data;
        n1 = 0;
        n2 = data.size() -1 ;
    }
    return value;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    return data.front();
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    return data.back();
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    return data.empty();
}
