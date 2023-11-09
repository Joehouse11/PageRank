#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct Node {
    double rank;
    string name;
    int outDegree;

    Node(){}
    Node(string name){
        this->rank = 0.0;
        this->name = name;
        this->outDegree = 0;
    }
};
class AdjacencyList {
private:
//Think about what member variables you need to initialize
// create your representation of an adjencyList
    map<string, vector<pair<string,double>>> aList;
    int nodeCount;
    int numIterations;
    // number of nodes;

    //create a node list to track # of froms for each node
    map<string, int> outDegree;
    vector<Node> nodeList;

    map<string, double> finalRank;


public:
//Think about what helper functions you will need in the algorithm
    AdjacencyList(){
    this->nodeCount = 0;

    }
    void PageRank(int n);
    void AddNode(string from, string to);
    void CalcOutDegree();
    void setIterations(int i);
    void print();
};
void AdjacencyList::AddNode(string from, string to) {
// check if the websites already exist in Adjacency list
//if not create them
//Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
// if map is empty map.end and map.begin will be the same
    map<string, vector<pair<string,double>>>::iterator itFrom;
    map<string, vector<pair<string,double>>>::iterator itTo;

    Node from1 = Node(from);
    Node to1 = Node(to);

    itFrom = aList.find(from);
    itTo = aList.find(to);

    // case where already exists
    if (itTo != aList.end()){

        aList[to].push_back(make_pair(from,1.0));

        outDegree[from]++;


    }
    //case where from node doesn't exit in AdjacencyList
    if (itFrom == aList.end()){


        aList[from];
        //increase nodecount
        nodeCount = nodeCount+1;

        //initialize outdegree
        outDegree[from] = 1;

    }
    if(itTo == aList.end()){
        aList[to].push_back(make_pair(from,1.0));
        // cover the case that itTo is new but itFrom is not

        if (itFrom != aList.end()){
            outDegree[from]++;
        }
        //increase nodecount
        nodeCount = nodeCount+1;

        outDegree[to] = 0;
    }

}
void AdjacencyList::PageRank(int n) {
// prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages
// and rounding rank to two decimal places

    setIterations(n);
    CalcOutDegree();

    // initialize Ro with 1/NodeCount
    for (auto page : aList){

        finalRank[page.first] = (1/(double)nodeCount);

    }

    for (int powerIt = 0; powerIt < n-1; powerIt++){

        //multiply M by Ro to find R1
        // update R1 then repeat
        map<string, double> tempRank;

        //iterate through each node in M
        for (auto page:aList){
            for(int i =0; i < page.second.size(); i++){
                // multiply the stored outdegree with Ro to find R1
              tempRank[page.first] += page.second.at(i).second * finalRank[page.second.at(i).first];


            }
            //need to account for the case that there are no web pages pointing to the page
            if (page.second.size() ==0){
                tempRank[page.first] = 0.00;
            }
        }
        //updates Rank to R(powerIt)
        finalRank = tempRank;


    }

}

void AdjacencyList::CalcOutDegree() {
    //needs to go through each map
    // then through each pair of every map
    // find the name of the from and then update its outdegree by dividing 1/(# times the node is the from)

    for (auto i = aList.begin(); i != aList.end(); i++){
        for (int j = 0; j < i->second.size(); j++) {
            i->second.at(j).second = 1/(double)outDegree[i->second.at(j).first];
        }
    }

}
void AdjacencyList::setIterations(int i) {
    this->numIterations = i;
}
void AdjacencyList::print(){
   // cout << "Node Count " << nodeCount << endl;

    for (auto it = finalRank.begin(); it != finalRank.end(); it++){
        cout << it->first << " " << fixed << setprecision(2) << it->second << endl;
    }
}

int main()
{
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;

//Create a graph object
    AdjacencyList graph;

    for(int i = 0;i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;

// Add nodes to graph
    graph.AddNode(from, to);
    }

    graph.PageRank(power_iterations);

    graph.print();
}

