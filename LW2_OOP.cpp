#include <iostream>

class Point {
public:
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
    Point(const Point& p) {
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
protected:
    Point center;
public:
    Figure() {
        printf("[Figure()]\n");
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
        center.show();
    }
    ~Figure() {
        printf("[~Figure()]\n");
    }
};

class Circle : public Figure {
private:
    int r;
public:
    Circle(): r(0){
        printf("[Circle()]\n");
    }
    Circle(int r): r(r) {
        printf("[Circle(int r)]\n");
    }
    Circle(Circle &c): Figure(c), r(c.r){
        printf("[Circle(Circle &c)]\n");
    }
    void setCenter(int x, int y) {
        center.x = x;
        center.y = y;
    }
    void show() {
        printf("[Circle::show()] r = %d\n", r);
        center.Point::show();
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

class Section {
private:
    Point* strt;
    Point* end;
public:
    Section(): strt(new Point()), end(new Point()){
        printf("[Section()]\n");
    }
    Section(int x1, int y1, int x2, int y2): strt(new Point(x1, y1)), end(new Point(x2, y2)){
        printf("[Section(int x1, int y1, int x2, int y2)]\n");
    }
    Section(Section& s): strt(new Point(*(s.strt))), end(new Point(*(s.end))){
        printf("[Section(Section& s)]\n");
    }
    void show() {
        printf("[Section::show()]\n");
        strt->show();
        end->show();
    }
    ~Section() {
        printf("[~Section()]\n");
        delete(strt);
        delete(end);
    }
};

int main()
{
    setlocale(NULL,"RU");

    {
        //
        // Динамическое создание точки и ее удаление
        //
        printf("\nДинамическое создание точки и ее удаление:\n");
        Point* p = new Point();
        p->show();
        delete(p);
        p->show(); // Обращение к неинецилизированной памяти,
                   //так как объект был удален в предыдущей строчке
                   
        //
        // Статическое создание точки и ее удаление
        //
        printf("\nСтатическое создание точки и ее удаление:\n");
        {
            Point p;
            p.show();
        }
        p->show(); // Обращение к неинецилизированной памяти,
                   //так как объект был удален в предыдущей строчке
    }
    //
    // Использование различных конструкторов
    //
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

    //
    // Создал объект Figure, который содержит в себе Point
    //
    printf("\nСоздал объект Figure, который содержит в себе Point:\n");
    Figure* f = new Figure();
    f->show();
    delete(f);
    // Время жизни Figure и Point (который внутри Figure) - одинаковое
    // Значит это наиболее сильная связь между классами - композиция

    //
    // Создание Circle (наследника Figure)
    //
    printf("\nСоздание Circle (наследника Figure):\n");
    Circle* c = new Circle();
    c->show(); //скомпилится - так как show() обьявлен публичным в полях класса Circle
    //c->r - не скомпилится так как r - private (доступен только в полях самого класса)
    //c->center - не скомпилистся так как center - protected 
    //(доступен только в полях самого класса и всех его наследников)
    delete(c);

    //
    // Создал объект Section, который хранит указатели на 2 Point
    //
    printf("\nСоздал объект Section, который хранит указатели на 2 Point\n");
    Section* s = new Section(1, 1, 5, 5);
    s->show();
    delete(s);
    //s->show();
    //Вызвано необработанное исключение: нарушение доступа для чтения.
    //this было 0xFFFFFFFFFFFFFFFB.
    //Обратились к неинициализированной памяти - получили runtime ошибку

    //
    // В переменную-указатель на базовый класс поместил объект-потомок (Circle в Figure)
    //
    printf("\nВ переменную-указатель на базовый класс поместил объект-потомок (Circle в Figure)\n");
    Figure* f1 = new Circle();
    f1->show(); // Можно вызвать только методы Figure
    delete(f1); // ~Circle() не вызывается, нооо!
    ((Circle*)f1)->show(); // здесь мы видим что атрибут r обьекта Circle неиницилизирован
    // как так?
    
    printf("\n\n\n");
    Circle* c2 = new Circle(9);
    c2->setCenter(2,3);
    Circle* c1 = new Circle(*c2);
    c2->show();
    c1->show();
}


