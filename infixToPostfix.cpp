/*
characters to deal with: + - * / ^ ( )
doesn't handle negative numbers (unary operators)
when * comes after / or vice versa, we add them to stack (they're commutative) 2*3/4 => 234/*
left associative (when happen in the stack, we empty the stack - or pop the elements after the parenthesis):
  "-" then "+"
  "*" then "+"
  "/" then "+"
  "^" then "+"

  "-" then "-"
  "*" then "-"
  "/" then "-"
  "^" then "-"

  "^" then "*"

  "^" then "/"
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
typedef vector<int> vi;

bool isSymbol(char a) {
  return a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '(' || a == ')';
}

string infixToPostfix(string infix) {
  stack<char> s;
  string postfix = "";
  for (int i = 0; i < infix.length(); i++) {
    if (!isSymbol(infix[i])) {
      postfix += infix[i];
      continue;
    }
    switch (infix[i])
    {
    case '^':
      s.push(infix[i]);
      break;

    case '(':
      s.push(infix[i]);
      break;

    case ')':
      while (s.top() != '(') {
        postfix += s.top();
        s.pop();
      }
      s.pop();
      break;

    case '*':
      if (s.empty()) {
        s.push(infix[i]);
        break;
      }
      switch (s.top()) {
      case '+':
      case '-':
      case '(':
      case '*':
      case '/':
        s.push(infix[i]);
        break;

      case '^':
        while (!s.empty() && s.top() != '(') {
          postfix += s.top();
          s.pop();
        }
        s.push(infix[i]);
        break;
      }
      break;

    case '/':
      if (s.empty()) {
        s.push(infix[i]);
        break;
      }
      switch (s.top()) {
      case '+':
      case '-':
      case '(':
      case '*':
      case '/':
        s.push(infix[i]);
        break;

      case '^':
        while (!s.empty() && s.top() != '(') {
          postfix += s.top();
          s.pop();
        }
        s.push(infix[i]);
        break;
      }
      break;

    case '+':
      if (s.empty()) {
        s.push(infix[i]);
        break;
      }
      switch (s.top()) {
      case '+':
      case '(':
        s.push(infix[i]);
        break;

      case '-':
      case '*':
      case '/':
      case '^':
        while (!s.empty() && s.top() != '(') {
          postfix += s.top();
          s.pop();
        }
        s.push(infix[i]);
        break;
      }
      break;

    case '-':
      if (s.empty()) {
        s.push(infix[i]);
        break;
      }
      switch (s.top()) {
      case '+':
      case '(':
        s.push(infix[i]);
        break;

      case '-':
      case '*':
      case '/':
      case '^':
        while (!s.empty() && s.top() != '(') {
          postfix += s.top();
          s.pop();
        }
        s.push(infix[i]);
        break;
      }
      break;

    default:
      cout << "infixToPostfix error: non supported character \" " << infix[i] << " \" " << endl;
      return "error";
      break;
    }
  }
  while (!s.empty()) {
    postfix += s.top();
    s.pop();
  }
  return postfix;
}

int main() {

  string s;
  cin >> s;
  cout << infixToPostfix(s);
  cout << endl;

  return 0;
}