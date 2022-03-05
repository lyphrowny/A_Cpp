#pragma once

#include <unordered_map>
#include <vector>

#include "../wrapper/Wrapper.h"

class Engine {
    std::unordered_map<std::string, Wrapper*> _funcs;

public:
    Engine() = default;

    void register_command(Wrapper* wrapper, const std::string& name) {
        if (wrapper == nullptr)
            throw std::runtime_error("Passed wrapper is nullptr");
        _funcs[name] = wrapper;
    }

    primitive execute(const std::string& name, const operands& args) {
        auto wrap = _funcs.find(name);
        if (wrap == _funcs.end())
            throw std::runtime_error("No function named `" + name + "` was registered!");
        return wrap->second->run(args);

    }
};