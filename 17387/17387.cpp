#include <iostream>

struct Point
{

    long long x;
    long long y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}
    Point &operator=(const Point &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    ~Point() {}
};

const bool operator>(const Point &p1, const Point &p2)
{
    return p1.x > p2.x || (p1.x == p2.x && p1.y > p2.y);
}

const bool operator<=(const Point &p1, const Point &p2)
{
    return p1.x < p2.x || (p1.x == p2.x && p1.y <= p2.y);
}

const bool operator==(const Point &p1, const Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

std::istream &operator>>(std::istream &in, Point &p)
{
    in >> p.x >> p.y;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Point &p)
{
    out << p.x << ' ' << p.y;
    return out;
}

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

struct Line
{
    Point p1;
    Point p2;
    Line() : p1(0, 0), p2(0, 0) {}
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}
    Line(const Line &l) : p1(l.p1), p2(l.p2) {}
    Line &operator=(const Line &l)
    {
        p1 = l.p1;
        p2 = l.p2;
        return *this;
    }
    ~Line() {}
};

const bool operator==(const Line &l1, const Line &l2)
{
    return l1.p1 == l2.p1 && l1.p2 == l2.p2;
}

std::istream &operator>>(std::istream &in, Line &l)
{
    in >> l.p1 >> l.p2;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Line &l)
{
    out << l.p1 << ' ' << l.p2;
    return out;
}

const int ccw(const Point &p1, const Point &p2, const Point &p3)
{
    long long res = (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y) - (p1.y * p2.x + p2.y * p3.x + p3.y * p1.x);
    if (res > 0)
        return 1;
    else if (res < 0)
        return -1;
    else
        return 0;
}

const int is_Lines_crossed(Line &L1, Line &L2)
{
    int res1 = ccw(L1.p1, L1.p2, L2.p1) * ccw(L1.p1, L1.p2, L2.p2);
    int res2 = ccw(L2.p1, L2.p2, L1.p1) * ccw(L2.p1, L2.p2, L1.p2);
    if (res1 == 0 && res2 == 0)
    {
        if (L1.p1 > L1.p2)
        {
            swap(L1.p1, L1.p2);
        }
        if (L2.p1 > L2.p2)
        {
            swap(L2.p1, L2.p2);
        }
        return L2.p1 <= L1.p2 && L1.p1 <= L2.p2;
    }
    return res1 <= 0 && res2 <= 0 ? 1 : 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    Line L1, L2;
    std::cin >> L1 >> L2;

    std::cout << is_Lines_crossed(L1, L2) << '\n';
    return 0;
}