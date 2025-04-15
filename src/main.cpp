#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
  NUMBER,
  OPERATOR,
  L_BRACKET,
  R_BRACKET
};

struct Token {
  TokenType type;
  double value;
  char symbol;

  Token(TokenType t, double v):
  type(t), value(v), symbol('\0') {}

  Token(TokenType t, char s):
    type(t), value(0.0), symbol(s) {}
};

std::vector<Token> CreateTokenStream(std::string expression) {
  std::vector<Token> token_stream;
  std::string temp_string;
  size_t brackets_balance_count = 0;
  for (auto i : expression) {
    if ((i < '9' && i > '0') || i == '.') {
      temp_string.push_back(i);
    } 
    if (i == '+' || i == '-' || i == '*' || i =='/') { 
      token_stream.emplace_back(TokenType::NUMBER, std::stod(temp_string));
      temp_string.clear();
      token_stream.emplace_back(TokenType::OPERATOR, i);
    }
    if (i == '(') {
      temp_string.clear();
      token_stream.emplace_back(TokenType::L_BRACKET, i);
      brackets_balance_count++;
    }
    if (i == ')') {
      if(temp_string.size() > 0 && temp_string != ".") {
        token_stream.emplace_back(TokenType::NUMBER, std::stod(temp_string));
      }
      temp_string.clear();
      token_stream.emplace_back(TokenType::R_BRACKET, i);
      brackets_balance_count--;
    }
  }

  if(temp_string.size() > 0) {
    token_stream.emplace_back(TokenType::NUMBER, std::stod(temp_string));
  }
  if (brackets_balance_count != 0) {
    std::cout << "Invalid expression" << std::endl;
    token_stream.clear();
  }
  return token_stream;
}



void PrintTokenStream(const std::vector<Token>& token_stream) {
  std::cout << std::endl;
  for (int i = 0; i < token_stream.size(); i++) {
    if (token_stream[i].type == TokenType::NUMBER) {
      std::cout << token_stream[i].value << std::endl;
    }
    if (token_stream[i].type == TokenType::OPERATOR || token_stream[i].type == TokenType::L_BRACKET || token_stream[i].type == TokenType::R_BRACKET) {
      std::cout << token_stream[i].symbol << std::endl;
    }
  }
}

int main() {
  std::string expression = "";
  std::getline(std::cin, expression);
  std::vector<Token> token_stream = CreateTokenStream(expression);
  
  PrintTokenStream(token_stream);
  return 0;
}
