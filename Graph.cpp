#include "Graph.h"

Graph::~Graph()
{
    for(int i=0; i<nodeNum; i++)
    {
        delete nodes[i];
    }
    delete[] nodes;
}

void Graph::addNode(Node* _node)
{
    for(int i=0; i<nodeNum; i++)
        if((int)(*nodes[i]) == (int)(*_node)) return;
    Node** buffer = new Node*[nodeNum];
    for (int i=0; i<nodeNum; i++)
        buffer[i] = nodes[i];
    nodes = new Node*[++nodeNum];
    for (int i=0; i<nodeNum-1; i++)
    {
        nodes[i] = buffer[i];
    }
    delete[] buffer;
    nodes[nodeNum-1] = _node;
}

Node* Graph::getNodeByID(int _ID)
{
    for(int i=0; i<nodeNum; i++)
    {
        if((*nodes[i]) == _ID) return nodes[i];
    }
    return NULL;
}

void Graph::print()
{
    std::cout << "Wszystkie wezly w grafie:" << std::endl;
    for (int i=0; i<nodeNum; i++)
        nodes[i]->print();
    std::cout << std::endl;
}

void Graph::generateFromAdjList(std::string _data)
{
    int curNodeID;
    bool isIDKnown = false;
    if(_data.length() <= 6) {std::cout << "Niepoprawne dane" << std::endl; return;}
    std::string header = _data.substr(0, 7);
    if(header != "AdjList") {std::cout << "Niepoprawne dane (zly naglowek)" << std::endl; return;}
    _data = _data.substr(7);
    int whileCount = 0;
    while(_data.length() > 0 && whileCount < 20)
    {
        whileCount++;
        size_t endOfLine = _data.find_first_of("\n");
        std::string line;
        if(endOfLine != std::string::npos) line = _data.substr(0, endOfLine+1);
        else line = _data;
        _data = _data.substr(line.length());
        if(line.substr(line.length()-1) == "\n") line = line.substr(0, line.length()-1);
        while(line.length() > 0)
        {
            endOfLine = line.find_first_of(" ");
            std::string value;
            if(endOfLine != std::string::npos) value = line.substr(0, endOfLine+1);
            else value = line;
            line = line.substr(value.length());
            if(value != "- ")
            {
                if(value.substr(value.length()-1) == " ") value = value.substr(0, value.length()-1);
                int intValue = std::stoi(value.c_str());
                if(isIDKnown)
                {
                    Node* curNode = getNodeByID(curNodeID);
                    if(curNode != NULL)
                    {
                        Node* adjNode = getNodeByID(intValue);
                        if(adjNode == NULL)
                        {
                            adjNode = new Node(intValue);
                            addNode(adjNode);
                        }
                        curNode->addAdj(adjNode, false);
                    }
                }
                else
                {
                    curNodeID = intValue;
                    addNode(new Node(curNodeID));
                }
            }
            else isIDKnown = true;
        }
        isIDKnown = false;
    }
}
