#include "Tokenizer.h"

std::stack<Token>& Tokenizer::tokenize() {
    Token t;
    auto chr = this->_toTokenize.begin();
    while (chr != this->_toTokenize.end()) {
        if (*chr == ' ' || *chr == '\t') {
            chr++;
            continue;
        }
        if (*chr == '.' || std::isdigit(*chr)) {
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
            this->_tokens.push(t);
            t.setValue(0);
            continue;
        }
        std::string tName;
        if (std::isalpha(*chr)) {
            while (std::isalpha(*chr))
                tName += *chr++;
            this->_tokens.emplace(tName);
            continue;
        }
        tName = *chr;
        this->_tokens.emplace(tName);
        chr++;
    }
    return this->_tokens;
}
