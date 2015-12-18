#include <iostream>
#include <ctype.h>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <functional>
#include <utility>
#include <queue>
#include <stdexcept>
using namespace std;

class Vertex;
class Edge;
class Edge {
    public:
    int cap;
    int flow;
    Vertex * origin;
    Vertex * target;
    string eName;
    Edge (int c = -1, int f = 0, Vertex * t = NULL) : cap(c), flow(f), target(t) {}
    int getMaxIncreaseFlow (int activeIndex, int nextIndex) {
        int direction;
        if (activeIndex < nextIndex) {
            direction = 1;
        }
    else {
            direction = -1;
        }
        if ((direction > 0 && this->flow > 0) || (direction < 0 && this->flow < 0)) {
            return this->cap - abs(this->flow);
        }
        else {
            return this->cap + abs(this->flow);
        }
    }
    int updatedFlow (int newFlow) {
        this->flow += newFlow;
        return this->flow;
    }
};
class Vertex {
    public:
    bool sourc;
    bool sin;
    string name;
    int previous;
    int index;
    vector<Edge> edge;
    int weight;
    bool completed;
    Vertex (bool so = false, bool si = false, bool c = false, string n = "ERROR", int p = -1, int w = -1) : sourc(so), sin(si), completed(c), name(n), previous(p), weight(w) {}
};
class Graph {
    public:
    struct OrderByCap{
            bool operator() (Vertex const &a, Vertex const &b) { return a.weight < b.weight; }
    };
    priority_queue<Vertex, vector<Vertex>, OrderByCap> q;
    priority_queue<Vertex, vector<Vertex>, OrderByCap> q2;
    void maxFlow (Vertex active, Vertex sink, vector<Vertex> &v, ofstream &outfile) {
        Vertex source = active;
        
        //
        //
        //
        //
        //
        //
        //  Start of Part 2
        //
        //
        //
        //
        //
        
        for (int j = 0; j < v.size(); j++) {
            v[j].completed = false;
            v[j].weight = -1;
            v[j].previous = -1;
        }
        active = v[source.index];
        q = q2;
        vector<string> minCut;
        bool minCutFound = false;
        bool inVector = false;
        bool sinkActivated = false;
        do {
            inVector = false;
            for (int i = 0; i < minCut.size(); i++) {
                if (active.name == minCut[i]) {
                    inVector = true;
                }
            }
            if (inVector == false) {
                minCut.push_back(active.name);
            }
            cout << "Current: " << active.name << "(" << active.weight << ")"<< " FROM : ";
            if (active.previous == -1) {
                cout << " ??? " << endl << endl;
            }
            else {
                for (int k = 0; k < v.size(); k++) {
                  if (v[k].name == active.name) {
                      cout << v[v[k].previous].name << endl << endl;
                    }
                }
            }
            for (int i = 0; i < active.edge.size(); i++) {
                int maxFlowIncrease = active.edge[i].getMaxIncreaseFlow(active.index, active.edge[i].target->index);
                cout << "MAX FLOW INCREASE FOR "<< active.edge[i].eName << ": " << maxFlowIncrease << endl;
                if ((active.edge[i].target->weight == -1 || active.edge[i].target->weight < maxFlowIncrease) && active.edge[i].target->completed == false){
                    if (active.weight != -1) {
                        if (active.weight < maxFlowIncrease) {
                            active.edge[i].target->weight = active.weight;
                        }
                        else {
                            active.edge[i].target->weight = maxFlowIncrease;
                        }
                    }
                    else {
                        active.edge[i].target->weight = maxFlowIncrease;
                    }
                    
                    active.edge[i].target->previous = active.index;
                }
                cout << "Looking at: " << active.edge[i].target->name;
                if (active.edge[i].target->completed == false && active.edge[i].target->weight != 0){
                    cout << "   Not completed yet! Going in queue: ";
                    cout << active.edge[i].target->name << "(" << active.edge[i].target->weight << ")";
                    q.push(*active.edge[i].target);
                }
                else {
                    cout << "   Already completed! Queue unchanged.";
                }
                cout << endl;
            }
            for (int j = 0; j < v.size(); j++) {
                if (v[j].name == active.name) {
                    v[j].completed = true;
                }
            }
            for (int j = 0; j < v.size(); j++) {
                if (v[j].name == active.name) {
                    v[j].completed = true;
                }
            }
            if (q.empty() && v[sink.index].completed == false) {
                minCutFound = true;
                break;
            }
            if (v[sink.index].completed == true) { //then print new path
                int end;
                for (int j = 0; j < v.size(); j++) {
                    if (v[j].name == sink.name) {
                        end = j;
                    }
                }
                int beginning;
                for (int j = 0; j < v.size(); j++) {
                    if (v[j].name == source.name) {
                        beginning = j;
                    }
                }
                vector<string> print;
                print.push_back(sink.name);
                int position = end;
                vector<int> flowVect;
                cout << "FLOW VECTOR: ";
                while (position != beginning) {
                    print.push_back(v[v[position].previous].name);
                    for (int i = 0; i < v[position].edge.size(); i++) {
                        if (v[position].edge[i].target->name == v[v[position].previous].name) {
                            int f = v[position].weight;
                            flowVect.push_back(f);
                            cout << f << " ";
                        }
                    }
                    position = v[position].previous;
                }
                int lowestFlow = 100;
                for (int i = 0; i < flowVect.size(); i++) {
                    if (flowVect[i] < lowestFlow) {
                        lowestFlow = flowVect[i];
                    }
                }
                position = end;
                while (position != beginning) {
                    for (int i = 0; i < v[position].edge.size(); i++) {
                        if (v[position].edge[i].target->name == v[v[position].previous].name) {
                            if (v[position].index > v[v[position].previous].index) {
                                v[position].edge[i].flow = v[position].edge[i].updatedFlow(lowestFlow);
                                for (int j = 0; j < v[v[position].previous].edge.size(); j++) {
                                    if (v[position].edge[i].eName == v[v[position].previous].edge[j].eName) {
                                        v[v[position].previous].edge[j].flow = v[v[position].previous].edge[j].updatedFlow(lowestFlow);
                                    }
                                }
                            }
                            else {
                                v[position].edge[i].flow = v[position].edge[i].updatedFlow(-lowestFlow);
                                for (int j = 0; j < v[v[position].previous].edge.size(); j++) {
                                    if (v[position].edge[i].eName == v[v[position].previous].edge[j].eName) {
                                        v[v[position].previous].edge[j].flow = v[v[position].previous].edge[j].updatedFlow(-lowestFlow);
                                    }
                                }
                            }
                        }
                    }
                    position = v[position].previous;
                }
                cout << "PATH: {";
                for (int j = print.size() - 1; j >= 0; j--) {
                    cout << print[j] << " ";
                }
                print.clear();
                cout << "}" << endl;
                cout << "FLOW: " << lowestFlow << endl << endl;
                
                for (int j = 0; j < v.size(); j++) {
                    v[j].completed = false;
                    v[j].weight = -1;
                    v[j].previous = -1;
                }
                active = v[source.index];
                q = q2;
                minCut.clear();
                sinkActivated = false;
            }
            else {  //otherwise new path hasnt been found and needs to keep going
                active = q.top();
                if (active.name == sink.name) {
                    sinkActivated = true;
                }
                cout << endl << "Coming out queue: ";
                cout << active.name << "(" << active.weight << ")";
                q.pop();
            }
            
            cout << endl << endl;
            cout << "---------------------------" << endl;
        } while (minCutFound == false);
        
        int newMaxFlow = 0;
        for (int i = 0; i < v[sink.index].edge.size(); i++) {
            newMaxFlow += abs(v[sink.index].edge[i].flow);
        }
        outfile << "Max flow obtained: " << newMaxFlow << endl;
        cout << "NEW MAX FLOW: " << newMaxFlow << endl;
        outfile << "Vertices in min cut: ";
        cout << "Minumum cut vertices:";
        for (int i = 0; i < minCut.size(); i++) {
            outfile << minCut[i] << " ";
            cout << minCut[i] << " ";
        }
        outfile << endl;
        cout << endl;
        
        //
        //
        //
        //
        //
        //
        //  Finding Indvidual Path Flows
        //
        //
        //
        //
        //
        //
        
        for (int j = 0; j < v.size(); j++) {
            v[j].completed = false;
            v[j].weight = -1;
            v[j].previous = -1;
        }
        q = q2;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].edge.size(); j++) {
                v[i].edge[j].cap = abs(v[i].edge[j].flow);
                v[i].edge[j].flow = 0;
            }
        }
        active = v[source.index];
        int targetFlow = newMaxFlow;
        newMaxFlow = 0;
        while (newMaxFlow != targetFlow) {
            newMaxFlow = 0;
            cout << "Current: " << active.name << "(" << active.weight << ")"<< " FROM : ";
            if (active.previous == -1) {
                cout << " ??? " << endl << endl;
            }
            else {
                for (int k = 0; k < v.size(); k++) {
                  if (v[k].name == active.name) {
                      cout << v[v[k].previous].name << endl << endl;
                    }
                }
            }
            for (int i = 0; i < active.edge.size(); i++) {
                int maxFlowIncrease = active.edge[i].getMaxIncreaseFlow(active.index, active.edge[i].target->index);
                cout << "MAX FLOW INCREASE FOR "<< active.edge[i].eName << ": " << maxFlowIncrease << endl;
                if ((active.edge[i].target->weight == -1 || active.edge[i].target->weight < maxFlowIncrease) && active.edge[i].target->completed == false){
                    if (active.weight != -1) {
                        if (active.weight < maxFlowIncrease) {
                            active.edge[i].target->weight = active.weight;
                        }
                        else {
                            active.edge[i].target->weight = maxFlowIncrease;
                        }
                    }
                    else {
                        active.edge[i].target->weight = maxFlowIncrease;
                    }
                    
                    active.edge[i].target->previous = active.index;
                }
                cout << "Looking at: " << active.edge[i].target->name;
                if (active.edge[i].target->completed == false && active.edge[i].target->weight != 0){
                    cout << "   Not completed yet! Going in queue: ";
                    cout << active.edge[i].target->name << "(" << active.edge[i].target->weight << ")";
                    q.push(*active.edge[i].target);
                }
                else {
                    cout << "   Already complete! Queue unchanged.";
                }
                cout << endl;
            }
            for (int j = 0; j < v.size(); j++) {
                if (v[j].name == active.name) {
                    v[j].completed = true;
                }
            }
            if (v[sink.index].completed == true) { //then print new path
                int end;
                for (int j = 0; j < v.size(); j++) {
                    if (v[j].name == sink.name) {
                        end = j;
                    }
                }
                int beginning;
                for (int j = 0; j < v.size(); j++) {
                    if (v[j].name == source.name) {
                        beginning = j;
                    }
                }
                vector<string> print;
                print.push_back(sink.name);
                int position = end;
                vector<int> flowVect;
                while (position != beginning) {
                    print.push_back(v[v[position].previous].name);
                    for (int i = 0; i < v[position].edge.size(); i++) {
                        if (v[position].edge[i].target->name == v[v[position].previous].name) {
                            int f = v[position].edge[i].cap;
                            flowVect.push_back(f);
                        }
                    }
                    position = v[position].previous;
                }
                int lowestFlow = 100;
                for (int i = 0; i < flowVect.size(); i++) {
                    if (flowVect[i] < lowestFlow) {
                        lowestFlow = flowVect[i];
                    }
                }
                position = end;
                while (position != beginning) {
                    for (int i = 0; i < v[position].edge.size(); i++) {
                        if (v[position].edge[i].target->name == v[v[position].previous].name) {
                            if (v[position].index > v[v[position].previous].index) {
                                v[position].edge[i].flow = v[position].edge[i].updatedFlow(lowestFlow);
                                for (int j = 0; j < v[v[position].previous].edge.size(); j++) {
                                    if (v[position].edge[i].eName == v[v[position].previous].edge[j].eName) {
                                        v[v[position].previous].edge[j].flow = v[v[position].previous].edge[j].updatedFlow(lowestFlow);
                                    }
                                }
                            }
                            else {
                                v[position].edge[i].flow = v[position].edge[i].updatedFlow(-lowestFlow);
                                for (int j = 0; j < v[v[position].previous].edge.size(); j++) {
                                    if (v[position].edge[i].eName == v[v[position].previous].edge[j].eName) {
                                        v[v[position].previous].edge[j].flow = v[v[position].previous].edge[j].updatedFlow(-lowestFlow);
                                    }
                                }
                            }
                        }
                    }
                    position = v[position].previous;
                }
                outfile << "Flow: " << lowestFlow << " Path: ";
                cout << "PATH: {";
                for (int j = print.size() - 1; j >= 0; j--) {
                    outfile << print[j] << " ";
                    cout << print[j] << " ";
                }
                outfile << endl;
                print.clear();
                cout << "}" << endl;
                cout << "FLOW: " << lowestFlow << endl << endl;
                
                for (int j = 0; j < v.size(); j++) {
                    v[j].completed = false;
                    v[j].weight = -1;
                    v[j].previous = -1;
                }
                active = v[source.index];
                q = q2;
            }
            else {  //otherwise new path hasnt been found and needs to keep going
                active = q.top();
                cout << endl << "Coming out queue: ";
                cout << active.name << "(" << active.weight << ")";
                q.pop();
            }
            
            cout << endl << endl;
            cout << "---------------------------" << endl;
            
            for (int i = 0; i < v[sink.index].edge.size(); i++) {
                newMaxFlow += abs(v[sink.index].edge[i].flow);
            }
        }
        outfile.close();
        cout << "FINISHED!!!" << endl;
    }
};

int main( int argc, char *argv[] ) {
    string filename = argv[1];
    string line;
    string outputFilename = filename;
    if(filename.find('.') != string::npos) {
        int index = filename.find('.');
        outputFilename.erase(index, outputFilename.size() - 1);
    }
    
    outputFilename += ".out";
    
    ifstream myfile(filename.c_str());
    ofstream outfile(outputFilename.c_str());
    
    vector<Vertex> v;
    Vertex source;
    Vertex sink;
    Graph g;
    Edge e;
    int place = 0;
    
    getline(myfile, line);
    istringstream ss(line);
    string value;
    ss >> value;
    int numVertices = stoi(value);
    ss >> value;
    int numEdges = stoi(value);
    for (int i = 0; i < numVertices; i++) {
        getline(myfile, line);
        if  (line.find("source") != string::npos) {
            int index = line.size() - 1 - 6;
            line.erase(index, line.size() - 1);
            source.name = line;
            source.weight = -1;
            source.sourc = true;
            source.index = place;
            place++;
            v.push_back(source);
        }
        else if (line.find("sink") != string::npos) {
            int index = line.size() - 1 - 4;
            line.erase(index, line.size() - 1);
            sink.name = line;
            sink.weight = -1;
            sink.sin = true;
            sink.index = place;
            place++;
            v.push_back(sink);
        }
        else {
            Vertex regular;
            regular.name = line;
            regular.weight = -1;
            regular.index = place;
            place++;
            v.push_back(regular);
        }
    }
    while (getline(myfile, line)) {
        istringstream ss(line);
        string value;
        ss >> value;
        string edgeName = value;
        ss >> value;
        int fatness = stoi(value);
        ss >> value;
        string from = value;
        ss >> value;
        string to = value;
        Vertex * pointer;
        Vertex * pointer2;
        for (int i = 0; i < v.size(); i++) {
            if (v[i].name == to) {
                pointer = &v[i];
            }
        }
        for (int i = 0; i < v.size(); i++) {
            if (v[i].name == from) {
                pointer2 = &v[i];
            }
        }
        for (int j = 0; j < v.size(); j++) {
            if (v[j].name == from) {
                e.cap = fatness;
                e.origin = pointer2;
                e.target = pointer;
                e.eName = edgeName;
                v[j].edge.push_back(e);
            }
        }
        for (int i = 0; i < v.size(); i++) {
            if (v[i].name == from) {
                pointer = &v[i];
            }
        }
        for (int i = 0; i < v.size(); i++) {
            if (v[i].name == to) {
                pointer2 = &v[i];
            }
        }
        for (int j = 0; j < v.size(); j++) {
            if (v[j].name == to) {
                e.cap = fatness;
                e.origin = pointer2;
                e.target = pointer;
                e.eName = edgeName;
                v[j].edge.push_back(e);
            }
        }
    }
    myfile.close();
    for (int j = 0; j < v.size(); j++) {
        cout << v[j].name << " " << v[j].index << endl;
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].name << "'s ";
        cout << "edgeacency list: ";
        for (int j = 0; j < v[i].edge.size(); j++) {
            cout << "<" << v[i].edge[j].cap << " ";
            cout << v[i].edge[j].target->name;
            cout << " " << v[i].edge[j].eName << "> ";
        }
        cout << endl << endl;
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i].sourc == true) {
            source = v[i];
        }
    }
    g.maxFlow(source, sink, v, outfile);
    
    return 0;
}
