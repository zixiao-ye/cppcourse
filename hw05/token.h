#pragma once

#include <string>
#include <variant>

namespace sql {

namespace token {
/// Each token is represented by a struct, this is the bases of our type based token system
struct Select {};

/// Token can also carry some information, but this is more to show of the possibilities, we are not
/// using it here
struct Identifier {
  std::string name;
};

/*
 * TODO: all the tokens go between here
 */
/*
 * ... and here
 */
} // namespace token

/// Simple class representing a token for our simplified SQL select clause. A token be any of the
/// token types. And at runtime you can query which type is currently stored in the token.
class Token {
public:
  /// TODO: Add all types of token to the variant
  using token_type =
      std::variant<token::Select, token::Identifier>;

  // Disallow default construction, this doesn't really make sense, what should be a default
  // token? Maybe Unknown, but we don't have that so just disallow it
  Token() = delete;

  // Construct a token from a variant
  Token(token_type value);

  /// Getter for the underlying variant
  [[nodiscard]]
  token_type value() const;

private:
  token_type value_;
};
} // namespace sql
