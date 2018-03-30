#include "Node.h"

Node::~Node()
{
    for(int i=0; i<adjNum; i++)
    {
        delete adj[i];
    }
    delete[] adj;
}

bool Node::isAdj(Node* _node)
{
    for(int i=0; i<adjNum; i++)
    {
        if((int)(*adj[i]) == (int)(*_node)) return true;
    }
    return false;
}

void Node::addAdj(Node* _node, bool viceVersa)
{
    for (int i=0; i<adjNum; i++)
        if (_node->ID == adj[i]->ID) return;
    Node** buffer = new Node*[adjNum];
    for (int i=0; i<adjNum; i++)
        buffer[i] = adj[i];
    adj = new Node*[++adjNum];
    for (int i=0; i<adjNum-1; i++)
    {
        adj[i] = buffer[i];
    }
    delete[] buffer;
    adj[adjNum-1] = _node;
    if(viceVersa) _node->addAdj(this, false);
}

void Node::print()
{
    if(adjNum > 0)
    {
        std::cout << "Wezel " << ID << " jest przylegly z wezlami o identyfikatorach: ";
        for (int i=0; i<adjNum; i++) std::cout << adj[i]->ID << " ";
        std::cout << std::endl;
    }
    else std::cout << "Wezel " << ID << " nie ma przyleglych wezlow" << std::endl;
}
