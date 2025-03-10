#include <iostream>
#include "Quadtree.h"
#include <fstream>
#include <sstream>

// Function to print the contents of a vector of strings
// Prints "<None>" if the vector is empty, otherwise prints elements separated by commas
void print(const vector<string> & vec,const string &key){
    static int call_count = 0;
    if (key=="city"){
        if (call_count != 0)
            cout << endl;
        cout << endl;
    }

    if (vec.empty()){
        cout<<"<None>";
    } else{
        for (int i = 0; i < vec.size(); ++i) {
            if (i == 0){
                cout<<vec[i];
                continue;
            }
            cout<<", "<<vec[i];
        }
    }
    if (key=="city")
        cout << endl;
    call_count++;
}

int main() {
    // Open the input file containing city data
    ifstream file("cities.txt");
    if (!file) {
        cout << "Cannot open the file!" << endl; // Check if the file was successfully opened
        return 1;
    }

    string line;
    int maxX, maxY;

    // Read the first line of the file to determine maxX and maxY
    getline(file, line);
    istringstream firstLine(line);
    firstLine >> maxX >> maxY;

    // Create an empty Quadtree
    Quadtree tree(nullptr);

    // Read the remaining lines in the file to populate the Quadtree
    while (getline(file, line)) {
        string city_name;
        int x, y;
        istringstream iss(line);
        iss >> city_name >> x >> y; // Extract city name and coordinates from the line
        NodeData data(city_name, x, y); // Create a NodeData object with the parsed values

        // Only insert the city into the tree if it lies within the defined bounds
        if (x <= maxX && y <= maxY)
            tree.insert(data);
    }
    file.close(); // Close the file

    // Print the structure of the Quadtree
    tree.pretty_print();

    // Open a second file containing query data
    string filename2 = "queries0.txt";
    ifstream file2(filename2);
    if (!file2.is_open()) {
        cerr << "Failed to open " << filename2 << endl; // Check if the file was successfully opened
        return 1;
    }

    // Process each query in the file
    while (getline(file2, line)) {
        int value1, value2, value3;
        istringstream iss(line);
        char comma;

        // Extract three integer values separated by commas
        iss >> value1 >> comma >> value2 >> comma >> value3;

        // Perform the query on the Quadtree
        tree.find_countries(value1, value2, value3);

        // Print the cities found and the search path
        print(tree.cities,"city");
        print(tree.path,"path");

        // Clear the lists of cities and search paths for the next query
        tree.cities.clear();
        tree.path.clear();
    }
    file2.close(); // Close the query file
    return 0;
}
