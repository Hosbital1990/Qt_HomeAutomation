#include <iostream>
#include "sensor.h"
#include "vector"
#include    <QDebug>

Sensor::Sensor()
{
    std::cout << "Done!" << std::endl;

}

Sensor::Sensor(std::string_view name, int order_number, int priority, bool power_state, short int operation_state)
    : name(name), order_number(order_number), priority(priority), power_state(power_state), operation_state(operation_state)
{
    std::cout << "Done!" << std::endl;
}

Sensor::~Sensor()
{
    std::cout << "Done!" << std::endl;

}

void Sensor::start_data_reading()
{

    std::cout  << this->name << "sensor start reading data :"<<std::endl;
}

std::vector<double> Sensor::providing_data()
{
  //  qDebug() << "Hello from Providing Data! :)" ;

    return std::vector<double>();
}

bool Sensor::power_trigger()
{
    return false;
}

bool Sensor::change_operation_state(int new_state)
{
    return false;
}
