#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

using primitive = double;
using operand = std::pair<std::string, primitive>;
using operands = std::vector<operand>;
using values = std::vector<primitive>;
using named_operands = std::unordered_map<std::string, primitive>;

class Wrapper {
private:
    named_operands _ops;
    std::vector<std::string> _opsOrder;
    std::function<primitive(const values&)> _func;
public:
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
        _func = [obj, obj_func](const values& vals) {
            if (vals.size() != sizeof...(Args))
                throw std::runtime_error("Invalid number of arguments");
            return _call(obj, obj_func, std::make_index_sequence<sizeof...(Args)>{}, vals);
        };
    }

    template<class O, class... V, size_t... S>
    static primitive
    _call(O* obj, primitive(O::*func)(V...), std::index_sequence<S...>, const values& vals) {
        return (obj->*func)(vals[S]...);
    }

    primitive run(const operands& args) {
        named_operands ops;
        ops.insert(args.begin(), args.end());
        auto it = ops.begin();
        values argVals;

        for (auto&& op: _opsOrder) {
            if ((it = ops.find(op)) == ops.end())
                throw std::runtime_error("Operand `" + op + "` is not found");
            argVals.push_back(ops.at(it->first));
        }
        return _func(argVals);
    }
};