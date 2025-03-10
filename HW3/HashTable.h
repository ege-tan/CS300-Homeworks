//
// Created by Ege Tan on 7.12.2024.
//
#ifndef HW3_HASHTABLE_H
#define HW3_HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

class HashTable {

public:
    exception HashTable(const string & notFound = "ITEM NOT FOUND" , int size = 101);
    const string & find( const string & x ) const;
    void insert( const string & x );
    void remove( const string & x );
    void makeEmpty( );
    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry {
        string element;
        EntryType info;
        HashEntry(const string & e = string(), EntryType i = EMPTY )
        :element( e ), info( i ) {}
    };
    vector<HashEntry> array;
    int currentSize;
    int nextPrime( int );
    bool isPrime( int );
    const string ITEM_NOT_FOUND;
    bool isActive( int currentPos ) const;
    int findPos( const string & x ) const;
    void rehash();
};

#endif //HW3_HASHTABLE_H
