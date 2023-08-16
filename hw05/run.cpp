#include "hw05.h"
#include <iostream>

std::vector<sql::Token> valid_token_stream() {
  std::vector<sql::Token> tokens;

  tokens.emplace_back(sql::token::Select{});
  tokens.emplace_back(sql::token::Asterisks{});
  tokens.emplace_back(sql::token::From{});
  tokens.emplace_back(sql::token::Identifier{"MY_TABLE"});
  tokens.emplace_back(sql::token::Semicolon{});

  return tokens;
}

std::vector<sql::Token> invalid_token_stream() {
  std::vector<sql::Token> tokens;

  tokens.emplace_back(sql::token::From{});
  tokens.emplace_back(sql::token::Asterisks{});
  tokens.emplace_back(sql::token::Select{});
  tokens.emplace_back(sql::token::Identifier{"MY_TABLE"});
  tokens.emplace_back(sql::token::Semicolon{});

  return tokens;
}

int main() {
  // Change to get an invalid token stream
  bool get_valid_tokens = true;

  std::vector<sql::Token> tokens;
  if (get_valid_tokens) {
    tokens = valid_token_stream();
  } else {
    tokens = invalid_token_stream();
  }

  if (sql::is_valid_sql_query(tokens)) {
    std::cout << "Query valid\n";
  } else {
    std::cout << "Query not valid\n";
  }

  // Your other tests go here
}
