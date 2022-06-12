#include "histogram.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

string System_info()
{
    string result;
    const size_t MAX_LEN=256;
    char str_info[MAX_LEN];
    DWORD info=GetVersion();
    DWORD mask=0x0000ffff;
    DWORD version=info&mask;
    DWORD version_major=version&0x00ff;
    DWORD version_minor=version&0xff00;
    sprintf(str_info,"Windows v%u.%u",version_major,version_minor);
    result=str_info;
    if((info&0x8000'0000)==0)
    {
        DWORD build = info >> 16;
        sprintf(str_info, " (build %u)\n", build);
        result += str_info;
    }
    return result;
}

string Computer_name()
{
    DWORD max_len=MAX_COMPUTERNAME_LENGTH+1;
    char computer_name[max_len];
    GetComputerNameA(computer_name,&max_len);
    string result=computer_name;
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if(numbers.size() == 0)
    {
        return;
    }

    min = max = numbers[0];
    for(double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        if (max < number)
        {
            max = number;
        }
    }
}

void svg_begin(double width, double height)
{
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

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
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
    const auto SYS_INDENT_LEFT = 20;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    double max_count=bins[0];// максимальное кол-во цифр в гистограмме
    size_t color_mas[bins.size()];// массив, которое присваиваем цвет гистограмме
    for (size_t bin : bins)
    {
       if (max_count<bin)
       {
           max_count=bin;
       }
    }

    for(size_t i=0; i<bins.size(); i++)
    {
      color_mas[i]=size_t((10 - (bins[i] * 9) / max_count))*111;//высчитываем цвет
    }

    for (size_t i=0; i<bins.size(); i++)
    {
    const double bin_width = BLOCK_WIDTH * bins[i];
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, '#'+to_string(color_mas[i]), '#'+to_string(color_mas[i]));
    top += BIN_HEIGHT;
    }
    string sys_info =System_info();
    string comp_name =Computer_name();
    svg_text(SYS_INDENT_LEFT, BIN_HEIGHT * bins.size() + TEXT_BASELINE, sys_info);
    svg_text(SYS_INDENT_LEFT, BIN_HEIGHT * bins.size() + 2 * TEXT_BASELINE, comp_name);
    svg_end();
}


