#include "clsAmooNorouz.h"
#include <QtCore>

clsAmooNorouz* amoo;
extern "C" {

void init() {
    clsAmooNorouz::stuConfig config;
    if(config.loadFromFile("config.xml") == false)
        config.saveToFile("config.xml");
    amoo = new clsAmooNorouz(config);
}

void amooNowroozMaker(char* inputAddress, char* outputAddress) {
    if(amoo == NULL)
        qDebug() << "you have to init the module!!";
    cv::Mat input = cv::imread(std::string(inputAddress));
    cv::Mat output = amoo->getAmooNorouzImage(input);
    cv::imwrite(std::string(outputAddress), output);
}


}
int main(int argc, char *argv[])
{
    amooNowroozMaker("/home/ali/Pictures/test3.jpg","/home/ali/Pictures/out2.jpg");

}
