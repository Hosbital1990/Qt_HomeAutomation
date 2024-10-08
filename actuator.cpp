
#include "actuator.h"

Actuator::Actuator(){

    std::cout << "Defualt constructor of Actuator is called"<<std::endl;
}

Actuator::Actuator(std::string_view name, bool power_state, short int operation_state)
    : name(name), power_state(power_state), operation_state(operation_state)
{

    std::cout << "Main constructor of Actuator is called"<<std::endl;


}

Actuator::~Actuator()
{

    std::cout << "Desructur of Actuator called!"<<std::endl;

}

void Actuator::actuator_adjuster(Sensor *sensor)
{

    auto sensor_data = sensor->providing_data();
}
