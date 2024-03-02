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
        printf("Point(int x, int y)\n");
        this->x = x;
        this->y = y;
    }
    Point(Point& p) {
        printf("Point(Point& p)\n");
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

    {
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

    // Использование различных конструкторов
    printf("\nИспользование разных конструкторов:\n");
    Point* p = new Point();
    p->show();

    Point* p1 = new Point(5,5);
    p1->show();
    
    Point* p2 = new Point(*p1);
    p2->show();
    
    delete(p);
    delete(p1);
    delete(p2);
    
}


