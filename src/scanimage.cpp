#include<iostream>
#include<ocr.h>
#include<Turnstile_operate.hpp>
#include<Platecheck.hpp>
#include<netoperator.h>
#define MAXLINE 8192
// ip
char ip[16] = "255.255.255.255";
// port
char port[6] = "65535"

// baidu ocr api abstract
Json::Value baiduocr(cv::Mat img,aip::Ocr &client)
{
    std::vector<unsigned char> data_encode;
    cv::imencode(".jpg",img,data_encode);
    std::string image1(data_encode.begin(),data_encode.end());
    Json::Value res =  client.license_plate(image1,aip::null);
    return res;
}
int main()
{
    //baidu api client
    aip::Ocr client("25031553","77nFYZZWBBG3cVj9j0rsKV48","2XE5eOll5DjAD7iOpGwWVRY5rH2l1BSy");

    //easypr abstract class
    Platecheck a;

    // receive plate classess
    vector<easypr::CPlate> plateVec;


    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
    {
        fprintf(stderr,"camera open failed");
        return -1;
    }
    cv::namedWindow("Video");
    while (1)
    {
        cv::Mat img;
        cap >> img;
        if(img.empty())
        {
            fprintf(stderr,"get image failed");
            return -1;
        }
        cv::imshow("Video",img);
        int result=a.check_plate_easypr(img,plateVec);
        // std::cout << plateVec.size()<<std::endl;
        for(auto plate : plateVec)
        {
            send_text(ip,port,);
            std::cout<< plate.getPlateStr()<<std::endl;
        }

        if(cv::waitKey(30)>=0) break;
    
    }
    cap.release();
    
    
    return 0;
    
}
