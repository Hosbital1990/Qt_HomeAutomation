
#include<QThread>
#include <random>
#include <chrono>
#include "memory_interface.h"
#include "temp_sensor.h"
#include   <QDebug>
Temp_Sensor::Temp_Sensor(){}
Temp_Sensor::Temp_Sensor(std::string_view name, int order_number, int priority, bool power_state, short int operation_state)
    :name(name), order_number(order_number), priority(priority), power_state(power_state),operation_state(operation_state)
{
    //call temp data reading thread as soon as temp object created
    qDebug() << "Hello from Temp sensor constructor!!!!!!!!!!!!!" << this->name ;

    //     temp_data_reading_thread= std::jthread(&Temp_Sensor::start_data_reading,this);

    qtemp_data_reading_thread = new QThread ;
    this->moveToThread(qtemp_data_reading_thread);

    QObject::connect(qtemp_data_reading_thread, &QThread::started, this, &Temp_Sensor::start_data_reading);
    QObject::connect(qtemp_data_reading_thread, &QThread::finished, qtemp_data_reading_thread, &QThread::deleteLater);
    QObject::connect(qtemp_data_reading_thread, &QThread::finished, this, &Temp_Sensor::deleteLater);
    qtemp_data_reading_thread->start();

}

Temp_Sensor::~Temp_Sensor()
{
    qDebug() << "Distruted Temp!" ;
}

void Temp_Sensor::start_data_reading(){

    qDebug() << "Hello from Start data reading!" ;

    while (true) {
        raw_temp_data.push_back(560);
        //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
        QThread::msleep(500);
    }
}

std::vector<double> Temp_Sensor::providing_data() {

 //   qDebug() << "Hello from Providing Data! :)" ;

    return raw_temp_data;
}



std::string Temp_Sensor::get_DataBase_name(){

    return DataBase_name ;

}
