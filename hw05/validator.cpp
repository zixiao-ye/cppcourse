#include "validator.h"

#include <variant>
#include <vector>
#include<iostream>
#include "token.h"

namespace sql {

bool SqlValidator::is_valid() const {
  /// TODO: Implement this
  
  return std::holds_alternative<state::Valid>(state_);
}


void SqlValidator::handle(Token token) {
  /// TODO: Implement this
  state_ = std::visit([&token](auto& s){return transition(s, token);}, state_);
}

struct TransitionFromStartVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviour
  State operator()(token::Select) const { return state::SelectStmt{}; }

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


struct TransitionFromValidVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Valid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::Valid, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromValidVisitor{}, token.value());
}


struct TransitionFromInvalidVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::Invalid, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromInvalidVisitor{}, token.value());
}


struct TransitionFromSelectStmtVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::AllColumns{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::NamedColumn{}; }
};

State transition(state::SelectStmt, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromSelectStmtVisitor{}, token.value());
}


struct TransitionFromAllColumnsVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::FromClause{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::AllColumns, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromAllColumnsVisitor{}, token.value());
}


struct TransitionFromNamedColumnVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::FromClause{}; }
  State operator()(token::Comma) const { return state::MoreColumns{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::NamedColumn, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromNamedColumnVisitor{}, token.value());
}


struct TransitionFromMoreColumnsVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::NamedColumn{}; }
};

State transition(state::MoreColumns, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromMoreColumnsVisitor{}, token.value());
}


struct TransitionFromFromClauseVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Invalid{}; }
  State operator()(token::Identifier) const { return state::TableName{}; }
};

State transition(state::FromClause, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromFromClauseVisitor{}, token.value());
}


struct TransitionFromTableNameVisitor {
  State operator()(token::Select) const { return state::Invalid{}; }
  State operator()(token::From) const { return state::Invalid{}; }
  State operator()(token::Comma) const { return state::Invalid{}; }
  State operator()(token::Asterisks) const { return state::Invalid{}; }
  State operator()(token::Semicolon) const { return state::Valid{}; }
  State operator()(token::Identifier) const { return state::Invalid{}; }
};

State transition(state::TableName, Token token) {
  // TODO: Implement
  return std::visit(TransitionFromTableNameVisitor{}, token.value());
}

bool is_valid_sql_query(std::vector<Token> tokens){
  sql::SqlValidator sql;
  for ( std::vector<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++)
  {
    sql.handle(*iter);
  }
  
  return sql.is_valid();
}

} // namespace sql
