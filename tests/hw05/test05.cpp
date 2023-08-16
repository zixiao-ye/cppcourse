/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "hw05.h"

// require at least c++20
static_assert(__cplusplus >= 202002L);

template <class TokenType> bool is_token_of_type(const sql::Token &token) {
  return std::holds_alternative<TokenType>(token.value());
}

TEST_CASE("Creating tokens") {
  WHEN("Creating a Select token") {
    auto token = sql::Token(sql::token::Select{});
    CHECK_UNARY(is_token_of_type<sql::token::Select>(token));
  }
  WHEN("Creating a From token") {
    auto token = sql::Token(sql::token::From{});
    CHECK_UNARY(is_token_of_type<sql::token::From>(token));
  }
  WHEN("Creating a Comma token") {
    auto token = sql::Token(sql::token::Comma{});
    CHECK_UNARY(is_token_of_type<sql::token::Comma>(token));
  }
  WHEN("Creating a Asterisks token") {
    auto token = sql::Token(sql::token::Asterisks{});
    CHECK_UNARY(is_token_of_type<sql::token::Asterisks>(token));
  }
  WHEN("Creating a Semicolon token") {
    auto token = sql::Token(sql::token::Semicolon{});
    CHECK_UNARY(is_token_of_type<sql::token::Semicolon>(token));
  }
  WHEN("Creating a Identifier token") {
    auto token = sql::Token(sql::token::Identifier{"Name"});
    CHECK_UNARY(is_token_of_type<sql::token::Identifier>(token));
  }
}

TEST_CASE("Test valid SQL queries") {
  GIVEN("the sequence of tokens: 'SELECT * FROM MYTABLE;'") {
    std::vector<sql::Token> tokens;
    tokens.emplace_back(sql::token::Select{});
    tokens.emplace_back(sql::token::Asterisks{});
    tokens.emplace_back(sql::token::From{});
    tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
    tokens.emplace_back(sql::token::Semicolon{});

    CHECK_UNARY(sql::is_valid_sql_query(tokens));
  }

  GIVEN("the sequence of tokens: 'SELECT * FROM MYTABLE;;;;'") {
    std::vector<sql::Token> tokens;
    tokens.emplace_back(sql::token::Select{});
    tokens.emplace_back(sql::token::Asterisks{});
    tokens.emplace_back(sql::token::From{});
    tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
    tokens.emplace_back(sql::token::Semicolon{});
    tokens.emplace_back(sql::token::Semicolon{});
    tokens.emplace_back(sql::token::Semicolon{});
    tokens.emplace_back(sql::token::Semicolon{});

    CHECK_UNARY(sql::is_valid_sql_query(tokens));
  }

  GIVEN("the sequence of tokens: 'SELECT Col1, Col2 FROM MYTABLE;'") {
    std::vector<sql::Token> tokens;
    tokens.emplace_back(sql::token::Select{});
    tokens.emplace_back(sql::token::Identifier{"Col1"});
    tokens.emplace_back(sql::token::Comma{});
    tokens.emplace_back(sql::token::Identifier{"Col2"});
    tokens.emplace_back(sql::token::From{});
    tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
    tokens.emplace_back(sql::token::Semicolon{});

    CHECK_UNARY(sql::is_valid_sql_query(tokens));
  }
}

TEST_CASE("Test invalid SQL queries") {
  GIVEN("a sequence of tokens, which do not start with 'SELECT'") {
    std::vector<sql::Token> tokens;

    WHEN("The first token is an Asterisks") {
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
      tokens.emplace_back(sql::token::Semicolon{});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }

    WHEN("The first token is 'FROM'") {
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
      tokens.emplace_back(sql::token::Semicolon{});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }

    WHEN("The first token is an identifier") {
      tokens.emplace_back(sql::token::Identifier{"WhatAreYouEvenDoing?"});
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
      tokens.emplace_back(sql::token::Semicolon{});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }
  }

  GIVEN("a sequence of tokens, which does not have a comma between columns") {
    std::vector<sql::Token> tokens;

    WHEN("the sequence of tokens: 'SELECT Col1, Col2 FROM MYTABLE;'") {
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Identifier{"Col1"});
      tokens.emplace_back(sql::token::Identifier{"Col2"});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
      tokens.emplace_back(sql::token::Semicolon{});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }
  }

  GIVEN("a sequence of tokens, which mix named columns and asterisks") {
    std::vector<sql::Token> tokens;

    WHEN("the sequence of tokens: 'SELECT Col1, Col2 FROM MYTABLE;'") {
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Identifier{"Col1"});
      tokens.emplace_back(sql::token::Comma{});
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});
      tokens.emplace_back(sql::token::Semicolon{});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }
  }

  GIVEN("a sequence of tokens, without a trailing semicolong") {
    std::vector<sql::Token> tokens;

    GIVEN("the sequence of tokens: 'SELECT * FROM MYTABLE'") {
      std::vector<sql::Token> tokens;
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Asterisks{});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }

    GIVEN("the sequence of tokens: 'SELECT Col1, Col2 FROM MYTABLE'") {
      std::vector<sql::Token> tokens;
      tokens.emplace_back(sql::token::Select{});
      tokens.emplace_back(sql::token::Identifier{"Col1"});
      tokens.emplace_back(sql::token::Comma{});
      tokens.emplace_back(sql::token::Identifier{"Col2"});
      tokens.emplace_back(sql::token::From{});
      tokens.emplace_back(sql::token::Identifier{"MYTABLE"});

      CHECK_UNARY_FALSE(sql::is_valid_sql_query(tokens));
    }
  }
}

TEST_CASE("Transition from Start state") {
  auto current_state = sql::state::Start{};

  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::SelectStmt>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}

TEST_CASE("Transition from SelectStmt state") {
  auto current_state = sql::state::SelectStmt{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::AllColumns>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::NamedColumn>(state));
    }
  }
}

TEST_CASE("Transition from AllColumns state") {
  auto current_state = sql::state::AllColumns{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::FromClause>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}

TEST_CASE("Transition from NamedColumn state") {
  auto current_state = sql::state::NamedColumn{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::FromClause>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::MoreColumns>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}

TEST_CASE("Transition from MoreColumns state") {
  auto current_state = sql::state::MoreColumns{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::NamedColumn>(state));
    }
  }
}

TEST_CASE("Transition from FromClause state") {
  auto current_state = sql::state::FromClause{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::TableName>(state));
    }
  }
}

TEST_CASE("Transition from TableName state") {
  auto current_state = sql::state::TableName{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Valid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}

TEST_CASE("Transition from Valid state") {
  auto current_state = sql::state::TableName{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Valid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}

TEST_CASE("Transition from Invalid state") {
  auto current_state = sql::state::Invalid{};
  GIVEN("a select token") {
    auto token = sql::Token{sql::token::Select{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a from token") {
    auto token = sql::Token{sql::token::From{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a comma token") {
    auto token = sql::Token{sql::token::Comma{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a asterisks token") {
    auto token = sql::Token{sql::token::Asterisks{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a semicolon token") {
    auto token = sql::Token{sql::token::Semicolon{}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }

  GIVEN("a identifier token") {
    auto token = sql::Token{sql::token::Identifier{"CoolTableName"}};
    auto state = sql::transition(current_state, token);

    THEN("New state is SelectStmt") {
      CHECK_UNARY(std::holds_alternative<sql::state::Invalid>(state));
    }
  }
}
