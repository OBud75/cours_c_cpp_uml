#include "tsp.hpp"
#include <limits>
#include <iostream>


Tour::Tour(const std::vector<Location>& locations) : locations(locations), totalDistance(0) {
    calculateDistance();
}

void Tour::calculateDistance() {
    totalDistance = 0;
    for (size_t i = 0; i < locations.size() - 1; ++i) {
        totalDistance += locations[i].distanceTo(locations[i + 1]);
    }
    if (!locations.empty()) {
        totalDistance += locations.back().distanceTo(locations.front());
    }
}

double Tour::distance() const {
    return totalDistance;
}

std::vector<Location> Tour::getLocations() const {
    return locations;
}


int findNearestUnvisitedLocationIndex(const Location& currentLocation, const std::vector<Location>& locations, std::vector<bool>& visited) {
    double minDistance = std::numeric_limits<double>::max();
    int nearestIndex = -1;
    for (size_t i = 0; i < locations.size(); ++i) {
        if (!visited[i]) {
            double distance = currentLocation.distanceTo(locations[i]);
            if (distance < minDistance) {
                minDistance = distance;
                nearestIndex = int(i);
            }
        }
    }
    return nearestIndex;
}

Tour findBestTour(const std::vector<Location>& locations) {
    std::vector<bool> visited(locations.size(), false);
    std::vector<Location> tourLocations;

    int currentIndex = 0;
    visited[currentIndex] = true;
    tourLocations.push_back(locations[currentIndex]);

    while (tourLocations.size() < locations.size()) {
        currentIndex = findNearestUnvisitedLocationIndex(tourLocations.back(), locations, visited);
        if (currentIndex == -1) break; 
        visited[currentIndex] = true;
        tourLocations.push_back(locations[currentIndex]);
    }
    return Tour(tourLocations);
}

Tour twoOptSwap(const std::vector<Location>& inputTour) {
    std::vector<Location> tour = inputTour;
    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (size_t i = 1; i < tour.size() - 1; ++i) {
            for (size_t k = i + 1; k < tour.size(); ++k) {
                double delta = -tour[i - 1].distanceTo(tour[i]) - tour[k].distanceTo(tour[(k + 1) % tour.size()])
                               + tour[i - 1].distanceTo(tour[k]) + tour[i].distanceTo(tour[(k + 1) % tour.size()]);
                if (delta < 0) {
                    std::reverse(tour.begin() + i, tour.begin() + k + 1);
                    improvement = true;
                    
                }
            }
        }
    }
    return Tour(tour);
}

