#include <iostream>

class Point {
private:
    int x, y;
public:
    Point() {
        printf("Point()\n");
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        x = x;
        y = y;
    }
    Point(Point& p) {
        x = p.x;
        y = p.y;
    }
    void show() {
        printf("x = %d, y = %d\n", x, y);
    }
    ~Point() {
        printf("~Point()\n");
    }
};

int main()
{
    setlocale(NULL,"RU");

    // Динамическое создание точки и ее удаление
    printf("\nДинамическое создание точки и ее удаление:\n");
    Point* p = new Point();
    p->show();
    delete(p);
    p->show();

    // Статическое создание точки и ее удаление
    printf("\nСтатическое создание точки и ее удаление:\n");
    {
        Point p;
        p.show();
    }
    p->show();

}

