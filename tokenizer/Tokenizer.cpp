#include <stack>

#include "Tokenizer.h"

/**
 * splits the string on tokens in RPN
 * @return list of tokens in RPN
 */
std::list<std::unique_ptr<Token>> Tokenizer::tokenize() {
    std::string tName;
    std::stack<std::unique_ptr<Token>> st;
    auto chr = this->_toTokenize.begin();
    while (chr != this->_toTokenize.end()) {
        if (std::isspace(*chr)) {
            chr++;
            continue;
        }
        if (*chr == LPAR) {
            tName = *chr;
            st.push(std::make_unique<Token>(this->_availableOps[tName]));
            chr++;
        } else if (*chr == RPAR && !st.empty()) {
            auto next = std::move(st.top());
            while (!st.empty() && next->op->getName()[0] != LPAR) {
                _tokens.push_back(std::move(next));
                st.pop();
                next = std::move(st.top());
            }
            st.pop();
            chr++;
        } else if (std::ispunct(*chr) && *chr != DOT || std::isalpha(*chr)) {
            if (std::ispunct(*chr))
                tName = *chr++;
            else {
                tName.clear();
                while (std::isalpha(*chr))
                    tName += *chr++;
            }
            if (_availableOps.find(tName) == _availableOps.end())
                throw std::domain_error("Function `" + tName + "` is not supported");
            while (!st.empty() && st.top()->op->getName() != tName &&
                   st.top()->op->getPrecedence() >= _availableOps[tName]->getPrecedence()) {
                _tokens.push_back(std::move(st.top()));
                st.pop();
            }
            st.push(std::make_unique<Token>(this->_availableOps[tName]));
        } else if (*chr == DOT || std::isdigit(*chr)) {
            tName = CONST;
            double value = 0;
            while (chr != this->_toTokenize.end() && std::isdigit(*chr)) {
                value = 10 * value + (*chr - '0');
                chr++;
            }
            if (*chr == DOT) {
                chr++;
                double factor = 1.;
                while (chr != this->_toTokenize.end() && std::isdigit(*chr)) {
                    factor /= 10;
                    value += factor * (*chr - '0');
                    chr++;
                }
            }
            auto t = std::make_unique<Token>(_availableOps[tName]);
            t->setValue(value);
            _tokens.push_back(std::move(t));
        }
    }
    while (!st.empty()) {
        this->_tokens.push_back(std::move(st.top()));
        st.pop();
    }
    return std::move(this->_tokens);
}
