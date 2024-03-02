#include <iostream>

class Point {
private:
    int x, y;
public:
    Point() {
        printf("[Point()]\n");
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        printf("[Point(int x, int y)]\n");
        this->x = x;
        this->y = y;
    }
    Point(Point& p) {
        printf("[Point(Point& p)]\n");
        x = p.x;
        y = p.y;
    }
    void show() {
        printf("[Point::show()] x = %d, y = %d\n", x, y);
    }
    void set(int x, int y) {
        this->x = x;
        this->y = y;
        printf("[Point::set(int x, int y)] x = %d, y = %d\n", x, y);
    }
    void set(Point& p) {
        this->x = p.x;
        this->y = p.y;
        printf("[Point::set(Point& p)] x = %d, y = %d\n", x, y);
    }
    ~Point() {
        printf("[~Point()]\n");
    }
};

class Figure {
public:
    Point center;
    Figure() {
        printf("[Figure()]\n");
        center.set(0, 0);
    }
    Figure(int x, int y) {
        printf("[Figure(int x, int y)]\n");
        center.set(x, y);
    }
    Figure(Figure& f) {
        printf("[Figure(Figure& f)]\n");
        center.set(f.center);
    }
    void show() {
        printf("[Figure::show()]\n");
        center.Point::show();
    }
    ~Figure() {
        printf("[~Figure()]\n");
    }
};

class Circle : public Figure {
    int r;
    Circle(){
        r = 0;
        center.set(0, 0);
        printf("[Circle()]\n");
    }
    Circle(int r) {
        center.set(0,0);
        this->r = r;
        printf("[Circle(int r)]\n");
    }
    Circle(Circle &c){
        this->r = c.r;
        center.set(c.center);
        printf("[Circle(Circle &c)]\n");
    }
    float space(){
        float ans = 3.14 * r * r;
        printf("[Circle::space()] space = %f\n", ans);
        return 3.14 * r * r;
    }
    ~Circle(){
        printf("[~Circle()]\n");
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
        p->show(); // Обращение к неинецилизированной памяти,
                   //так как объект был удален в предыдущей строчке

        // Статическое создание точки и ее удаление
        printf("\nСтатическое создание точки и ее удаление:\n");
        {
            Point p;
            p.show();
        }
        p->show(); // Обращение к неинецилизированной памяти,
                   //так как объект был удален в предыдущей строчке
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

    // Создал объект Figure, который содержит в себе Point
    printf("\nСоздал объект Figure, который содержит в себе Point:\n");
    Figure* f = new Figure();
    f->show();
    delete(f);
    // Время жизни Figure и Point (который внутри Figure) - одинаковое
    // Значит это наиболее сильная связь между классами - композиция
}


