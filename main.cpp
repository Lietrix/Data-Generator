#include <random>
#include <vector>
#include <fstream>
#include <cmath> 
#include <iostream>
#include <chrono>
using namespace std;


double mean(vector<int> &);
double stdDev(vector<int> &);
double coefficientOfVariation(vector<int> &data);
vector<int> getRandomSample(const vector<int> &, int, mt19937 &);

int main() {

    ifstream infile("Data.txt");
    if(!infile) {
        cerr << "Unable to open file Data.txt";
        return 1;
    }
    ofstream ofile("Write.txt");
    if(!ofile) {
        cerr << "Unable to write to file Write.txt";
        return 1;
    }

    // Read Data
    int sample;
    vector<int> dataSet;
    while(infile >> sample) {
        dataSet.push_back(sample);
    }
    infile.close();

    // Random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // Sample size and number of iterations
    int sampleSize = 50; // You can change this to 10 as well
    int iterations = 10000;

    for (int i = 0; i < iterations; ++i) {
        vector<int> sample = getRandomSample(dataSet, sampleSize, gen);
        double cv = coefficientOfVariation(sample);
        ofile << cv << endl;
    }

    ofile.close();
    return 0;
}

vector<int> getRandomSample(const vector<int> &data, int sampleSize, mt19937 &gen) {
    vector<int> sample;
    uniform_int_distribution<> dis(0, data.size() - 1);
    for (int i = 0; i < sampleSize; ++i) {
        sample.push_back(data[dis(gen)]);
    }
    return sample;
}

double mean(vector<int> &data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (int value : data) {
        sum += value;
    }
    return sum / data.size();
}


double stdDev(vector<int> &data) {
    if (data.size() <= 1) {
        return 0.0;
    }

    double avg = mean(data);
    double sum = 0.0;
    for (int value : data) {
        sum += (value - avg) * (value - avg);
    }
    return sqrt(sum / (data.size() - 1));
}

double coefficientOfVariation(vector<int> &data) {
    double avg = mean(data);
    if (avg == 0) {
        // Avoid division by zero
        return 0.0;
    }
    double stdDeviation = stdDev(data);
    return stdDeviation / avg;
}