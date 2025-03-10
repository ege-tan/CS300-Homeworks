#include <iostream>
#include <fstream>
#include "HashTable.h"

#define W '1'
#define B '0'

using namespace std;

string convert_to_rle(const string & concfile){
    string rle {};
    int count = 1;
    char current;
    current = concfile.at(0);
    for(int i = 1 ; i< concfile.size() ;i++){
        if (concfile[i] == current){
            count++;
        }
        else{
            if (current == B){
                rle = rle + to_string(count) + 'B';
            }
            else{
                rle = rle + to_string(count) + 'W';
            }
            current = concfile[i];
            count = 1;
        }
    }
    if (current == B){
        rle = rle + to_string(count) + 'B';
    }
    else{
        rle = rle + to_string(count) + 'W';
    }
    return rle;
}

int main() {
    HashTable hashTable;

    while (true) {
        cout << "Enter image number to insert into the hash table (or 'query' to continue): ";
        string input;
        cin >> input;
        cout << endl;
        if (input == "query") {
            break;
        }

        ifstream file("images/image" + input + ".txt");
        if (!file) {
            cout << "Cannot open the file!" << endl;
            continue;
        }

        string line, concfile;
        while (getline(file, line)) {
            concfile += line;
        }
        string rle = convert_to_rle(concfile);
        hashTable.insert(rle);
        cout << "Image " << input << " inserted into the hash table." << endl;
    }

    while (true) {
        cout << "Enter image number to query (or 'exit' to quit): ";
        string input;
        cin >> input;
        if (input == "exit") {
            cout << "Exiting the program!" << endl;
            break;
        }

        ifstream file("images/query" + input + ".txt");
        if (!file) {
            cout << "Cannot open the file!" << endl;
            continue;
        }

        string line, concfile;
        while (getline(file, line)) {
            concfile += line;
        }
        string rle = convert_to_rle(concfile);

        if (hashTable.find(rle) == "ITEM_NOT_FOUND") {
            cout << "No match for the image with encoding: " << rle << endl;
        } else {
            cout << "RLE String for query" << input << ".txt found in hash table." << endl;
            cout << "Decoded content: " << endl;
            cout << concfile << endl;
        }
    }
    return 0;
}