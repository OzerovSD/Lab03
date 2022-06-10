#include "histogram.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <curl/curl.h>
#include <sstream>
#include <string>

using namespace std;

vector<double>input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
    in>>result[i];
    }
    return result;
}


Input read_input(istream& in, bool prompt)
{
    Input data;
    if (prompt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if (prompt)
    cerr << "enter bin count: ";
    in >> data.bin_count;
    return data;
}


vector<size_t>make_histogram(struct Input name)
{
  double min, max;
  find_minmax(name.numbers, min, max);
    vector<size_t> bins(name.bin_count);
    for (double number : name.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * name.bin_count);
        if (bin == name.bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

Input download(const string& address) {
    stringstream buffer;
    CURL *curl = curl_easy_init();
    if(curl)
        {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            {
                cerr <<curl_easy_strerror(res)<<endl;
                exit(1);
            }
        curl_easy_cleanup(curl);
        }
    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    Input input;
    if (argc>1)
        {
        input = download(argv[1]);
        }
    else
        {
        input = read_input(cin, true);
        }
    {
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);


return 0;
}
