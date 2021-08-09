#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
**************************************************************************************************/

// Constructors


Edge::Edge(int target_id){

    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = 0;

}

Edge::Edge(int target_id, float weight)
{
    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = weight;
}

Edge::Edge(int target_id,int id_origem, float weight)
{
    this->target_id = target_id;
    this->id_origem = id_origem;
    this->next_edge = nullptr;
    this->weight = weight;
}


// Destructor
Edge::~Edge(){

    if (this->next_edge != nullptr){
        delete this->next_edge;
        this->next_edge = nullptr;
    }

}

// Getters
int Edge::getTargetId(){

    return this->target_id;

}

Edge* Edge::getNextEdge(){

    return this->next_edge;

}

float Edge::getWeight(){

    return this->weight;

}

 int Edge::getIdOrigem() {
     return this->id_origem;
 }

// Setters

 void Edge::setTargetId(int id) {
     this->target_id = id;
 }

 void Edge::setIdOrigem(int id) {
     this->id_origem = id;
 }

void Edge::setNextEdge(Edge* edge){

    this->next_edge = edge;

}

void Edge::setWeight(float weight){

    this->weight = weight;

}
