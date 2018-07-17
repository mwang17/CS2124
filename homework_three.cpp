#include "std_lib_facilities.h"

class Token {
public:
  char kind;
  double value;
};

Token get_token(){
    char ch;
    cin >> ch;
    switch (ch) {
      case '(': case ')': case '+': case '-': case '*': case '/':
        return Token{ch};
      case '.':
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{'8',val};
        }
      case 'q':
        return Token{'q'};
      default:
        return Token{ch};
    }

}


vector<Token> tok;

int main(){
  for(Token t = get_token(); t.kind != 'q'; t = get_token()){
    tok.push_back(t);
  }
  for(size_t i = 0; i < tok.size(); i++){
    if(tok[i].kind == '8'){
      cout << "a number token with val = " << tok[i].value << "\n";
    } else if(tok[i].kind == '(' || tok[i].kind == ')' || tok[i].kind == '+' || tok[i].kind == '-' || tok[i].kind == '*' || tok[i].kind == '/'){
      cout << "a token of kind " << tok[i].kind << "\n";
    } else{
      cout << "We received an invalid token of value " << tok[i].kind << '\n';
    }
  }
}
