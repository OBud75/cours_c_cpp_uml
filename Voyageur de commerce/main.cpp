#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

struct City {
    int id;
    double x, y;
};

double distance(const City& a, const City& b) {

    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::vector<int> nearestNeighbor(const std::vector<City>& cities) {
    int n = cities.size();
    std::vector<bool> visited(n, false);
    std::vector<int> path;
    path.push_back(0);
    visited[0] = true;

    for (int i = 0; i < n - 1; ++i) {
        int lastVisited = path.back();
        double minDist = std::numeric_limits<double>::max();
        int closestCity = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double currentDist = distance(cities[lastVisited], cities[j]);
                if (currentDist < minDist) {
                    minDist = currentDist;
                    closestCity = j;
                }
            }
        }

        path.push_back(closestCity);
        visited[closestCity] = true;
    }

    path.push_back(path.front());
    return path;
}

int main() {

    std::vector<City> cities = {
     {0, 2.0, 3.0}, // Paris avec coordonnées x=2, y=3
    {1, 4.0, 0.0}, // Bordeaux avec coordonnées x=4, y=0
    {2, 1.0, 1.0}, // Lyon avec coordonnées x=1, y=1
    {3, 5.0, 2.0}  // Lille avec coordonnées x=5, y=2
    };

    std::vector<int> path = nearestNeighbor(cities);

    std::cout << "Chemin trouve : ";
    for (int cityId : path) {
        std::cout << cityId << " ";
    }
    std::cout << "\nDistance totale : ";
    double totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalDistance += distance(cities[path[i]], cities[path[i + 1]]);
    }
    std::cout << totalDistance << std::endl;

    return 0;
}
