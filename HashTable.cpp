#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
    public:
        double loadFactorThreshold = 0.8;  // Threshold for load factor
        int capacity;                      // Size of the hash table
        int elementCount = 0;              // Number of elements in the hash table
        std::vector<int> hashTable;        // Vector to store hash table elements

        HashTable(int initialCapacity) {
            capacity = initialCapacity;
            hashTable.resize(capacity, -1);  // Initialize table with -1 (empty slots)
        }

        // Function to insert an element into the hash table
        void insert(int value) {
            resizeIfNeeded();  // Check if resizing is required
            int position = probeForInsert(value);
            
            if (position == -1) {
                cout << "Max probing limit reached!" << endl;
                return;
            } else if (position == -2) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }

            hashTable[position] = value;  // Insert value at the found position
            elementCount++;
        }

        // Function to remove an element from the hash table
        void remove(int value) {
            int position = probeForSearch(value);
            
            if (position == -1) {
                cout << "Element not found" << endl;
                return;
            }
            
            hashTable[position] = -1;  // Mark slot as empty
            elementCount--;
        }

        // Function to search for an element in the hash table
        int search(int value) {
            return probeForSearch(value);  // Return the position or -1 if not found
        }

        // Function to print the hash table
        void printTable() {
            for (const auto& entry : hashTable) {
                if (entry == -1) {
                    cout << "- ";
                } else {
                    cout << entry << " ";
                }
            }
            cout << '\n';
        }

    private:
        // Function to check and resize the table if needed
        void resizeIfNeeded() {
            if (static_cast<double>(elementCount) / capacity > loadFactorThreshold) {
                capacity = getNextPrimeSize();  // Find the next prime size
                std::vector<int> newHashTable(capacity, -1);  // Create a new table

                // Reinsert all existing elements into the resized table
                for (const auto& entry : hashTable) {
                    if (entry != -1) {
                        reinsertElement(entry, newHashTable);
                    }
                }

                hashTable.swap(newHashTable);  // Swap with the new resized table
            }
        }

        // Function to reinsert an element during resizing
        void reinsertElement(int value, std::vector<int>& newTable) {
            int newCapacity = newTable.size();
            int maxProbes = (newCapacity + 1) / 2;
            int position;

            for (int step = 0; step <= maxProbes; ++step) {
                position = (value % newCapacity + step * step) % newCapacity;
                if (newTable[position] == -1) {
                    newTable[position] = value;
                    break;
                }
            }
        }

        // Function to find the next prime size for resizing
        int getNextPrimeSize() {
            int newSize = capacity * 2 + 1;
            while (!isPrime(newSize)) {
                newSize++;
            }
            return newSize;
        }

        // Function to check if a number is prime
        bool isPrime(int number) {
            if (number < 2) return false;
            for (int i = 2, sqrtNum = sqrt(number); i <= sqrtNum; i++) {
                if (number % i == 0) return false;
            }
            return true;
        }

        // Function to handle quadratic probing for insertion
        int probeForInsert(int value) {
            int maxProbes = (capacity + 1) / 2;
            int position;

            for (int step = 0; step <= maxProbes; ++step) {
                position = (value % capacity + step * step) % capacity;
                if (hashTable[position] == -1) {
                    return position;  // Empty slot found
                } else if (hashTable[position] == value) {
                    return -2;  // Duplicate element found
                }
            }

            return -1;  // Probing limit reached
        }

        // Function to handle quadratic probing for searching
        int probeForSearch(int value) {
            int maxProbes = (capacity + 1) / 2;
            int position;

            for (int step = 0; step <= maxProbes; ++step) {
                position = (value % capacity + step * step) % capacity;
                if (hashTable[position] == -1) {
                    return -1;  // Element not found
                } else if (hashTable[position] == value) {
                    return position;  // Element found
                }
            }

            return -1;  // Element not found after probing
        }
};
