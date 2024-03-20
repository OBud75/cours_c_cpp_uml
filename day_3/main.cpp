#include "location/tsp.hpp"
#include "location/graph.hpp"
#include "location/location.hpp"

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <string>
#include <queue>
#include <map>

using namespace std;
using namespace cv;

int findLocationIndex(const std::vector<Location>& locations, const Location& loc) {
    auto it = std::find_if(locations.begin(), locations.end(), [&loc](const Location& l) {
        return l.getX() == loc.getX() && l.getY() == loc.getY();
    });
    return it != locations.end() ? std::distance(locations.begin(), it) : -1;
}

int findEdgeIndex(const std::vector<std::pair<int, int>>& edges, int start, int end) {
    auto it = std::find_if(edges.begin(), edges.end(), [start, end](const std::pair<int, int>& edge) {
        return (edge.first == start && edge.second == end) || (edge.first == end && edge.second == start);
    });
    return it != edges.end() ? std::distance(edges.begin(), it) : -1;
}

int solve_travelling_salesman_problem() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 250);

    // Génération d'emplacements aléatoires uniques
    std::vector<Location> locations;
    while (locations.size() < 6) {
        double x = distrib(gen);
        double y = distrib(gen);
        Location newLocation(x, y);
        
        // Assurer que le nouvel emplacement est unique avant de l'ajouter à la liste
        if (std::none_of(locations.begin(), locations.end(), [&newLocation](const Location& loc) {
            return newLocation.getX() == loc.getX() && newLocation.getY() == loc.getY();
        })) {
            locations.push_back(newLocation);
        }
    }

    Graph graph(locations.size());
    vector<bool> isTSPedge(graph.getV() * (graph.getV() - 1) / 2, false);
    vector<pair<int, int>> allEdges;
    vector<int> allWeights;

    for (int i = 0; i < graph.getV(); ++i) {
        for (int j = i + 1; j < graph.getV(); ++j) {
            allEdges.emplace_back(i, j);
            allWeights.push_back(static_cast<int>(locations[i].distanceTo(locations[j])));
            graph.addEdge(i, j, allWeights.back());
        }
    }

    Tour bestTour = findBestTour(locations);
    
    for (size_t i = 0; i < bestTour.getLocations().size(); ++i) {
        size_t nextIndex = (i + 1) % bestTour.getLocations().size();
        int startIndex = findLocationIndex(locations, bestTour.getLocations()[i]);
        int endIndex = findLocationIndex(locations, bestTour.getLocations()[nextIndex]);
        
        int edgeIndex = findEdgeIndex(allEdges, startIndex, endIndex);
        if (edgeIndex != -1) {
            isTSPedge[edgeIndex] = true;
        }
    }

    vector<cv::Point> cvPoints;
    for (const auto& loc : locations) {
        cvPoints.emplace_back(static_cast<int>(loc.getX()), static_cast<int>(loc.getY()));
    }

    string outputPath = "./output/tsp_solution.jpg";
    graph.drawCompleteGraph(locations, bestTour, outputPath);
    std::cout << "Graph complete. TSP path: ";
    for (const auto& loc : bestTour.getLocations()) {
        std::cout << "(" << loc.getX() << ", " << loc.getY() << ") ";
    }
    std::cout << std::endl;

    cout << "Le graphe complet et le chemin TSP sont dessinés et enregistrés dans " << outputPath << endl;

    return 0;
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        std::cout << "HELLO" << std::endl;
        solve_travelling_salesman_problem();
        std::cout << "BYE" << std::endl;
        return 0;
    }

    if (argc != 2) {
        cout << "Please provide a function name as an argument.\n";
        return 1;
    }
    map<string, int(*)()> functions;
    functions["solve_travelling_salesman_problem"] = &solve_travelling_salesman_problem;

}
