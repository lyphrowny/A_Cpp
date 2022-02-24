#include "Evaluator.h"

double Evaluator::evaluate(std::list<std::unique_ptr<Token>>& rpn) {
    std::stack<double> st;
    std::vector<double> args(2);

    for (auto&& tok: rpn) {
        if (tok->op->getArity() == Arity::UNARY) {
            if (tok->op->getName() == "CONST") {
                st.push(tok->getValue());
                continue;
            }
            else {
                args[0] = st.top();
                st.pop();
            }
        } else if (tok->op->getArity() == Arity::BINARY) {
            args[1] = st.top();
            st.pop();
            args[0] = st.top();
            st.pop();
        }
        st.push(tok->op->calcFunc(args));
    }
    return st.top();
}


//double Evaluator::evaluate(std::list<Token>& rpn) {
//    std::stack<double> st;
//    double _temp;
//
//    for (auto&& tok: rpn) {
//        if (tok.getName() == "CONST")
//            st.push(tok.getValue());
//        else if (tok.getName() == "!") {
//            _temp = std::tgamma(st.top() + 1);
//            st.pop();
//            st.push(_temp);
//        } else if (tok.getName() == "~") {
//            _temp = -st.top();
//            st.pop();
//            st.push(_temp);
//        } else if (tok.getName() == "sin") {
//            _temp = std::sin(st.top());
//            st.pop();
//            st.push(_temp);
//        } else if (tok.getName() == "tan") {
//            _temp = std::tan(st.top());
//            st.pop();
//            st.push(_temp);
//        } else {
//            double x = st.top();
//            st.pop();
//            double y = st.top();
//            st.pop();
//            if (tok.getName() == "+")
//                st.push(y + x);
//            else if (tok.getName() == "-")
//                st.push(y - x);
//            else if (tok.getName() == "*")
//                st.push(y * x);
//            else if (tok.getName() == "/")
//                st.push(y / x);
//            else if (tok.getName() == "^")
//                st.push(std::pow(y, x));
//        }
//    }
//    return st.top();
//}
