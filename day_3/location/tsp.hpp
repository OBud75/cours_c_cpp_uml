#ifndef TSP_HPP
#define TSP_HPP

#include "location.hpp"
#include <vector>

class Tour {
private:
    std::vector<Location> locations;
    double totalDistance;
    std::vector<bool> isTSPedge;
    
public:
    explicit Tour(const std::vector<Location>& locations);
    void calculateDistance();
    double distance() const;
    std::vector<Location> getLocations() const;
    const std::vector<bool>& getIsTSPedge() const { return isTSPedge; }

        
};

// Cette fonction crée le tour en utilisant l'algorithme du plus proche voisin
Tour findBestTour(const std::vector<Location>& locations);
Tour twoOptSwap(const std::vector<Location>& tour);

#endif
