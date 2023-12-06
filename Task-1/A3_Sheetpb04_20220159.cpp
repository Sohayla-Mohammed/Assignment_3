// File: A3_SheetPb04_20220159.cpp
// Author: Sohayla Mohammed Ahmed
// Section: S(2)
// ID: 20220159



#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Set {
private:
    T* items;
    int size;
    int capacity;

public:
    Set() : size(0), capacity(15) {
        items = new T[capacity];
    }

    ~Set() {
        delete[] items;
    }

    void add(const T& item) {
        if (!contains(item)) {
            if (size == capacity) {
                // Resize the array if needed
                capacity *= 2;
                T* newItems = new T[capacity];
                for (int i = 0; i < size; ++i) {
                    newItems[i] = items[i];
                }
                delete[] items;
                items = newItems;
            }
            items[size++] = item;
        }
    }

    void remove(const T& item) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (items[i] == item) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // Shift elements to fill the gap
            for (int i = index; i < size - 1; ++i) {
                items[i] = items[i + 1];
            }
            --size;
        }
    }

    int getSize() const {
        return size;
    }

    bool contains(const T& item) const {
        for (int i = 0; i < size; ++i) {
            if (items[i] == item) {
                return true;
            }
        }
        return false;
    }

    T* toArray() const {
        T* arrayCopy = new T[size];
        for (int i = 0; i < size; ++i) {
            arrayCopy[i] = items[i];
        }
        return arrayCopy;
    }

    bool operator==(const Set<T>& other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; ++i) {
            if (items[i] != other.items[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Set<T>& other) const {
        return !(*this == other);
    }
};


int main() {
    Set<int> intSet;
    intSet.add(1);
    intSet.add(2);
    intSet.add(3);
    intSet.add(2);  // Should not add again

    cout << "Size of intSet: " << intSet.getSize() << endl;

    // Adding a new item to the set (4)
    intSet.add(4);

    cout << "Size of intSet after adding 4: " << intSet.getSize() << endl;

    // Removing an item from the set (2)
    intSet.remove(2);

    cout << "Size of intSet after removing 2: " << intSet.getSize() << endl;

    // Determining if an item is a member of the set (3)
    if (intSet.contains(3)) {
        cout << "3 is a member of intSet." << endl;
    } else {
        cout << "3 is not a member of intSet." << endl;
    }

    // Returning a pointer to a dynamically created array
    int* intArray = intSet.toArray();
    cout << "Items in intSet: ";
    for (int i = 0; i < intSet.getSize(); ++i) {
        cout << intArray[i] << " ";
    }
    cout << endl;

    // deallocate the memory
    delete[] intArray;

    Set<std::string> stringSet;
    stringSet.add("apple");
    stringSet.add("banana");
    stringSet.add("apple");  // Should not add again

    cout << "Size of stringSet: " << stringSet.getSize() << endl;

    return 0;
}
