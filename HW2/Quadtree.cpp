//
// Created by Ege Tan on 8.11.2024.
//
#include "Quadtree.h"

// Constructor for Quadtree that initializes the root node
Quadtree::Quadtree(Node * _root):root(_root){}

// Destructor for Quadtree, ensures that the root node and its children are deleted
Quadtree::~Quadtree() {
    delete root;
}

// Determines the region of a node relative to a circular range defined by (x, y, r)
// Returns an integer corresponding to a specific region
int Quadtree::determine_region(const int x, const int y, const int r, const Node* node) const {
    double distance = calculate_distance(x, y, node->data.x, node->data.y);

    // Check if the node is within the circular range
    if (distance <= r)
        return 13;

    // Check if the node is outside the circular range in specific regions
    if (node->data.x < x - r) {
        if (node->data.y > y + r)
            return 1; // Top-left region
        if (node->data.y < y - r)
            return 6; // Bottom-left region
        return 4; // Left region
    }
    if (node->data.x > x + r) {
        if (node->data.y > y + r)
            return 3; // Top-right region
        if (node->data.y < y - r)
            return 8; // Bottom-right region
        return 5; // Right region
    }
    if (node->data.y < y - r)
        return 7; // Bottom region
    if (node->data.y > y + r)
        return 2; // Top region

    // Check for nodes close to the edges of the circular range
    if (node->data.y > y && node->data.y < y + r) {
        if (node->data.x > x && node->data.x < x + r && distance > r)
            return 10;
        if (node->data.x < x && node->data.x > x - r && distance > r)
            return 9;
    }
    if (node->data.y < y && node->data.y > y - r) {
        if (node->data.x > x && node->data.x < x + r && distance > r)
            return 12;
        if (node->data.x < x && node->data.x > x - r && distance > r)
            return 11;
    }

    // Default case: outside all regions
    return 0;
}

// Inserts a NodeData object into the Quadtree
void Quadtree::insert(const NodeData &data) {
    insert(data, root);
}

// Recursive helper function for inserting a NodeData object into the Quadtree
void Quadtree::insert(const NodeData &data, Node* &t) const {
    // Create a new node if the current position is null
    if (t == nullptr) {
        t = new Node(data, nullptr, nullptr, nullptr, nullptr);
        return;
    }

    // Prevent insertion of duplicate nodes
    if (data.x == t->data.x && data.y == t->data.y)
        return;

    // Determine which quadrant to insert the node into
    if (data.x >= t->data.x) {
        if (data.y >= t->data.y)
            insert(data, t->NE); // Northeast quadrant
        else
            insert(data, t->SE); // Southeast quadrant
    }
    else {
        if (data.y >= t->data.y)
            insert(data, t->NW); // Northwest quadrant
        else
            insert(data, t->SW); // Southwest quadrant
    }
}

// Recursive function to print the Quadtree in a structured manner
void Quadtree::pretty_print(const Node* t) {
    if (t != nullptr) { // If the tree is not empty
        cout << t->data.city_name<< endl;// Print the current node
        pretty_print(t->SE); // Recursively print the southeast subtree
        pretty_print(t->SW); // Recursively print the southwest subtree
        pretty_print(t->NE); // Recursively print the northeast subtree
        pretty_print(t->NW); // Recursively print the northwest subtree
    }
}

// Public interface to pretty_print, starting from the root node
void Quadtree::pretty_print() {
    pretty_print(root);
}

// Public interface to find cities within a circular range
void Quadtree::find_countries(int x, int y, int r) {
    find_countries(x, y, r, root);
}

// Recursive helper function to find cities within a circular range
void Quadtree::find_countries(int x, int y, int r, const Node * t) {
    if (t == nullptr)
        return; // Base case: empty subtree

    // Add the current node's city name to the search path
    path.push_back(t->data.city_name);

    // Check if the current node's coordinates are within the circular range
    if (calculate_distance(x, y, t->data.x, t->data.y) <= r)
        cities.push_back(t->data.city_name);

    // Determine the region of the current node relative to the circular range
    int region = determine_region(x, y, r, t);

    // Recursively search relevant quadrants
    if ((region == 1 || region == 2 || region == 4 || region == 9 || region == 10 || region == 11 || region == 13))
        find_countries(x, y, r, t->SE);

    if ((region == 2 || region == 3 || region == 5 || region == 9 || region == 10 || region == 12 || region == 13))
        find_countries(x, y, r, t->SW);

    if ((region == 4 || region == 6 || region == 7 || region == 9 || region == 11 || region == 12 || region == 13))
        find_countries(x, y, r, t->NE);

    if ((region == 5 || region == 7 || region == 8 || region == 10 || region == 11 || region == 12 || region == 13))
        find_countries(x, y, r, t->NW);
}

// Calculates the distance between two points (x1, y1) and (x2, y2)
double Quadtree::calculate_distance(int x1, int y1 , int x2 , int y2) const {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
