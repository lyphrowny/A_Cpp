#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

#include "../wrapper/Wrapper.h"

using primitive = double;
using operand = std::pair<std::string, primitive>;
using operands = std::vector<operand>;

class Engine {
    std::unordered_map<std::string, std::unique_ptr<Wrapper>> _funcs;

public:
    Engine() = default;
    void register_command(const Wrapper& wrapper, const std::string& name) {
        _funcs[name] = std::make_unique<Wrapper>(wrapper);
    }

    primitive execute(const std::string& name, const operands& args) {
        auto wrap = _funcs.find(name);
        if (wrap == _funcs.end())
            throw std::runtime_error("No function named `" + name + "` was registered!");
        return wrap->run(args);
    }
};