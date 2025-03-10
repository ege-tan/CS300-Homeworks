//
// Created by Ege Tan on 7.12.2024.
//
#include "HashTable.h"

HashTable::HashTable(const string & notFound, int size):ITEM_NOT_FOUND( notFound ), array( nextPrime( size )){
    makeEmpty();
}

int hashFunction(const string& rleString, int tableSize) {
    int asciiSum = 0;
    for (char ch : rleString) {
        asciiSum += static_cast<int>(ch);
    }
    return asciiSum % tableSize;
}

bool HashTable::isPrime(int n) {
    if( n == 2 || n == 3 )
        return true;
    if( n == 1 || n % 2 == 0 )
        return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

int HashTable::nextPrime( int n)
{
    if( n % 2 == 0 )
        n++;
    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}

bool HashTable::isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
}

int HashTable::findPos(const string & x) const {
    int i = 0;
    int p = hashFunction(x, array.size( )); // current position
    while( array[p].info != EMPTY && array[p].element != x ) {
        p += 1; // add the difference
        if( p >= array.size( ) ) p -= array.size( ); // perform the mod
    }
    return p;
}

const string &HashTable::find(const string &x) const {
    int pos = findPos(x);
    if (isActive(pos))
        return array[pos].element;
    return ITEM_NOT_FOUND;
}

void HashTable::insert(const string &x) {
    int pos = findPos(x);
    if (isActive(pos)) return;
    array[pos] = HashEntry(x, ACTIVE);

    if (++currentSize > array.size() / 2)
        rehash();
}

void HashTable::remove(const string &x) {
    int pos = findPos(x);
    if (isActive(pos))
        array[pos].info = DELETED;
}

void HashTable::makeEmpty() {
    for (auto &entry : array)
        entry.info = EMPTY;
}

void HashTable::rehash() {
    vector<HashEntry> oldArray = array;
    array.resize(nextPrime(2 * oldArray.size()));
    for (auto &entry : array)
        entry.info = EMPTY;

    currentSize = 0;
    for (auto &entry : oldArray)
        if (entry.info == ACTIVE)
            insert(entry.element);
}

