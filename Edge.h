/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int id_origem; // Identificiador do id do Nó de origem
        int target_id;
        Edge* next_edge;
        float weight;

    public:
        // Constructors
        // Edge(int target_id);
        Edge(int id_origem, int target_id);
        Edge(int id_origem, int target_id, float weight);
        // Destructor
        ~Edge();
        // Getters
        int getTargetId();
        int getIdOrigem();
        Edge* getNextEdge();
        float getWeight();
        // Setters
        void setTargetId(int id);
        void setIdOrigem(int id);
        void setNextEdge(Edge* edge);
        void setWeight(float weight); 
        // Função especial que serve para estrtura de comparação do Kruskal
        bool operator <(const Edge& Edge2) const
        {
            return weight < Edge2.weight;
        }

};      

#endif // EDGE_H_INCLUDED