#include "temp_sensor.h"
#include<thread>
#include <random>
#include <chrono>

#include    <QDebug>
#include    <QtConcurrent/QtConcurrent>

#include "heater_controller.h"

Heater_Controller::Heater_Controller()
{
    qDebug() << "Defualt constructor of Actuator is called";

}

Heater_Controller::Heater_Controller(std::string_view name, int order_number, int priority, bool power_state, short int operation_state, Sensor* sensor)
    :name(name), order_number(order_number), priority(priority), power_state(power_state), operation_state(operation_state)

{
    qDebug() << "Hello from Second Constructor of Heater_Controler:!!!!!!!!!!!!! " << sensor->name;
    //heater_adjuster_thread = std::jthread(&Heater_Controller::actuator_adjuster,this,sensor);

    // QtConcurrent::run([sensor, this]()
    //                   {
    //     this->actuator_adjuster(sensor);
    // });


    qheater_adjuster_thread = new QThread ;
    this->moveToThread(qheater_adjuster_thread);

    QObject::connect(qheater_adjuster_thread, &QThread::started, this, [sensor,this](){Heater_Controller::actuator_adjuster(sensor);});
    QObject::connect(qheater_adjuster_thread, &QThread::finished, qheater_adjuster_thread, &QThread::deleteLater);
    QObject::connect(qheater_adjuster_thread, &QThread::finished, this, &Heater_Controller::deleteLater);
    qheater_adjuster_thread->start();



}

Heater_Controller::~Heater_Controller()
{
    qDebug() << "Desructur of Heater controller called!";

}


    void Heater_Controller::actuator_adjuster(Sensor *sensor) {
        QThread::sleep(4);

        while(true) {
            if (sensor) {
                // qDebug() << "Attempting to provide sensor data..."
                //          << "Sensor Name: " << sensor
                //          << "   Operation: "<< sensor->operation_state
                // << "   Operation: "<< sensor->providing_data();

            } else {
                qDebug() << "Sensor pointer is null!";
            }
            QThread::msleep(1000);
        }
    }


