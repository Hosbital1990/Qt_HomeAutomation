

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include<thread>
#include <random>
#include <chrono>

#include "sensor.h"
#include "temp_sensor.h"

class Actuator : public QObject{

public:

    Actuator();
    Actuator(std::string_view name, bool power_state, short int operation_state);
    virtual ~Actuator();

    virtual void actuator_adjuster(Sensor* sensor);

private:
    std::string_view name;
    bool power_state;
    short int operation_state;



};


#endif // ACTUATOR_H
