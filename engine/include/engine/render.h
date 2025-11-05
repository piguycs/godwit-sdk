#pragma once

#include <memory>
#include <vector>

#include "renderables.h"

namespace engine {

template <typename RenderType>
class RenderCtx {
    friend class Engine;
    std::vector<std::shared_ptr<RenderType>> queue;
    static constexpr int DEFAULT_PREALLOC = 512;

   public:
    RenderCtx() { queue.reserve(DEFAULT_PREALLOC); }
    RenderCtx(std::size_t preallocQueueSize) { queue.reserve(preallocQueueSize); }

    template <typename T, typename... Args>
    void add(Args&&... args) {
        queue.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    }
};

using RenderCtx2D = RenderCtx<IRenderable2D>;
using RenderCtx3D = RenderCtx<IRenderable3D>;

}  // namespace engine
