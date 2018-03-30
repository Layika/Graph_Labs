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
    //int whileCount = 0;
    while(_data.length() > 0) // && whileCount < 20
    {
        //whileCount++;
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

std::string Graph::generateAdjList()
{
    std::stringstream result;
    result << "AdjList" << std::endl;
    for(int i=0; i<nodeNum; i++)
    {
        int adjNum = nodes[i]->getAdjNum();
        result << (*nodes[i]);
        if(adjNum > 0) result << " - ";
        for(int j=0; j<nodes[i]->getAdjNum(); j++) result << (*nodes[i])[j] << " ";
        result << std::endl;
    }
    return result.str();
}

void Graph::generateFromAdjMatrix(std::string _data)
{
    if(_data.length() <= 8) {std::cout << "Niepoprawne dane" << std::endl; return;}
    std::string header = _data.substr(0, 9);
    if(header != "AdjMatrix") {std::cout << "Niepoprawne dane (zly naglowek)" << std::endl; return;}
    _data = _data.substr(9);
    int nodeCount;
    int lineCount = -2;
    while(_data.length() > 0)
    {
        size_t endOfLine = _data.find_first_of("\n");
        std::string line;
        if(endOfLine != std::string::npos) line = _data.substr(0, endOfLine+1);
        else line = _data;
        _data = _data.substr(line.length());
        if(line.substr(line.length()-1) == "\n") line = line.substr(0, line.length()-1);
        nodeCount = -1;
        while(line.length() > 0)
        {
            endOfLine = line.find_first_of("\t");
            std::string value;
            if(endOfLine != std::string::npos) value = line.substr(0, endOfLine+1);
            else value = line;
            line = line.substr(value.length());
            if(nodeCount != -1)
            {
                if(value.substr(value.length()-1) == "\t") value = value.substr(0, value.length()-1);
                int intValue = std::stoi(value.c_str());
                if(lineCount == -1)
                {
                    addNode(new Node(intValue));
                }
                else
                {
                    if(intValue == 1) nodes[nodeCount]->addAdj(nodes[lineCount], false);
                }
            }
            nodeCount++;
        }
        lineCount++;
    }
}

std::string Graph::generateAdjMatrix()
{
    std::stringstream result;
    result << "AdjMatrix" << std::endl << "*\t";
    for(int i=0; i<nodeNum; i++) result << (*nodes[i]) << "\t";
    result << std::endl;
    for(int i=0; i<nodeNum; i++)
    {
        for(int j=-1; j<nodeNum; j++)
        {
            if(j==-1) result << (*nodes[i]) << "\t";
            else
            {
                if(nodes[j]->isAdj(nodes[i])) result << "1\t";
                else result << "0\t";
            }
        }
        result << std::endl;
    }
    return result.str();
}

void Graph::generateFromIncMatrix(std::string _data)
{
    if(_data.length() <= 8) {std::cout << "Niepoprawne dane" << std::endl; return;}
    std::string header = _data.substr(0, 9);
    if(header != "IncMatrix") {std::cout << "Niepoprawne dane (zly naglowek)" << std::endl; return;}
    _data = _data.substr(9);
    int nodeCount;
    int lineCount = -2;
    int matrixSize = 0;
    Node** startNodes;
    Node** endNodes;
    while(_data.length() > 0)
    {
        size_t endOfLine = _data.find_first_of("\n");
        std::string line;
        if(endOfLine != std::string::npos) line = _data.substr(0, endOfLine+1);
        else line = _data;
        _data = _data.substr(line.length());
        if(line.substr(line.length()-1) == "\n") line = line.substr(0, line.length()-1);
        nodeCount = -1;
        while(line.length() > 0)
        {
            endOfLine = line.find_first_of("\t");
            std::string value;
            if(endOfLine != std::string::npos) value = line.substr(0, endOfLine+1);
            else value = line;
            line = line.substr(value.length());
            if(value.substr(value.length()-1) == "\t") value = value.substr(0, value.length()-1);
            if(lineCount != -1 || nodeCount != -1)
            {
                int intValue = std::stoi(value.c_str());
                Node* curNode;
                if(lineCount == -1)
                {
                    matrixSize++;
                }
                else
                {
                    //if(intValue == 1) nodes[nodeCount]->addAdj(nodes[lineCount], false);
                    if(nodeCount == -1) {curNode = new Node(intValue); addNode(curNode);}
                    else
                    {
                        if(intValue == 1) startNodes[nodeCount] = curNode;
                        if(intValue == -1) endNodes[nodeCount] = curNode;
                    }
                }
            }
            nodeCount++;
        }
        if(lineCount == -1)
        {
            startNodes = new Node*[matrixSize];
            endNodes = new Node*[matrixSize];
        }
        lineCount++;
    }
    for(int i=0; i<matrixSize; i++) startNodes[i]->addAdj(endNodes[i], false);
}

std::string Graph::generateIncMatrix()
{
    std::stringstream result;
    result << "IncMatrix" << std::endl << "*\t";
    int totalAdj = 0;
    for(int i=0; i<nodeNum; i++) totalAdj += nodes[i]->getAdjNum();
    int adjaciencies[totalAdj][2];
    for(int i=0; i<totalAdj; i++) result << (i+1) << "\t";
    result << std::endl;
    int k = 0;
    for(int i=0; i<nodeNum; i++)
    {
        //result << (*nodes[i]) << "\t";
        int adjNum = nodes[i]->getAdjNum();
        for(int j=0; j<adjNum; j++)
        {
            adjaciencies[k][0] = (*nodes[i]);
            adjaciencies[k][1] = (*nodes[i])[j];
            k++;
        }
    }
    for(int i=0; i<nodeNum; i++)
    {
        result << (*nodes[i]) << "\t";
        for(int j=0; j<totalAdj; j++)
        {
            if(adjaciencies[j][0] == (*nodes[i])) result << "1\t";
            else if(adjaciencies[j][1] == (*nodes[i])) result << "-1\t";
            else result << "0\t";
        }
        result << std::endl;
    }
    return result.str();
}

void Graph::generateRandomByProbability(int _n, float _p)
{
    nodes = new Node*[_n];
    nodeNum = _n;
    float randResult;
    for(int i=0; i<_n; i++) nodes[i] = new Node(i+1);
    for(int i=0; i<_n; i++)
    {
        for(int j=0; j<_n; j++)
        {
            if(i != j)
            {
                randResult = (float) (1 + rand() % 1000)/1000.0f;
                if(randResult <= _p) nodes[i]->addAdj(nodes[j], false);
            }
        }
    }
}

void Graph::generateRandomByAdjaciencies(int _n, int _l)
{
    int maxAdj = (_n - 3) * _n + 2 * _n;
    if(_l > maxAdj)
    {
        std::cout << "BLAD: Za duza liczba krawedzi" << std::endl;
        return;
    }
    nodes = new Node*[_n];
    nodeNum = _n;
    for(int i=0; i<_n; i++) nodes[i] = new Node(i+1);
    for(int i=0; i<_l; i++)
    {
        int source = rand() % _n;
        int destination = rand() % _n;
        if(source == destination) i--;
        else if(nodes[source]->isAdj(nodes[destination])) i--;
        else nodes[source]->addAdj(nodes[destination], false);
    }
}
