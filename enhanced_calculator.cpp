#include "std_lib_facilities.h"

const char number = '8';
const char quit = 'q';
const char print = ';';
const char name = 'a';
const char let = 'L';
const char help = 'H';
const char sine = 'S';
const char cosine = 'C';
const char tangent = 'T';
const char isin = 's';
const char icos = 'c';
const char itan = 't';
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string helpkey = "help";
const string sinkey = "sin";
const string coskey = "cos";
const string tankey = "tan";
const string arcsinkey = "arcsin";
const string arccoskey = "arccos";
const string arctankey = "arctan";


//--------------------------------
//token class
class Token {
public:
  char kind;
  double value;
  string name;
  Token():kind{0}{}
  Token(char ch):kind{ch}, value{0}{}
  Token(char ch, double val): kind{ch}, value{val} {}
  Token(char ch, string n): kind{ch}, name{n} {}
};

class Token_stream {
public:
  Token get();
  void putback(Token t);
  void ignore(char c);
private:
  bool full{false};
  Token buffer;
};

void Token_stream::putback(Token t){
  buffer = t;
  full = true;
}

void Token_stream::ignore(char c){
  if(full && c == buffer.kind){
    full = false;
    return;
  }
  full = false;

  char ch = 0;
  while(cin >> ch){
    if(ch == c){
      return;
    }
  }
}

Token Token_stream::get(){
  if(full){
    full = false;
    return buffer;
  }
  char ch;
  cin >> ch;
  switch (ch) {
    //special characters
    case print:
    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '/':
    case '*':
    case '%':
    case '=':
    case '^':
      //return token with kind character
      return Token{ch};
    //numbers
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case number: case '9':
    {
      //return token with kind number and value of number
      cin.putback(ch);
      double val;
      cin>>val;
      return Token{number, val};
    }
    //unrecognized characters
    default:
      if(isalpha(ch)){
        string s;
        s+=ch;
        while(cin.get(ch) && (isalpha(ch) || isdigit(ch))){
          s += ch;
        }
        cin.putback(ch);
        if(s == declkey) return Token(let);
        if(s == helpkey) return Token(help);
        if(s == sinkey) return Token(sine);
        if(s == coskey) return Token(cosine);
        if(s == tankey) return Token(tangent);
        if(s == arcsinkey) return Token(isin);
        if(s == arccoskey) return Token(icos);
        if(s == arctankey) return Token(itan);
        return Token(name, s);
      }
      error("bad token");
  }
}

vector<Token> tok;
Token_stream ts;

//---------------------------------------
//variable class and methods
class Variable {
public:
  string name;
  double value;
};

vector <Variable> var_table;

double get_value(string s){
  for(int i = 0; i < var_table.size(); i++)
    if(var_table[i].name == s) return var_table[i].value;
  error("get: undefined variable ", s);
}

void set_value(string s, double d){
  for(int i = 0; i < var_table.size(); i++){
    if(var_table[i].name == s) {
      var_table[i].value = d;
      return;
    }
  }
  error("set: undefined variable ", s);
}

bool is_declared(string var){
  for(int i = 0; i < var_table.size(); i++)
    if(var_table[i].name == var) return true;
  return false;
}

double define_name(string var, double val){
  if(is_declared(var)) error(var, "declared twice");
  var_table.push_back(Variable{var, val});
  return val;
}

//------------------------------------------
//calculator

double expression();

double declaration(){
  Token t = ts.get();
  if(t.kind != name) error("name expected in declaration");
  string var_name = t.name;

  Token t2 = ts.get();
  if(t2.kind != '=') error("= missing in declaration of ", var_name);

  double d = expression();
  define_name(var_name, d);
  return d;
}


double primary(){
  Token t = ts.get();
  switch (t.kind) {
    case '(':
      {
      double d = expression();
      t = ts.get();
      if(t.kind != ')'){
        error("')' expected");
      }
      return d;
    }
    case number:
      return t.value;
    case name:
    {
      Token next = ts.get();
      if(next.kind == '='){
        double d = expression();
        set_value(t.name, d);
        return d;
      }
      else{
        ts.putback(next);
        return get_value(t.name);
      }
    }
    case sine:
    {
      t = ts.get();
      if(t.kind != '(') error("sin: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("sin: ')' expected");
      return sin(d);
    }
    case cosine:
    {
      t = ts.get();
      if(t.kind != '(') error("cos: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("cos: ')' expected");
      return cos(d);
    }
    case tangent:
    {
      t = ts.get();
      if(t.kind != '(') error("tan: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("tan: ')' expected");
      return tan(d);
    }
    case isin:
    {
      t = ts.get();
      if(t.kind != '(') error("arcsin: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("arcsin: ')' expected");
      return asin(d);
    }
    case icos:
    {
      t = ts.get();
      if(t.kind != '(') error("arccos: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("arccos: ')' expected");
      return acos(d);
    }
    case itan:
    {
      t = ts.get();
      if(t.kind != '(') error("arctan: '(' expected");
      double d = expression();
      t = ts.get();
      if(t.kind != ')') error("arctan: ')' expected");
      return atan(d);
    }
    case '-':
      return -primary();
    case '+':
      return primary();
    default:
      if(t.kind != help)
        error("primary expected");
  }
}

double exponent(){
  double left = primary();
  Token t = ts.get();
  while(true){
    switch(t.kind){
      case '^':
        left = pow(left, primary());
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}

double term(){
  double left = exponent();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '*':
        left *= exponent();
        t = ts.get();
        break;
      case '/':{
        double d = exponent();
        if(d == 0){
          error("divide by zero");
        }
        left /= d;
        t = ts.get();
        break;
      }
      case '%':
        {
          double d = primary();
          if(d == 0){
            error("divide by zero");
          }
          left = fmod(left, d);
          t = ts.get();
          break;
        }
      default:
        ts.putback(t);
        return left;
    }
  }
}


double expression(){
  double left = term();
  Token t = ts.get();
  while (true){
    switch (t.kind){
      case '+':
        left += term();
        t = ts.get();
        break;
      case '-':
        left -= term();
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}

void helpFunction(Token t){
  cout << "For simple arithmetic, use the format '3 + 4;'\n" <<
  "This format works for multiplication '3 * 4;', division '3 / 4;',\n" <<
  "subtraction '3 - 4;', and modulus '3 % 4;'. \n\nThe calculator also"<<
  "accepts parenthesis; '2 * (3 + 4);' returns 14, not 10. \n"<<
  "Similarly, order of operations works correctly; '2 + 3 * 4;'\n"<<
  "returns 14, not 20.\n\n"<<
  "The calculator can also calculate trignometric functions using\n"<<
  "the format 'sin(x)' or arcsin(x).\n\n"<<
  "Variables can also be used. To do so, simply type 'let x = 3;'\n"<<
  "To reassign a new value, simply type 'x = 4;'. Variables can be\n"<<
  "treated like numbers.\n";
}

double statement(){
  Token t = ts.get();
  switch(t.kind){
    case let:
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }
}

void clean_up_mess(){
  ts.ignore(print);
}

void calculate(){
  while(cin)
  try {
    cout << prompt;
    Token t = ts.get();
    while(t.kind == print)
      t = ts.get();
    if(t.kind == quit)
      return;
    if(t.kind == help){
      helpFunction(t);
    } else {
      ts.putback(t);
      cout << result << statement() << '\n';
    }
  }
  catch (exception& e){
    cerr << e.what() << '\n';
    clean_up_mess();
  }
}

int main(){
  cout << "Welcome to the enhanced calculator. Type 'help' for more information: \n";
  try{
    define_name("pi",3.1415926535);
    define_name("e", 2.7182818284);

    calculate();
    return 0;
  }
  catch (runtime_error& e){
    cerr << e.what() << "\n";
    return 1;
  }
  catch (...){
    cerr << "exception \n";
    return 2;
  }
}
