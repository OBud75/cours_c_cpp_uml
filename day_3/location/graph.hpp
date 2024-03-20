#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "location.hpp"
#include "tsp.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class Graph {
public:
    Graph(int V);
    void addEdge(int u, int v, double w);
    void drawCompleteGraph(const std::vector<Location>& locations, const Tour& tspTour, const std::string& filePath);
    int getV() const { return V; }

private:
    int V;
    std::vector<std::vector<std::pair<int, double>>> adj;
};

#endif
