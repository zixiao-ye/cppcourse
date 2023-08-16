#include "validator.h"

#include <variant>
#include <vector>

#include "token.h"
#include "utils.h"

namespace sql {

bool SqlValidator::is_valid() const {
  /// TODO: Implement this
  return false;
}

void SqlValidator::handle(Token token) {
  /// TODO: Implement this
}

struct TransitionFromStartVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviour
  State operator()(token::Select) const { return state::Invalid{}; }

  /// All the other tokens, put it in the invalid state
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::Start, Token token) {
  return std::visit(TransitionFromStartVisitor{}, token.value());
}

State transition(state::Valid, Token token) {
  // TODO: Implement
  return state::Invalid{};
}

State transition(state::Invalid, Token token) {
  // TODO: Implement
  return state::Invalid{};
}

} // namespace sql
