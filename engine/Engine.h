#pragma once

#include <unordered_map>
#include <vector>

#include "../wrapper/Wrapper.h"

/**
 * interface to use wrapped functions
 */
class Engine {
    std::unordered_map<std::string, Wrapper*> _funcs; //< stores pairs of `func_name`, `func`

public:
    /**
     * default constructor is prohibited and not used
     */
    Engine() = default;

    /**
     * registers the command
     * @param wrapper wrapped function
     * @param name name with which to register the wrapped function
     */
    void register_command(Wrapper* wrapper, const std::string& name) {
        if (wrapper == nullptr)
            throw std::runtime_error("Passed wrapper is nullptr");
        _funcs[name] = wrapper;
    }

    /**
     * runs the the wrapped function with name `name`
     * @param name name of the wrapped function to run
     * @param args arguments to call the wrapped function with
     * @return returns the result of the wrapped function
     */
    primitive execute(const std::string& name, const operands& args) {
        auto wrap = _funcs.find(name);
        if (wrap == _funcs.end())
            throw std::runtime_error("No function named `" + name + "` was registered!");
        return wrap->second->run(args);
    }
};