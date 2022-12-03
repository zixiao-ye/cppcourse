#include "token.h"

namespace sql {
Token::Token(token_type value) : value_(value) {}

Token::token_type Token::value() const { return value_; }
}
