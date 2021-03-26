#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Point {
private:
    float x, y;
public:
    void setX(float x) {
        this->x = x;
    };
    void setY(float y) {
        this->y = y;
    };

    Point() {
        x = 0;
        y = 0;
        cout << "set zero" << endl;
    };
    float getX() const {
        return x;
    };
    float getY() const {
        return y;
    };
    Point(float _x, float _y) :x(_x), y(_y) {
        cout << "float" << endl;
    };
    Point(int _x, int _y) :x(_x), y(_y) {
        cout << "int" << endl;
    };
    Point(const Point& t) {
        x = t.getX(); y = t.getY();
    };
    void operator=(const Point& t) {
        x = t.getX(); y = t.getY();
    };
    float ToZero() {
        return sqrt(pow(x, 2) + pow(y, 2));
    };
    ~Point() {}
};

class Line {
protected:
    vector<Point> v;
    float length;
    float pointTOPoint(Point& a, Point& b) {
        return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
    }
public:
    bool islock;
    Line() {
        cout << "Line is created";
    }
    Line(Point m[], int k) {
        for (int i = 0; i < k; i++)
            v.push_back(m[i]);

        if ((v[0].getX() == v[k - 1].getX()) && (v[0].getY() == v[k - 1].getY())) {
            islock = true;
        }
        else {
            islock = false;
        }
    };
    Line(vector<Point>& m) {
        v = m;
    };
    Line(Line& p) {
        v = p.v;
    };

    void operator=(const Line& t) {
        v = t.v;
    }
    void Get_Length() {
        cout << length;
    }
    virtual float perimeter() {
        float length_ = 0.0;
        for (int i = 0; i < v.size() - 1; i++) {
            length_ = length_ + sqrt(pow(v[i + 1].getX() - v[i].getX(), 2) + pow(v[i + 1].getY() - v[i].getY(), 2));
        }
        length = length_;
        return length;
    };

};

class Broken : public Line {
public:
    Broken() {
        cout << "Broken is created";
    };

    Broken(Point m[], int k) : Line(m, k) {}

    Broken(vector<Point>& m) : Line(m) {}

    Broken(Broken& p) : Line(p) {}

    void operator=(const Broken& t) {
        v = t.v;
    }

    float Broken_perimeter() {
        float length = 0.0;
        for (size_t i = 0; i < v.size() - 1; i++) {
            length = length + pointTOPoint(v[i], v[i + 1]);
        }
        return length;
    }
    ~Broken() {}
};

class Broken_Loop : public Line {
public:
    Broken_Loop() {
        cout << "Broken_Loop is created";
    };

    Broken_Loop(Point m[], int k) : Line(m, k) {}

    Broken_Loop(vector<Point>& m) : Line(m) {}

    void operator=(const Broken_Loop& t) {
        v = t.v;
    }

    float Brokenloop_perimeter() {
        float length = Line::perimeter();
        length = length + pointTOPoint(v[0], v[v.size() - 1]);
        return length;
    }
    ~Broken_Loop() {}
};

class Figure {
protected:
    vector<Point> e;
    float perimeter = 0.0;
    float area = 0.0;
public:
    void operator=(const Figure& t) {}
    Figure() {
        area = 0.0;
        perimeter = 0.0;
        cout << "Zero figure";
    }
    Figure(Point m[], int k) {
        for (int i = 0; i < k; i++)
            e.push_back(m[i]);
    }
    Figure(vector<Point>& m) {
        e = m;
    };
    Figure(Figure& p) {
        e = p.e;
    };

    void Isconvex() {
        int i, flag, k, j;
        float z;
        for (i = 0; i < k; i++) {
            j = (i + 1) % (int)k;
            k = (i + 2) % (int)k;
            z = (e[j].getX() - e[i].getX()) * (e[k].getY() - e[j].getY());
            z -= (e[j].getY() - e[i].getY()) * (e[k].getX() - e[j].getX());
            if (z < 0)
                flag |= 1;
            else if (z > 0)
                flag |= 2;
            if (flag == 3)
                cout << "Yes. " << endl;
        }
        if (flag != 0)
            cout << "No. " << endl;
    }
    void Perimeter_Figure() {
        float length_;
        for (int i = 0; i < e.size() - 1; i++) {
            length_ = length_ + sqrt(pow(e[i + 1].getX() - e[i].getX(), 2) + pow(e[i + 1].getY() - e[i].getY(), 2));
        }
        perimeter = length_;
    };
    void Area_Figure() {
        double S = 0;
        double x, y;

        for (int i = 0; i < e.size() - 1; ++i) {
            x = e[i].getX();
            y = e[i + 1].getY();
            S += x * y;
        }
        x = e[e.size() - 1].getX();
        y = e[0].getY();
        S += x * y;

        for (int i = 0; i < e.size() - 1; ++i) {
            x = e[i + 1].getX();
            y = e[i].getY();
            S -= x * y;
        }
        x = e[0].getX();
        y = e[e.size() - 1].getY();
        S -= x * y;

        S = abs(S);
        S = S / 2;

        area = S;
    }

    ~Figure() {}
};

class Triangle : public Figure {

public:
    Triangle() {};
    void operator=(const Triangle& t) {
        e = t.e;
    }
    Triangle(Point m[], int k) : Figure(m, k) {}
    Triangle(vector<Point>& m) : Figure(m) {};
    Triangle(Figure& p) : Figure(p) {};

    void Triangle_Perimeter() {
        Figure::Perimeter_Figure();
        cout << "The perimeter is - " << perimeter << endl;
    }
    void Triangle_Area() {
        Figure::Area_Figure();
        cout << "The area is - " << area << endl;
    }

};

class Trapezoid : public Figure {
public:
    Trapezoid() {};
    void operator=(const Trapezoid& t) {
        e = t.e;
    }
    Trapezoid(Point m[], int k) : Figure(m, k) {}
    Trapezoid(vector<Point>& m) : Figure(m) {};
    Trapezoid(Figure& p) : Figure(p) {};

    void Trapezoid_Perimeter() {
        Figure::Perimeter_Figure();
        cout << "The perimeter is - " << perimeter << endl;
    }
    void Trapezoid_Area() {
        Figure::Area_Figure();
        cout << "The area is - " << area << endl;
    }

};

class Polygon : public Figure {
public:
    void operator=(const Polygon& t) {
        e = t.e;
    }
    Polygon(Point m[], int k) : Figure(m, k) {}
    Polygon(vector<Point>& m) : Figure(m) {};
    Polygon(Figure& p) : Figure(p) {};

    void Polygon_Perimeter() {
        Figure::Perimeter_Figure();
        cout << "The perimeter is - " << perimeter << endl;
    }
    void Polygon_Area() {
        Figure::Area_Figure();
        cout << "The area is - " << area << endl;
    }
};

class Regular_polygon : public Figure {
public:
    void operator=(const Regular_polygon& t) {
        e = t.e;
    }
    Regular_polygon(Point m[], int k) : Figure(m, k) {}
    Regular_polygon(vector<Point>& m) : Figure(m) {};
    Regular_polygon(Figure& p) : Figure(p) {};

    void Polygon_Perimeter() {
        Figure::Perimeter_Figure();
        cout << "The perimeter is - " << perimeter << endl;
    }
    void Polygon_Area() {
        Figure::Area_Figure();
        cout << "The area is - " << area << endl;
    }




};

int main() {

    Point a(float(2.2), 3.2);
    Point b(float(3.2), 4.2);
    Point c(float(4.2), 5.2);
    Point d(float(2.2), 3.2);
    Point e(float(10), 15.2);
    Point array[4] = { b,a,d,c };
    Point ara[4] = { a,c,b,d };
    Point kaa[3] = { c,a,b };
    Point man[3] = { a,c,e };
    //Line pak(array,5);
    Broken ipa(array, 4);
    Broken_Loop apa(ara, 4);
    Triangle opa(man, 3);
    Triangle pop(kaa, 3);
    //pak.perimeter();
    ipa.Broken_perimeter();
    apa.Brokenloop_perimeter();
    opa.Triangle_Area();
    opa.Triangle_Perimeter();

    Figure* t[2];
    t[0] = new Triangle();
    t[1] = new Trapezoid();

    t[0]->Perimeter_Figure();
    t[1]->Perimeter_Figure();

    return 0;
}