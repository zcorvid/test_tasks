#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <ostream>

namespace odo
{
template<class T>
class Platform2WheelCounter;

using real = long double;
static constexpr real pi = 2*std::acos(0);

// reduces x to (-base, base]
real ReduceByBase(real x, const real &base = pi)
{
    while (x < -base) x = x + 2*base;
    while (x >= base) x = x - 2*base;
    return x;
}

template<class T = real>
class CounterVariale
{
    T prev;
    T curr;
    friend class Platform2WheelCounter<T>;
};

template<class T = real>
class Platform2WheelCounter
{
private:
    // input parameters:
    T b, R;
    CounterVariale<T> alpha;
    CounterVariale<T> x    ;
    CounterVariale<T> y    ;
    CounterVariale<T> t    ;
    CounterVariale<T> th1  ;
    CounterVariale<T> th2  ;
    CounterVariale<T> Delta;
    CounterVariale<T> s    ;

    void UpdatePrev()
    {
        alpha.prev = alpha.curr;
        x    .prev = x    .curr;
        y    .prev = y    .curr;
        t    .prev = t    .curr;
        th1  .prev = th1  .curr;
        th2  .prev = th2  .curr;
        Delta.prev = Delta.curr;
        s    .prev = s    .curr;
    }

    void UpdateCalculatedVars()
    {
        Delta.curr =   th2.curr - th1.curr;
        s    .curr = ( th2.curr + th1.curr ) / 2.;
    }

    void CalcTarget_trapezoidal()
    {
        alpha.curr = (R / b) * Delta.curr; // alpha can be calculated analitically
        x.curr = x.prev + R * (std::cos(alpha.prev) + std::cos(alpha.curr)) * (s.curr - s.prev) / 2.;
        y.curr = y.prev + R * (std::sin(alpha.prev) + std::sin(alpha.curr)) * (s.curr - s.prev) / 2.;
    }

public:
    Platform2WheelCounter() = delete;
    Platform2WheelCounter(const Platform2WheelCounter&) = delete;
    Platform2WheelCounter(const T &i_b, const T &i_R) : b     (i_b)
                                                      , R     (i_R)
    {
        alpha.curr = 0;
        x    .curr = 0;
        y    .curr = 0;
        t    .curr = 0;
        th1  .curr = 0;
        th2  .curr = 0;
        UpdateCalculatedVars();
    }

    void ProcessData(const T &i_t, const T &i_th1, const T &i_th2)
    {
        UpdatePrev();
        t  .curr = i_t  ;
        th1.curr = i_th1;
        th2.curr = i_th2;
        UpdateCalculatedVars();
        CalcTarget_trapezoidal();
    }

    void PrintResult(std::ostream &out) const
    {
        out << x.curr << " " << y.curr << " " << odo::ReduceByBase(alpha.curr) << std::endl;
    }
};

}

int main(int argc, char *argv[])
{
    using odo::real;
    if (argc >= 2)
    {
        std::string fin_name = std::string(argv[1]);
        std::ifstream fin(fin_name);
        real b, R;
        {
            std::string line;
            std::getline(fin, line);
            std::istringstream lin(line);
            lin >> b >> R;
        }
        odo::Platform2WheelCounter<> worker(b, R);
        std::string line;
        while (std::getline(fin, line))
        {
            // read next data
            std::istringstream lin(line);
            real t, th1, th2;
            lin >> t >> th1 >> th2;
            worker.ProcessData(t, th1, th2);
        }
        worker.PrintResult(std::cout);
    }
    else
    {
        std::cout << "Enter please input file name..." << std::endl;
    }
    return 0;
}
