#include "caldova/nav/RouteCache.hpp"

namespace caldova::nav {

void RouteCache::remember(const PathBuffer& path) {
    lastPoints_ = path.points.data();
    lastCount_ = path.points.size();
}

PathBuffer RouteCache::restore() const {
    PathBuffer path;
    if (lastPoints_ == nullptr || lastCount_ == 0) {
        return path;
    }
    path.points.assign(lastPoints_, lastPoints_ + lastCount_);
    return path;
}

}
