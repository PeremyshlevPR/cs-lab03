#pragma once
#include <vector>
#include <string>
using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
};

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double left, double baseline, size_t width, double height, string stroke, string fill);
string enter_color();
void show_histogram_svg(const vector<size_t>& bins);
void show_histogram_text(vector<double> bins);
vector <size_t> make_histogram(const Input data);
void find_minmax(const vector<double>& numbers, double& min, double& max);
