#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

/**
 * aliases of frequently used types
 */
using primitive = double;
using operand = std::pair<std::string, primitive>;
using operands = std::vector<operand>;
using values = std::vector<primitive>;
using named_operands = std::unordered_map<std::string, primitive>;

/**
 * wraps the object's function with named arguments with support of default values
 */
class Wrapper {
private:
    named_operands _ops; //< unordered map with `string` as key and `primitive` as value
    std::vector<std::string> _opsOrder; //< vector of names to keep the order of the arguments
    std::function<primitive(const values&)> _func; //< stores function wrapped in lambda
public:
    /**
     * constructor
     * @tparam T class to with belongs the function
     * @tparam Args variadic arguments of the wrapped function
     * @param obj class instance to which belongs the wrapped function
     * @param obj_func the function to be wrapped
     * @param args vector of pairs `arg_name`, `arg_default_value`
     */
    template<typename T, typename... Args>
    Wrapper(T* obj, primitive (T::*obj_func)(Args...), const operands& args) {
        if (obj == nullptr || obj_func == nullptr || args.empty())
            throw std::runtime_error("Bad Wrapper init");
        if (sizeof...(Args) != args.size())
            throw std::runtime_error("Number of func args is not equal to the number of passed args!");

        // store the order of operands
        for (auto&& arg: args) {
            _opsOrder.push_back(arg.first);
            _ops.insert(arg);
        }
        // capturing the `obj` and `obj_func` in lambda
        _func = [obj, obj_func](const values& vals) {
            if (vals.size() != sizeof...(Args))
                throw std::runtime_error("Invalid number of arguments");
            return _call(obj, obj_func, std::make_index_sequence<sizeof...(Args)>{}, vals);
        };
    }

    /**
     * function wrapper to the function, captured in lambda
     * @tparam O class, to which belongs the captured function
     * @tparam V variadic arguments of captured function
     * @tparam S indexes
     * @param obj instance of class, to which belongs the captured function
     * @param func the captured function
     * @param vals arguments of the captured function
     * @return the result of running the captured function
     */
    template<class O, class... V, size_t... S>
    static primitive
    _call(O* obj, primitive(O::*func)(V...), std::index_sequence<S...>, const values& vals) {
        // unpacks the vector into function arguments
        return (obj->*func)(vals[S]...);
    }

    /**
     * public function to run the captured function
     * @param args arguments to run the captured function with
     * @return the result of running the captured function
     */
    primitive run(const operands& args) {
        named_operands ops;
        // copying the vector of pair into map
        ops.insert(args.begin(), args.end());
        auto it = ops.begin();
        // holds the values of the arguments
        values argVals;

        for (auto&& op: _opsOrder) {
            if ((it = ops.find(op)) == ops.end())
                throw std::runtime_error("Operand `" + op + "` is not found");
            argVals.push_back(ops.at(it->first));
        }
        return _func(argVals);
    }
};