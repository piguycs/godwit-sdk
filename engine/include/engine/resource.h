#pragma once

#include <any>
#include <functional>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename F>
struct FunctionTraits;

template <typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType(*)(Args...)> {
    using ArgTuple = std::tuple<Args...>;
};

namespace engine {

class ResourceManager {
    std::unordered_map<std::type_index, std::any> resources;
    std::vector<std::function<void()>> systems;
    std::vector<std::function<void()>> systems2D;
    std::vector<std::function<void()>> systems3D;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    template<typename T, typename... Args>
    void registerResource(Args&&... args) {
        resources.emplace(typeid(T), T(std::forward<Args>(args)...));
    }

    template<typename Func>
    void addSystem(Func&& func)  {
        using Traits = FunctionTraits<std::decay_t<Func>>;
        using ArgTuple = typename Traits::ArgTuple;

        auto system_wrapper = [this, func=std::forward<Func>(func)]() mutable {
            callSystemWrapper<ArgTuple>(
                func,
                std::make_index_sequence<std::tuple_size_v<ArgTuple>>{}
            );
        };

        systems.push_back(system_wrapper);
    }

    void runSystemsOnce() {
        for (auto& system : systems) {
            system();
        }
    }

    template<typename T>
    T& getResource() {
        auto it = resources.find(typeid(T));

        if (it != resources.end()) {
            return std::any_cast<T&>(it->second);
        }

        throw std::runtime_error(std::string("Resource not found: ") + typeid(T).name());
    }

private:
    template<typename ArgTuple, typename Func, size_t... Is>
    void callSystemWrapper(Func& func, std::index_sequence<Is...>) {
        auto args_tuple = std::forward_as_tuple(
            getResource<std::remove_reference_t<std::tuple_element_t<Is, ArgTuple>>>()...
        );

        std::apply(func, args_tuple);
    }
};

}
