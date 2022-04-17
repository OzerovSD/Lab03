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

void find_minmax(const vector<double>& numbers, double& min, double& max, size_t number_count)
{
    min = numbers[0];
    max = numbers[0];
    for(int i=0; i<number_count; i++)
    {
        if(min>numbers[i])
        {
           min=numbers[i];
        }

        if(max<numbers[i])
        {
            max=numbers[i];
        }
    }
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

void show_histogram_text(const auto bins)
{
    const size_t SCREEN_WIDTH=80;//������������ ���������� ������ ����������
    const size_t MAX_ASTERISK=SCREEN_WIDTH-3-1;//������������ ���������� ���-�� ���������
    size_t max_bin=bins[0];//������������ ������ �������;
        for(size_t bin: bins)
        {
            if(max_bin<bin)
            {
                max_bin=bin;
            }
        }

    for(size_t bin:bins)
    {
        size_t height=bin;//����������, ������� ������ ��� �����
        //���������, ����� �� �������������� ������, � ���� �����, �� ����������� height
        if(max_bin>MAX_ASTERISK)
        {
            height=MAX_ASTERISK*(static_cast<double>(bin)/max_bin);//����������
        }

        if(bin<100)
        {
           cout<<" ";
        }
         if(bin<10)
        {
           cout<<" ";
        }

        cout<<bin<<"|";
        for(size_t i=0; i<height; i++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
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
    find_minmax(numbers, min, max, number_count);

    const auto bins= make_histogram(numbers, bin_count, max, min, number_count);

    //����� �����������
    show_histogram_text(bins);

return 0;
}
