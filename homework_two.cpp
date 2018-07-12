#include "std_lib_facilities.h"
#include<string>
#include<vector>

int main(){

  //store line with whitespace
  string sentence;
  getline(cin, sentence);
  //initialize vector
  vector<string> words;
  //store words in vector
  string word = "";
  for(int i = 0; i < sentence.length(); i++){
    if(sentence[i] == ' '){
      words.push_back(word);
      word = "";
    } else{
    word += sentence[i];
    }
  }
  words.push_back(word);
  //sort words alphabetically
  sort(words);
  //output words while counting number each word appears
  int counter = 1;
  for(size_t i = 0; i < words.size()-1; i++){
    if(words[i] == words[i+1]){
      counter++;
    } else {
      cout << words[i] << ": " << counter << "\n";
      counter = 1;
    }
  }
  cout << words[words.size()-1] << ": " << counter << "\n";
}
