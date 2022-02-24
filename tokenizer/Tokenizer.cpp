#include "Tokenizer.h"

int Tokenizer::_precedence(std::string const& tName) {
    if (tName == "(")
        return 0;
    else if (tName == "+" || tName == "-")
        return 1;
    else if (tName == "*" || tName == "/")
        return 2;
    else if (tName == "^")
        return 3;
    else if (tName == "sin" || tName == "tan")
        return 4;
    else if (tName == "!")
        return 5;
    else if (tName == "~")
        return 6;
    return 0;
}

std::list<Token>& Tokenizer::tokenize() {
    Token t;
    std::string tName;
    std::stack<Token> st;
    auto chr = this->_toTokenize.begin();
    while (chr != this->_toTokenize.end()) {
        if (*chr == ' ' || *chr == '\t') {
            chr++;
            continue;
        }
        if (*chr == '(') {
            tName = *chr;
            st.emplace(tName);
            chr++;
        } else if (*chr == ')' && !st.empty()) {
            Token next = st.top();
            while (!st.empty() && next.getName() != "(") {
                _tokens.push_back(next);
                st.pop();
                next = st.top();
            }
            st.pop();
            chr++;
        } else if (std::ispunct(*chr) && *chr != '.' || std::isalpha(*chr)) {
            if (std::ispunct(*chr))
                tName = *chr++;
            else {
                while (std::isalpha(*chr))
                    tName += *chr++;
            }
            while (!st.empty() && this->_precedence(st.top().getName()) >= this->_precedence(tName)) {
                _tokens.push_back(st.top());
                st.pop();
            }
            st.emplace(tName);
            tName.clear();
        } else if (*chr == '.' || std::isdigit(*chr)) {
            t.setName("CONST");
            double value = 0;
            while (chr != this->_toTokenize.end() && std::isdigit(*chr)) {
                value = 10 * value + (*chr - '0');
                chr++;
            }
            if (*chr == '.') {
                chr++;
                double factor = 1.;
                while (chr != this->_toTokenize.end() && std::isdigit(*chr)) {
                    factor /= 10;
                    value += factor * (*chr - '0');
                    chr++;
                }
            }
            t.setValue(value);
            this->_tokens.push_back(t);
//            t.setValue(0);
//            continue;
        }
//        std::string tName;
//        if (std::isalpha(*chr)) {
//            while (std::isalpha(*chr))
//                tName += *chr++;
//            this->_tokens.emplace_back(tName);
//            continue;
//        }
//        tName = *chr;
//        this->_tokens.emplace_back(tName);
//        chr++;
    }
    while (!st.empty()) {
        this->_tokens.push_back(st.top());
        st.pop();
    }
    return this->_tokens;
}
