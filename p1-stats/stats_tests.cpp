/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 0.00001;
static bool almost_equal(double x, double y) {
  return abs(x - y) < epsilon;
}

static bool vector_almost_equal(const vector<double> &a, const vector<double> &b){
  if(a.size()!=b.size()){
    return false;
  }
  for(size_t i=0; i < a.size(); i++){
    if(!almost_equal(a[i], b[i])){
      return false;
    }
  }
  return true;
}

void test_sum_small_data_set();
void test_count_small_data_set();
void test_mean_small_data_set();
void test_median_small_data_set();
void test_min_small_data_set();
void test_max_small_data_set();
void test_stdev_small_data_set();
void test_percentile_small_data_set();
void test_filter_small_data_set();
// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  test_count_small_data_set();
  test_mean_small_data_set();
  test_median_small_data_set();
  test_min_small_data_set();
  test_max_small_data_set();
  test_stdev_small_data_set();
  test_percentile_small_data_set();
  test_filter_small_data_set();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  vector<double> data2;
  data2.push_back(-1.5);
  data2.push_back(2.0);
  data2.push_back(-0.5);

  assert(sum(data2) == 0);

  vector<double> data3;
  data3.push_back(3);
  data3.push_back(2);
  data3.push_back(1);

  assert(sum(data3) == 6);

  vector<double> data4;
  data4.push_back(0.0);
  data4.push_back(0.0);
  data4.push_back(0.0);

  assert(sum(data4) == 0.0);


  cout << "PASS!" << endl;
}

void test_count_small_data_set(){
  cout << "test_count_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(count(data) == 3);

  vector<double> data2;
  data2.push_back(100);

  assert(count(data2) == 1);

  vector<double> data3;
  data3.push_back(-1);
  data3.push_back(-2);
  data3.push_back(-3);

  assert(count(data3) == 3);

  vector<double> data4;
  data4.push_back(1.5);
  data4.push_back(2);
  data4.push_back(3.5);

  assert(count(data4) == 3);

  vector<double> data5;
  data5.push_back(0);
  data5.push_back(0);

  assert(count(data5) == 2);

  vector<double> data6;

  assert(count(data6) == 0);

  cout << "PASS!" << endl;
}

void test_mean_small_data_set(){
  cout << "test_mean_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(almost_equal(mean(data), 2));

  vector<double> data2;
  data2.push_back(1.5);
  data2.push_back(2.0);
  data2.push_back(3.5);

  assert(almost_equal(mean(data2), 2.33333333));

  vector<double> data3;
  data3.push_back(-1.5);
  data3.push_back(2);
  data3.push_back(-3.5);

  assert(almost_equal(mean(data3), -1.0));

  vector<double> data4;
  data4.push_back(0);
  data4.push_back(0);
  data4.push_back(0);

  assert(almost_equal(mean(data4), 0));

  vector<double> data5;
  data5.push_back(0);

  assert(almost_equal(mean(data5), 0));

  cout << "PASS!" << endl;
}

void test_median_small_data_set(){
  cout << "test_median_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(median(data) == 2);

  vector<double> data2;
  data2.push_back(3);
  data2.push_back(2);
  data2.push_back(1);

  assert(median(data2) == 2);

  vector<double> data3;
  data3.push_back(1.5);
  data3.push_back(1.5);

  assert(median(data3) == 1.5);

  vector<double> data4;
  data4.push_back(-1.5);
  data4.push_back(0.0);
  data4.push_back(1.5);

  assert(median(data4) == 0.0);

  vector<double> data5;
  data5.push_back(0.0);
  data5.push_back(0.0);
  data5.push_back(0.0);

  assert(median(data5) == 0.0);

  vector<double> data6;
  data6.push_back(1);
  data6.push_back(2);
  data6.push_back(3);
  data6.push_back(4);

  assert(median(data6) == 2.5);

  vector<double> data7;
  data7.push_back(10);
  data7.push_back(2);
  data7.push_back(8);
  data7.push_back(4);

  assert(median(data7) == 6);

  vector<double> data8;
  data8.push_back(10);

  assert(median(data8) == 10);

  cout << "PASS!" << endl;
}

void test_min_small_data_set(){
  cout << "test_min_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(min(data) == 1);

  vector<double> data2;
  data2.push_back(3);
  data2.push_back(2);
  data2.push_back(1);

  assert(min(data2) == 1);

  vector<double> data3;
  data3.push_back(2.5);
  data3.push_back(2.5);

  assert(min(data3) == 2.5);

  vector<double> data4;
  data4.push_back(-1);
  data4.push_back(-2);
  data4.push_back(-3);

  assert(min(data4) == -3);

  vector<double> data5;
  data5.push_back(0);
  data5.push_back(0);

  assert(min(data5) == 0);

  vector<double> data6;
  data6.push_back(5);

  assert(min(data6) == 5);

  cout << "PASS!" << endl;
}

void test_max_small_data_set(){
  cout << "test_max_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(max(data) == 3);

  vector<double> data2;
  data2.push_back(0);
  data2.push_back(0);

  assert(max(data2) == 0);

  vector<double> data3;
  data3.push_back(-1);
  data3.push_back(-2);

  assert(max(data3) == -1);

  vector<double> data4;
  data4.push_back(-1);

  assert(max(data4) == -1);

  vector<double> data5;
  data5.push_back(3);
  data5.push_back(2);
  data5.push_back(1);

  assert(max(data5) == 3);

  vector<double> data6;
  data6.push_back(3.5);
  data6.push_back(2.5);
  data6.push_back(1.5);

  assert(max(data6) == 3.5);

  cout << "PASS!" << endl;
}

void test_stdev_small_data_set(){
  cout << "test_stdev_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(almost_equal(stdev(data), 1.0));

  vector<double> data2;
  data2.push_back(1.5);
  data2.push_back(1.5);
  data2.push_back(1.5);

  assert(almost_equal(stdev(data2), 0.0));

  vector<double> data3;
  data3.push_back(3);
  data3.push_back(2);
  data3.push_back(1);

  assert(almost_equal(stdev(data), stdev(data3)));

  vector<double> data4;
  data4.push_back(11);
  data4.push_back(12);
  data4.push_back(13);

  assert(almost_equal(stdev(data), stdev(data4)));

  vector<double> data5;
  data5.push_back(2);
  data5.push_back(4);
  data5.push_back(6);

  assert(almost_equal(stdev(data5), 2.0 * stdev(data)));

  vector<double> data6;
  data6.push_back(-1);
  data6.push_back(-2);
  data6.push_back(-3);

  assert(almost_equal(stdev(data6), 1.0));

  vector<double> data7;
  data7.push_back(1);
  data7.push_back(2);

  assert(almost_equal(stdev(data7), sqrt(0.5)));

  cout << "PASS!" << endl;

}

void test_percentile_small_data_set(){
  cout << "test_percentile_small_data_set" << endl;
  vector<double> data;
  data.push_back(3);
  data.push_back(1);
  data.push_back(2);

  assert(almost_equal(percentile(data, 0.0), 1.0));
  assert(almost_equal(percentile(data, 1.0), 3.0));
  assert(almost_equal(percentile(data, 0.5), 2.0));

  vector<double> data2;
  data2.push_back(30);
  data2.push_back(10);
  data2.push_back(20);
  data2.push_back(50);
  data2.push_back(40);
  assert(almost_equal(percentile(data2, 0.1), 14.0));
  assert(almost_equal(percentile(data2, 0.9), 46.0));
  assert(almost_equal(percentile(data2, 0.5), 30.0));

  vector<double> data3;
  data3.push_back(10);
  data3.push_back(0);
  assert(almost_equal(percentile(data3, 0.25), 2.5));

  vector<double> data4;
  data4.push_back(2.5);
  data4.push_back(2.5);
  data4.push_back(2.5);
  data4.push_back(2.5);
  assert(almost_equal(percentile(data4, 0.0), 2.5));
  assert(almost_equal(percentile(data4, 0.6), 2.5));
  assert(almost_equal(percentile(data4, 1.0), 2.5));

   vector<double> data5;
   data5.push_back(50);
   data5.push_back(10);
   data5.push_back(40);
   data5.push_back(20);
   data5.push_back(30);
   
   assert(almost_equal(percentile(data5, 0.25), 20.0));

  cout << "PASS!" << endl;
}

void test_filter_small_data_set(){
  cout << "test_filter_small_data_set" << endl;
  vector<double> locations = {0,1,1,0,0,0,1,0,1};
  vector<double> temps = {40.2, 30.5, 50.0, 12.4, 35.5, 30.5, 22.2, 1.8, 20.0};
  vector<double> locations2 = {-1, 5, -1, 2, -1};
  vector<double> temps2 = {10, 20.5, 32.5, 12, 0};

  vector<double> t1 = filter(temps, locations, 1);
  vector<double> expected1 = {30.5, 50.0, 22.2, 20.0};
  assert(vector_almost_equal(t1, expected1));

  vector<double> t2 = filter(temps, locations, 0);
  vector<double> expected2 = {40.2, 12.4, 35.5, 30.5, 1.8};
  assert(vector_almost_equal(t2, expected2));

  vector<double> t3 = filter(temps, locations, 2);
  assert(t3.empty());

  vector<double> All1 = {1,1,1,1,1,1,1,1,1};
  vector<double> t4 = filter(temps, All1, 1);
  assert(vector_almost_equal(t4, temps));

  vector<double> All0 = {0,0,0,0,0,0,0,0,0};
  vector<double> t5 = filter(temps, All0, 1);
  assert(t5.empty());

  vector<double> t6 = filter(temps2, locations2, -1);
  vector<double> expected6 = {10, 32.5, 0};
  
  assert(vector_almost_equal(t6, expected6));

  vector<double> t7 = filter(temps2, locations2, 5);
  vector<double> expected7 = {20.5};
  assert(vector_almost_equal(t7, expected7));

  cout << "PASS!" << endl;
}






