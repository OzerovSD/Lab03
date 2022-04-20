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

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<text<<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke="black", string fill="black")
{
 cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto NAMECOLOR="darkorange";
    const auto COLOR="#ff8c00";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
    top += BIN_HEIGHT;
}
    svg_end();
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

    show_histogram_svg(bins);


return 0;
}
