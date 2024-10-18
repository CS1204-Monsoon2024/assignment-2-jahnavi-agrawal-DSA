//#include "HashTable.cpp"
#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table; // The hash table
    int capacity;           // Current size of the table
    int size;               // Number of elements in the table
    const float loadFactorThreshold = 0.8; // Threshold for resizing

    // Hash function: h(k) = k % capacity
    int hash(int key) {
        return key % capacity;
    }

    // Quadratic probing sequence
    int probe(int hashIndex, int i) {
        return (hashIndex + i * i) % capacity;
    }

    // Check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        for (int i = 3; i * i <= num; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Find the next prime number greater than or equal to `n`
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Rehash all keys into a new table of larger size
    void resize() {
        int newCapacity = nextPrime(capacity * 2); // Double the size and find next prime
        std::vector<int> newTable(newCapacity, -1); // New hash table initialized with -1 (empty)

        for (int i = 0; i < capacity; ++i) {
            if (table[i] != -1) {
                int key = table[i];
                int hashIndex = key % newCapacity;
                int j = 0;
                while (newTable[probe(hashIndex, j)] != -1) {
                    j++;
                }
                newTable[probe(hashIndex, j)] = key; // Insert into new table
            }
        }

        table = newTable;
        capacity = newCapacity;
    }

public:
    // Constructor to initialize hash table with a given capacity
    HashTable(int initialCapacity) {
        capacity = nextPrime(initialCapacity);
        table.resize(capacity, -1); // Initialize table with -1 (indicating empty slots)
        size = 0;
    }

    // Insert key into hash table
    void insert(int key) {
        int hashIndex = hash(key);
        int i = 0;

        // Check for duplicate key
        while (table[probe(hashIndex, i)] != -1) {
            if (table[probe(hashIndex, i)] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
            if (i >= capacity) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }

        // Insert the key
        table[probe(hashIndex, i)] = key;
        size++;

        // Check load factor and resize if necessary
        if ((float)size / capacity > loadFactorThreshold) {
            resize();
        }
    }

    // Search for key in hash table and return its index
    int search(int key) {
        int hashIndex = hash(key);
        int i = 0;

        // Probe through the table
        while (table[probe(hashIndex, i)] != -1) {
            if (table[probe(hashIndex, i)] == key) {
                return probe(hashIndex, i);
            }
            i++;
            if (i >= capacity) {
                return -1;
            }
        }
        return -1;
    }

    // Remove key from hash table
    void remove(int key) {
        int hashIndex = search(key);
        if (hashIndex == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }

        table[hashIndex] = -1;
        size--;
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
