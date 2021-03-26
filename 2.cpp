#include <iostream>
#include <vector>
#include <ostream>

class Mononomial {
    float coefficient;
    int32_t degree;
public:
    Mononomial() {}
    Mononomial(float coefficient, int32_t degree) {
        this->coefficient = coefficient;
        this->degree = degree;
    }
    void Set_coeff(float coefficient) {
        this->coefficient = coefficient;
    }
    void Set_degree(int32_t degree) {
        this->degree = degree;
    }
    float Get_coeff() {
        return coefficient;
    }
    int32_t Get_degree() {
        return degree;
    }
};

class Polynomial {
private:
    std::vector<Mononomial> Polynom;
public:
    Polynomial() {}
    
    Polynomial(std::vector<Mononomial>& a) : Polynom(a) {}
    
    Polynomial operator= (const Polynomial& p) {
        Polynom.resize(p.Polynom.size());
        //
        for (int32_t i = 0; i < p.Polynom.size(); ++i) {
            Polynom[i] = p.Polynom[i];
        }
        return *this;
    }
    bool operator== (Polynomial& p) {
        if (p.Polynom.size() != Polynom.size()) {
            return false;
        }
        for (int32_t i = 0; i < Polynom.size(); i++) {
            if ((Polynom[i].Get_coeff() != p.Polynom[i].Get_coeff()) && (Polynom[i].Get_degree() != p.Polynom[i].Get_degree())) {
                return false;
            }
        }
        return true;
    }
    bool operator!= (Polynomial& p) {
        return !(*this == p);
    }
    Polynomial operator+ (Polynomial& p) {
        std::vector<Mononomial> sum;
        for (int32_t i = 0; i < Polynom.size(); i++) {
            sum.push_back(Polynom[i]);
        }
        for (int32_t i = 0; i < p.Polynom.size(); i++) {
            sum.push_back(p.Polynom[i]);
        }
        return Polynomial(sum);
    }
    void operator+= (Polynomial& p) {
        *this = *this + p;
    }
    Polynomial operator- (Polynomial& p) {
        std::vector<Mononomial> sum;
        float coefficient;
        for (int32_t i = 0; i < p.Polynom.size(); i++) {
            coefficient = -1 * p.Polynom[i].Get_coeff();
            p.Polynom[i].Set_coeff(coefficient);
        }
        for (int32_t i = 0; i < Polynom.size(); i++) {
            sum.push_back(Polynom[i]);
        }
        for (int32_t i = 0; i < p.Polynom.size(); i++) {
            sum.push_back(p.Polynom[i]);
        }
        return Polynomial(sum);
    }
    Polynomial operator- () {
        std::vector<Mononomial> sum;
        float coefficient;
        for (int32_t i = 0; i < Polynom.size(); i++) {
            coefficient = -1 * Polynom[i].Get_coeff();
            sum.push_back(Mononomial(coefficient, Polynom[i].Get_degree()));
        }
        return Polynomial(sum);
    }
    void operator-= (Polynomial& p) {
        *this = *this - p;
    }
    Polynomial operator* (Polynomial& p) {
        std::vector <Mononomial> sum;
        for (int32_t i = 0; i < Polynom.size(); ++i) {
            for (int32_t j = 0; j < p.Polynom.size(); ++j) {
                sum.push_back(Mononomial(p.Polynom[i].Get_coeff() * Polynom[i].Get_coeff(), p.Polynom[i].Get_degree() + Polynom[i].Get_degree()));
            }
        }
        return Polynomial(sum);
    }
    Polynomial operator*= (Polynomial& p) {
        *this = *this * p;
        return Polynomial(p);
    }
    Polynomial operator/ (int32_t k) {
        std::vector<Mononomial> sum;
        for (int32_t i = 0; i < Polynom.size(); i++) {
            sum.push_back(Mononomial(Polynom[i].Get_coeff() / k, Polynom[i].Get_degree()));
        }
        return Polynomial(sum);
    }
    Polynomial operator/= (int32_t k) {
        *this = *this / k;
        return *this;
    }

    friend void operator<< (std::ostream& out, Polynomial& p) {
        for (int32_t i = 0; i < p.Polynom.size(); ++i) {
            std::cout << p.Polynom[i].Get_coeff()<< 'x' << "^" << p.Polynom[i].Get_degree() << ' ';
        }
    }
    friend Polynomial operator>> (std::istream& in, Polynomial& p) {
        float coeffieciet;
        int degree;
        std::cin >> coeffieciet >> degree;
        std::vector <Mononomial> sum;
        for (int32_t i = 0; i < p.Polynom.size(); ++i) {
            sum.push_back(p.Polynom[i]);
        }
        sum.push_back(Mononomial(coeffieciet, degree));
        p = sum;
        return Polynomial(p);
    }

    Mononomial operator[] (int i) {
        return Polynom[i];
    }


};

int main() {
    Mononomial p11(1, 1), p12(2, 1), p13(3, 1);
    Mononomial p21(2, 2), p22(3, 2), p23(4, 2);
    Mononomial p31(3, 3), p32(4, 3), p33(5, 3);
    std::vector <Mononomial> polynomArr1(3);
    std::vector <Mononomial> polynomArr2(3);
    std::vector <Mononomial> polynomArr3(3);
    polynomArr1 = { p11, p12, p13 };
    polynomArr2 = { p21, p22, p23 };
    polynomArr3 = { p31, p32, p33 };
    Polynomial pol1(polynomArr1);
    Polynomial pol2(polynomArr2);
    Polynomial pol3(polynomArr3);
    pol3 = pol1 / 2;
    //pol3 = -pol1;
    std::cout << pol3;
    return 0;
}