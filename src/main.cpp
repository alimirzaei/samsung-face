#include "clsAmooNorouz.h"
#include <QtCore>
#include <clsGetLandmarks.h>
clsAmooNorouz* amoo;
extern "C" {

void init() {
    clsAmooNorouz::stuConfig config;
    if(config.loadFromFile("config.xml") == false)
    {
        config.getLandMarksFromUser();
        config.saveToFile("config.xml");
    }
    amoo = new clsAmooNorouz(config);
}

void amooNowroozMaker(const char* inputAddress, char* outputAddress) {
    if(amoo == NULL){
        qDebug() << "you have to init the module!!";
        return;
    }
    QElapsedTimer timer;
    timer.start();
    

    cv::Mat input = cv::imread(std::string(inputAddress));
    cv::Mat output = amoo->getAmooNorouzImage(input);
    //cv::imshow("",output);
    //cv::waitKey(0);
    cv::imwrite(std::string(outputAddress), output);
    qDebug() << timer.elapsed();
}
}


int main(int argc, char *argv[])
{
    init();
    QString base = "/home/ali/Pictures/face/";
    QDir dir(base);
    QStringList files = dir.entryList(QStringList() << "*.jpg" <<"*.png");
    QElapsedTimer timer;
    for( QString file : files) {
        timer.start();
        amooNowroozMaker((base+file).toStdString().c_str(),(base+file.mid(0,file.indexOf("."))+"_out.jpg").toUtf8().data());
        qDebug() << timer.elapsed();
    }

}
