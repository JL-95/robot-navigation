#pragma once

#include "caldova/nav/Types.hpp"
#include <cstddef>

namespace caldova::nav {

class RouteCache {
public:
    void remember(const PathBuffer& path);
    PathBuffer restore() const;

private:
    const PathPoint* lastPoints_ = nullptr;
    std::size_t lastCount_ = 0;
};

}
