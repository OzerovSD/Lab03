#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-7, -2, -4}, min, max);
    assert(min == -7);
    assert(max == -2);
}

void test_equal()
{
    double min = 0;
    double max = 0;
    find_minmax({6, 6, 6}, min, max);
    assert(min == 6);
    assert(max == 6);
}

void test_massive()
{
    double min = 0;
    double max = 0;
    find_minmax({4}, min, max);
    assert(min == 4);
    assert(max == 4);
}

void test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
int
main() {
    test_positive();
    test_negative();
    test_equal();
    test_massive();
    test_empty();
}
