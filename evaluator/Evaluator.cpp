#include <stack>

#include "Evaluator.h"

/**
 * helper function to get the formatted error string
 * @param tok token, which produces the error
 * @param providedArgs number of already provided arguments
 * @return formatted error message
 */
std::string _formErrorMsg(std::unique_ptr<Token>&& tok, int providedArgs) {
    return "Function `" + tok->op->getName() + "` should have " + (tok->op->getArity() == Arity::UNARY ? "1" : "2") +
           " arguments, but " + std::to_string(providedArgs) + " were provided";
}

/**
 * evaluates the list of tokens in RPN
 * @param rpn list of tokens in RPN
 * @return result
 */
double Evaluator::evaluate(std::list<std::unique_ptr<Token>>&& rpn) {
    std::stack<double> st;
    std::vector<double> args(2);

    for (auto&& tok: rpn) {
        if (tok->op->getArity() == Arity::UNARY) {
            if (tok->op->getName() == "CONST") {
                st.push(tok->getValue());
                continue;
            } else {
                if (st.empty())
                    throw std::invalid_argument(_formErrorMsg(std::move(tok), 0));
                args[0] = st.top();
                st.pop();
            }
        } else if (tok->op->getArity() == Arity::BINARY) {
            if (st.empty())
                throw std::invalid_argument(_formErrorMsg(std::move(tok), 0));
            args[1] = st.top();
            st.pop();
            if (st.empty())
                throw std::invalid_argument(_formErrorMsg(std::move(tok), 1));
            args[0] = st.top();
            st.pop();
        }
        st.push(tok->op->calcFunc(args));
    }
    return st.top();
}
