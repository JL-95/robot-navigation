#pragma once

#include "robobites/nav/Types.hpp"
#include <cstddef>

namespace robobites::nav {

class RouteCache {
public:
    void remember(const PathBuffer& path);
    PathBuffer restore() const;

private:
    const PathPoint* lastPoints_ = nullptr;
    std::size_t lastCount_ = 0;
};

}
