#include "graph.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Graph::Graph(int V) : V(V), adj(V) {}

void Graph::addEdge(int u, int v, double w) {
    adj[u].push_back({v, w});
}

void Graph::drawCompleteGraph(const vector<Location>& locations, const Tour& tspTour, const string& filePath) {
    int scale = 4;
    int margin_size = 100;

    int edgeThickness = 3;
    int nodeRadius = 30;
    double fontSize = 1.0; 
    double edgesFontSize = 0.7;

    // Convert Locations to Points and scale them
    vector<Point> points;
    for (const Location& loc : locations) {
        points.push_back(Point(static_cast<int>(loc.getX() * scale), static_cast<int>(loc.getY() * scale)));
    }

    // Calculate bounding box based on scaled points
    Rect boundingBox = boundingRect(points);

    // Expand the bounding box by the margin size
    boundingBox.x -= margin_size;
    boundingBox.y -= margin_size;
    boundingBox.width += margin_size * 2;
    boundingBox.height += margin_size * 2;

    // Calculate image dimensions
    const int imageWidth = boundingBox.width + margin_size * 4;
    const int imageHeight = boundingBox.height + margin_size * 4;

    // Create a white background image
    Mat image = Mat::zeros(imageHeight, imageWidth, CV_8UC3);
    image.setTo(Scalar(255, 255, 255));

    Scalar grayColor(240, 205, 170);
    Scalar blueColor(255, 50, 0);
    Scalar nodeColor(80, 25, 150); 
    Scalar textColor(255, 255, 255); 
    Scalar edgeTextColor(0, 0, 0);

    // Draw all edges in light blue (grayColor)
    for (size_t i = 0; i < locations.size(); ++i) {
        for (size_t j = i + 1; j < locations.size(); ++j) {
            Point start = points[i];
            Point end = points[j];
            line(image, start, end, grayColor, edgeThickness);
        }
    }

    // Draw TSP edges in blue and label them with weights
    auto tspLocations = tspTour.getLocations();
    for (size_t i = 0; i < tspLocations.size() - 1; ++i) {
        size_t nextIndex = i + 1;
        Point start = points[i];
        Point end = points[nextIndex];
        line(image, start, end, blueColor, edgeThickness);

        // Calculate and place the weight text in the middle of the edge
        double weight = locations[i].distanceTo(locations[nextIndex]);
        Point weightPos = (start + end) * 0.5;
        putText(image, to_string(static_cast<int>(weight)), weightPos, FONT_HERSHEY_SIMPLEX, edgesFontSize, edgeTextColor, 2);
    }

    // Draw nodes and fit the names inside them
    for (size_t i = 0; i < locations.size(); ++i) {
        Point center = points[i];
        circle(image, center, nodeRadius, nodeColor, FILLED);
        String label = "P" + to_string(i);

        // Get text size to center the label within the node
        int baseline = 0;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, fontSize, 2, &baseline);
        Point labelPos(center.x - labelSize.width / 2, center.y + labelSize.height / 2);
        putText(image, label, labelPos, FONT_HERSHEY_SIMPLEX, fontSize, textColor, 2);
    }

    // Save the image and check if successful
    if (imwrite(filePath, image)) {
        cout << "Image saved to: " << filePath << endl;
    } else {
        cerr << "Error saving image to: " << filePath << endl;
    }
}
