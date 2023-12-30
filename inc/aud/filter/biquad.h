#include <vector>
#include <functional>

/* 
 *  --- DIRECT FORM I --- DIFFERENCE EQUATION ---
 *
 * y[n] = (b0/a0) * x[n]
 *      
 *      + (b1/a0) * x[n-1]
 *      + (b2/a0) * x[n-2]
 *
 *      - (a1/a0) * y[n-1]
 *      - (a2/a0) * y[n-2]
 *
 *
 *
 *
 *
 *
 * */
namespace Biq {
    struct coe {
        float a0;
        float a1;
        float a2;
        float b0;
        float b1;
        float b2;
    };
    // Output is vector of coefficients {a0,a1,a2,b0,b1,b2}
    class FilterStrategy {
        public:
            virtual coe calc_coe() const =0;

    };

    class LowPassStgy : public FilterStrategy {
        public:
            coe calc_coe() const override;
        
    };

}  
class Biquad {

    public:
       Biquad (Biq::FilterStrategy&& type, float frequency); 
       Biquad(const Biquad& other) = delete;
       Biquad& operator=(const Biquad& other) = delete;

       Biquad(Biquad&& other) {

       }
       Biquad& operator=(Biquad&& other) {
           return *this;
       }
        void set_source(std::function<float()> func);

    private:
        std::function<float()> source;
        std::vector<float> coe_a;
        std::vector<float> coe_b;
        std::vector<float> prev_in;
        std::vector<float> prev_out;

        float m_gain;

};
