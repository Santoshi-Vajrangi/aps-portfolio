#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

struct Point {
    double x, y;
    int cluster;
    double minDist;
};

double distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void kMeansClustering(std::vector<Point>& points, int k) {
    // Randomly initialize cluster centers
    std::vector<Point> centers;
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centers.push_back(points[rand() % points.size()]);
    }

    bool change = true;
    while (change) {
        change = false;
        
        // Assign points to the nearest center
        for (auto& point : points) {
            point.minDist = std::numeric_limits<double>::max();
            for (int i = 0; i < k; ++i) {
                double dist = distance(point, centers[i]);
                if (dist < point.minDist) {
                    point.minDist = dist;
                    point.cluster = i;
                }
            }
        }

        // Update cluster centers
        std::vector<int> counts(k, 0);
        std::vector<double> sumX(k, 0), sumY(k, 0);
        for (const auto& point : points) {
            int cluster = point.cluster;
            counts[cluster]++;
            sumX[cluster] += point.x;
            sumY[cluster] += point.y;
        }
        for (int i = 0; i < k; ++i) {
            Point newCenter = {sumX[i] / counts[i], sumY[i] / counts[i], 0, 0};
            if (distance(newCenter, centers[i]) > 1e-4) {
                change = true;
                centers[i] = newCenter;
            }
        }
    }

    // Output the result
    for (const auto& point : points) {
        std::cout << "Point (" << point.x << ", " << point.y << ") is in cluster " << point.cluster << std::endl;
    }
}

int main() {
    std::vector<Point> points = {
        {1.0, 1.0, -1, std::numeric_limits<double>::max()},
        {1.5, 2.0, -1, std::numeric_limits<double>::max()},
        {3.0, 4.0, -1, std::numeric_limits<double>::max()},
        {5.0, 7.0, -1, std::numeric_limits<double>::max()},
        {3.5, 5.0, -1, std::numeric_limits<double>::max()},
        {4.5, 5.0, -1, std::numeric_limits<double>::max()},
        {3.5, 4.5, -1, std::numeric_limits<double>::max()},
    };

    int k = 2; // Number of clusters
    kMeansClustering(points, k);

    return 0;
}
