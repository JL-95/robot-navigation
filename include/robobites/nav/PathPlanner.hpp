#pragma once

#include "caldova/nav/Types.hpp"
#include <vector>

namespace caldova::nav {

class CostGrid {
public:
    CostGrid(int width, int height);
    void applySensorFrame(const SensorFrame& frame);
    int costAt(int x, int y) const;
    int width() const;
    int height() const;

private:
    int width_ = 0;
    int height_ = 0;
    std::vector<int> cells_;
    int offset(int x, int y) const;
};

class PathPlanner {
public:
    PathBuffer plan(const RouteMap& route, const SensorFrame& frame) const;
};

}
