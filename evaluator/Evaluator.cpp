#include<math.h>

#include "Evaluator.h"

double Evaluator::evaluate(std::list<Token>& rpn) {
    std::stack<double> st;
    double _temp;

    for (auto&& tok: rpn) {
        if (tok.getName() == "CONST")
            st.push(tok.getValue());
        else if (tok.getName() == "!") {
            _temp = std::tgamma(st.top() + 1);
            st.pop();
            st.push(_temp);
        } else if (tok.getName() == "~") {
            _temp = -st.top();
            st.pop();
            st.push(_temp);
        } else if (tok.getName() == "sin") {
            _temp = std::sin(st.top());
            st.pop();
            st.push(_temp);
        } else if (tok.getName() == "tan") {
            _temp = std::tan(st.top());
            st.pop();
            st.push(_temp);
        } else {
            double x = st.top();
            st.pop();
            double y = st.top();
            st.pop();
            if (tok.getName() == "+")
                st.push(y + x);
            else if (tok.getName() == "-")
                st.push(y - x);
            else if (tok.getName() == "*")
                st.push(y * x);
            else if (tok.getName() == "/")
                st.push(y / x);
            else if (tok.getName() == "^")
                st.push(std::pow(y, x));
        }
    }
    return st.top();
}
