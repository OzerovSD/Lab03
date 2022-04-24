#include "histogram.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double>input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
        {
        cin >> result[i];
        }
    return result;
}



vector<size_t>make_histogram(const auto numbers, size_t bin_count, double max, double min, size_t number_count)
{
    vector<size_t> bins(bin_count,0);//����������, ������������ ���-�� ����� � �������� ���������
    double bin_size=(max-min)/bin_count;//������ ���������(�������)
    for(size_t i=0; i<number_count; i++)
    {
        bool found = false;
        for(size_t j=0; j<(bin_count-1)&& !found; j++)
        {
            auto lo=min + j*bin_size;//������ ������� �������
            auto hi=min + (j+1)*bin_size;//������� ������� �������
            if((lo <=numbers[i])&&(numbers[i]<hi))
            {
                bins[j]++;
                found=true;
            }
        }
        if (!found)//��� ������������� �����
        {
            bins[bin_count-1]++;//��������� ������� ����������� �� 1
        }
    }
    return bins;
}


int main()
{
    // ���� ������
    size_t number_count;//N, ���-�� �����
    cerr<<"Enter number_count:";
    cin>>number_count;

    const auto numbers = input_numbers(number_count);
     size_t bin_count;
     cerr<<"Enter bin_count:";//K, ���-�� ��������(������)
     cin>>bin_count;

    //������ �����������
    double min, max;
    find_minmax(numbers,min, max);



    const auto bins= make_histogram(numbers, bin_count, max, min, number_count);

    //����� �����������

    show_histogram_svg(bins);



return 0;
}
