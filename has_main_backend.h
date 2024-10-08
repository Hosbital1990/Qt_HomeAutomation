#ifndef HAS_MAIN_BACKEND_H
#define HAS_MAIN_BACKEND_H

#include <QThread>
#include <QWidget>

class HAS_Main_Backend : public QWidget
{
    Q_OBJECT
public:
    explicit HAS_Main_Backend(QWidget *parent = nullptr);

    HAS_Main_Backend(std::string_view username, std::string_view password, int user_ID_number);

    int system_ID;
    std::string system_name;

    // program starts from here
    void start_point();

    bool initial_analysis();


    std::string getCurrentTime();
    std::string getCurrentDate();


    ~HAS_Main_Backend();

signals:

public slots:


protected:

    struct Version{

        std::string system_version{"V01.0.0"};
        std::string release_date{"Aug 01, 2024"};
        int order_number {1000};

    };

private:



};


#endif // HAS_MAIN_BACKEND_H
