//
// Created by Ege Tan on 8.11.2024.
//
#ifndef HW2_QUADTREE_H
#define HW2_QUADTREE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

struct NodeData {
    string city_name;
    int x, y;
    NodeData(const string &city, int xPos, int yPos)
            :city_name(city), x(xPos), y(yPos) {}
};

class Node {
    NodeData data;
    Node* SE;
    Node* SW;
    Node* NE;
    Node* NW;
    Node(NodeData _data,Node * se ,Node *sw ,Node *ne ,Node *nw)
            :data(_data),SE(se),SW(sw),NE(ne),NW(nw){}
    Node(): data("",-1,-1){
        SE = nullptr;
        NE = nullptr;
        SW = nullptr;
        NW = nullptr;
    }
    ~Node(){
        delete SE;
        delete SW;
        delete NE;
        delete NW;
    }
    friend class Quadtree;
};

class Quadtree {
public:
    Quadtree(Node*);
    ~Quadtree();
    vector<string> path;
    vector<string> cities;
    void insert(const NodeData & );
    void pretty_print();
    void find_countries(int,int,int);
private:
    Node* root;
    void insert(const NodeData &, Node* &) const;
    void pretty_print(const Node*);
    void find_countries(int,int,int,const Node*);
    int determine_region(const int x,const int y,const int r,const Node* ) const;
    double calculate_distance(int, int, int, int) const;
};


#endif //HW2_QUADTREE_H
