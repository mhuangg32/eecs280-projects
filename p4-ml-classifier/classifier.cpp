#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include "csvstream.hpp"
using namespace std;

// EFFECTS: Return a set of unique whitespace delimited words
set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

class Classifier{
public:
  void train(const map<string, string> &row){
    const string label = row.at("tag");
    const string content = row.at("content");
    total_posts++;
    label_num[label]++;
    set<string> words = unique_words(content);
    for(const string &w:words){
      word_num[w]++;
      label_word_num[label][w]++;
      word.insert(w);
    }
  }
  int get_total_posts(){
    return total_posts;
  }
  int get_word_size() const{
    return word.size();
  }
  map<string, int> get_label_num() const{
    return label_num;
  }
  map<string, map<string,int>> get_label_word_num() const{
    return label_word_num;
  }
  //ln P(C)
  double log_prior(const string &label) const{
    return log(static_cast<double>(label_num.at(label))/total_posts);
  }
  //ln P(w|C)
  double log_likelihood_cal(const string &label, const string &word) const{
    return log(static_cast<double>(label_word_num.at(label).at(word))
                                              /(label_num.at(label)));
  }
  const map<string, int>& get_word_num() const{
    return word_num;
  }
  //log-probability score for one label given post content
  double score(const string &label, const set<string> &words) const{
    double s = log_prior(label);
    for(const string &w : words){
      if(label_word_num.count(label) && 
            label_word_num.at(label).count(w)){
              s+=log_likelihood_cal(label, w);
            }else if(word_num.count(w)){
              s+=log(static_cast<double>(word_num.at(w))/total_posts);
            }else{
              s+=log(1.0/total_posts);
            }
    }
    return s;
  }
  string predict(const string &content) const{
    set<string> words = unique_words(content);
    string best_label;
    double best_score = -1e300;
    for (const auto &lc : label_num) {
        double s = score(lc.first, words);
        if (s > best_score || 
            ((s == best_score) && (lc.first < best_label))) {
            best_score = s;
            best_label = lc.first;
        }
    }
    return best_label;
  }




private:
  int total_posts=0;
  set<string> word;
  map<string, int> label_num;
  map<string, int> word_num;
  map<string,map<string, int>> label_word_num;
};

void print_debug_info(const Classifier &c) {
  cout << "vocabulary size = " << c.get_word_size() << endl;
  cout << endl;
  cout << "classes:" << endl;
  for (const auto &a : c.get_label_num()) {
      cout << "  " << a.first << ", " << a.second
          << " examples" << ", log-prior = " << c.log_prior(a.first)
          << endl;
    }
  cout << "classifier parameters:" << endl;
  for (const auto &a : c.get_label_word_num()) {
    for (const auto &b :a.second) {
      cout << "  " << a.first << ":" << b.first
          << ", count = " << b.second
          << ", log-likelihood = "
          << c.log_likelihood_cal(a.first, b.first) << endl;
        }
    }
    cout << endl;
  }

void run_test(const Classifier &c, const string &filename) {
  ifstream fin(filename);
  if(!fin.is_open()){
    cout << "Error opening file: " << filename << endl;
      return;
    }
  fin.close();
  csvstream test_read(filename);
  int total= 0;
  int correct=0;
  map<string, string> r2;
  while(test_read >> r2){
    string true_label = r2["tag"];
    string content = r2["content"];
    string predicted = c.predict(content);
    double s = c.score(predicted, unique_words(content));
    cout << "  correct = " << true_label
        << ", predicted = " << predicted
        << ", log-probability score = " << s << endl;
    cout << "  content = " << content << endl;
    cout << endl;
    total++;
    if(predicted == true_label){
      ++correct;
    }
  }
  cout << "performance: " << correct << " / " << total
      << " posts predicted correctly" << endl;
}


int main(int argc, char *argv[]) {
  cout.precision(3);
  //check if it is 2 or 3
  if(argc != 2 && argc!=3){
    cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
    return 1;
  }
  ifstream fin(argv[1]);
  if(!fin.is_open()){
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }
  fin.close();
  //read the rows
  csvstream train_read(argv[1]);
  Classifier c;
  if(argc==2){
    cout << "training data:" << endl;
  }
  map<string, string> r;
  //print and train
  while(train_read >> r){
    if(argc==2){
      cout << "  label = "<< r["tag"]
      <<", content = " <<r["content"]<<endl;
    }
    c.train(r);
  }
  cout << "trained on "<< c.get_total_posts() << " examples"<<endl;

  if(argc == 2){
    print_debug_info(c);
  }

  if(argc==3){
    cout << endl;
    cout << "test data:" << endl;
    run_test(c, argv[2]);
  }
}
