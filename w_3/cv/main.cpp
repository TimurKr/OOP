#include <iostream>
#include <cmath>

using namespace std;




class Point {
    private:
        double x,y,z;
    public:
        // Constructors
        Point(){};
        Point(double x,double y,double z) : x(x),y(y),z(z){}
        
        // Interface
        void X(double x) { this->x = x; }
        void Y(double y) { this->y = y; }
        void Z(double z) { this->z = z; }

        double X() { return x; }
        double Y() { return y; }
        double Z() { return z; }

        // Manipulation
        double populate(double x,double y,double z);
        void print() { cout << "x = " << x << ", y = " << y << ", z = " << z << endl; };

        // Calculations
        double len();

};

double Point::len(){
    return 
        abs(sqrt(
            pow(x, 2) + 
            pow(y, 2) + 
            pow(z, 2)
        ));
}


Point crossProduct(Point v1, Point v2);


class Triangle {
    private:
        Point points[3];

    public:
        // Constructors
        Triangle() {};
        Triangle(Point a, Point b, Point c) { points[0] = a; points[1] = b; points[2] = c; }
        
        // Manipulation
        void populate(Point a, Point b, Point c) { points[0] = a; points[1] = b; points[2] = c; };
        void print();

        // Calculations
        double side_len(unsigned int i);
        Point side(unsigned int i);
        double perimeter();
        double area();
        Point norm(unsigned int i);
        double angle(unsigned int i);

};

void Triangle::print(){
    cout << "Súradnice bodov:" << endl;
    for (int i = 0; i < 3; i++){
        cout << "Bod " << i+1 << ": ";
        points[i].print();
    }
}

Point Triangle::side(unsigned int i){
    i %= 3;
    unsigned int j = (i+1) % 3;
    Point v = Point(
        points[j].X() - points[i].X(), 
        points[j].Y() - points[i].Y(), 
        points[j].Z() - points[i].Z()
    );
    return v;
}

double Triangle::side_len(unsigned int i){
    return side(i).len();
    
}

double Triangle::perimeter() {
    double side_a = side_len(1);
    double side_b = side_len(2);
    double side_c = side_len(3);
    return side_a + side_b + side_c;
}

Point Triangle::norm(unsigned int i = 0){

    Point v1 = side(i);
    Point v2 = side(i+1);

    return crossProduct(v1,v2);
}

double Triangle::area(){
    return norm().len() / 2;
}

double Triangle::angle(unsigned int i){
    Point v1 = side(i);
    Point v2 = side(i+1);
    return crossProduct(v1,v2).len() / (v1.len() * v2.len());
}

Point crossProduct(Point v1, Point v2) { 
    Point v = Point(
        v1.Y() * v2.Z() - v1.Z() * v2.Y(),
        v1.Z() * v2.X() - v1.X() * v2.Z(), 
        v1.X() * v2.Y() - v1.Y() * v2.X()
    );
    return v; 
}


int main(){ 
    Point a = Point(1,1,0);
    Point b = Point(-2,4,0);
    Point c = Point(-2,-2,0);
    Triangle t = Triangle(a,b,c);
    cout << "Obvod je: " << t.perimeter() << endl;
    cout << "Obsah je: " << t.area() << endl;
    cout << "Normála: ";
    t.norm().print();
    for (int i = 0; i < 5; i++){
        cout << "Uhol " << i << ": " << t.angle(i) << endl;
    }
    
}




