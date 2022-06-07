#include "histogram.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double>input_numbers(istream& in, size_t count)
{
 vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
 in >> result[i];
    }
    return result;
}

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr<<"Enter bin_count:";//K, кол-во столбцов(корзин)
    cin>>data.bin_count;

    return data;
}


vector<size_t>make_histogram(size_t bin_count, const vector<double>& numbers)
{
  double min, max;
  find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}



int main()
{
   Input results;
   results=read_input(cin);
    //Вывод гистограммы
   auto bins = make_histogram(results.bin_count, results.numbers);
    show_histogram_svg(bins);

return 0;
}
