#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include "gnuplot_i.hpp"

using namespace std;
using namespace Eigen;

struct misra1a_functor
{
    misra1a_functor(int inputs, int values, double *x, double *y)
        : inputs_(inputs), values_(values), x(x), y(y) {}

    double *x;
    double *y;

    int operator()(const VectorXd& b, VectorXd& fvec) const
    {
        for (int i = 0; i < values_; ++i) {
            fvec[i] = b[0]*(1.0 - exp(-b[1]*x[i])) - y[i] ;
        }
        return 0;
    }

    // Differential, Jacobian matrix
    int df(const VectorXd& b, MatrixXd& fjac)
    {
        for (int i = 0; i < values_; ++i) {
            fjac(i, 0) = (1.0 - exp(-b[1]*x[i]));
            fjac(i, 1) = (b[0]*x[i] * exp(-b[1]*x[i]));
        }
        return 0;
    }

    const int inputs_;
    const int values_;
    int inputs() const { return inputs_; }
    int values() const { return values_; }
};

int main()
{
    const int n = 2; // beta1, beta2
    int info;

    VectorXd p(n); // Initialize beta1 and beta2
    p << 500.0, 0.0001;

    // Input data
    double xa[] = {77.6E0, 114.9E0, 141.1E0, 190.8E0, 239.9E0, 289.0E0, 332.8E0, 378.4E0, 434.8E0, 477.3E0, 536.8E0, 593.1E0, 689.1E0, 760.0E0};
    double ya[] = {10.07E0, 14.73E0, 17.94E0, 23.93E0, 29.61E0, 35.18E0, 40.02E0, 44.82E0, 50.76E0, 55.05E0, 61.01E0, 66.40E0, 75.47E0, 81.78E0};

    vector<double> x(&xa[0], &xa[14]);
    vector<double> y(&ya[0], &ya[14]);

    misra1a_functor functor(n, x.size(), &x[0], &y[0]);
    LevenbergMarquardt<misra1a_functor> lm(functor);
    info = lm.minimize(p);

    cout << p[0] << " " << p[1] << endl;

    Gnuplot g1("test");
    g1.set_title("test");
    g1.set_style("points").plot_xy(x, y);

    stringstream str;
    str << p[0] << "*(1.0-exp(-" << p[1] << "*x))";

    g1.set_style("lines").plot_equation(str.str());

    getchar();
    return 0;
}

