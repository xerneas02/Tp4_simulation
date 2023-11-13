#ifndef RABBIT_CATEGORY_H

#define RABBIT_CATEGORY_H

#define MAX_LOOP 100
#define MAJORITY 8
#define MONTH_PER_YEAR 12

#define ull unsigned long long

class RabbitCategory
{
private:
    ull month;   //age in months
    ull male; //number of male rabbit
    ull female; //number of female rabbit
    double survivalRate; //survival rate

    double getSurvivalRate();

public:
    RabbitCategory(ull month);
    ull getMonths();
    ull getMale();
    ull getFemale();
    ull getNbRabbits();
    void transferRabbit(RabbitCategory * category); 
    void setRabbits(ull male, ull female);
};

#endif


