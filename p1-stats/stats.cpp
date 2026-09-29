// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

int count(vector<double> v) {
    return v.size();
}

double sum(vector<double> v) {
    double sum=0.0;
    for(size_t i=0; i<v.size();i++){
        sum+=v[i];
    }
    return sum;
}

double mean(vector<double> v) {
    return sum(v)/count(v);
}

double median(vector<double> v) {
    int num = count(v);
    vector<double> sorted;
    std::sort(v.begin(),v.end());
    if(num%2 == 0){
        return (v[num/2]+v[num/2-1])/2;
    }else{
        return v[num/2];
    }
}

double min(vector<double> v) {
    double min = v[0];
    for(size_t i=1; i< v.size(); i++){
        if(min > v[i]){
            min = v[i];
        }
    }
    return min;
}

double max(vector<double> v) {
    double max = v[0];
    for(size_t i=1; i< v.size(); i++){
        if(max < v[i]){
            max = v[i];
        }
    }
    return max;
}

double stdev(vector<double> v) {
    double meanv = mean(v);
    double sum = 0.0;
    for(size_t i=0;i<v.size();i++){
        sum+= ((v[i])-meanv)*((v[i])-meanv);
    }
    return sqrt((1.0/(count(v)-1))*sum); 
}

double percentile(vector<double> v, double p) {
    int n = count(v);
    std::sort(v.begin(),v.end());
    double rank = p*(n-1)+1;
    double kDouble = 0;
    double d = 0;
    d = modf(rank, &kDouble);
    int k = static_cast<int>(kDouble);
    if(k<n){
        double vp = 0;
        double vk = v[k-1];
        double vk_1 = v[k];
        vp = vk + d*(vk_1-vk);
        return vp;
    }else{
        return v[n-1];
    }


}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
    vector<double> criteria_1 = {};
    for(size_t i=0; i<criteria.size(); i++){
        if(criteria[i]==target){
            criteria_1.push_back(v[i]);
        }
    }
    return criteria_1;
}
