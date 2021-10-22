#include<iostream>
#include<opencv2/opencv.hpp>
#include<jsoncpp/json/json.h>
#include"ocr.h"
#include"easypr.h"
int main()
{
    
    easypr::CPlateRecognize pr;
    pr.LoadChineseANN("./model/ann_chinese.xml");
    pr.LoadChineseMapping("./model/province_mapping");
    pr.LoadGrayChANN("./model/annCh.xml");
    pr.LoadANN("./model/ann.xml");
    pr.LoadSVM("./model/svm_hist.xml");
    pr.setResultShow(0);
    pr.setDetectShow(easypr::PR_DETECT_CMSER|easypr::PR_DETECT_SOBEL);
    std::vector<easypr::CPlate> plateVec;
    cv::Mat src = imread("./1.jpg");
    int result = pr.plateRecognize(src,plateVec);

    for(auto plate : plateVec)
    {
        std::cout<< plate.getPlateStr()<<std::endl;
    }
    std::string app_id  = "";
    std::string api_key  = "";
    std::string secret_key  = "";
    aip::Ocr client(app_id,api_key,secret_key);
    Json::Value res;

    cv::Mat img  = cv::imread("./1.jpg");
    std::vector<unsigned char> data_encode;
    cv::imencode(".jpg",img,data_encode);
    std::string image1(data_encode.begin(),data_encode.end());
    res  = client.license_plate(image1,aip::null);
    std::string r = Json::FastWriter().write(res["words_result"]["number"]);
    std::string s=r.substr(1,12);
    std::cout<<s.size()<<std::endl;
    std::cout<<s<<std::endl;
    // cv::VideoCapture cap;
    // cap.open(0);
    // if(!cap.isOpened())
    // {
    //     fprintf(stderr,"camera open failed");
    //     return -1;
    // }
    // cv::namedWindow("Video");
    // while (1)
    // {
    //     cv::Mat img;
    //     cap >> img;
        
    //     if(img.empty())
    //     {
    //         fprintf(stderr,"get image failed");
    //         return -1;
    //     }
    //     cv::imshow("Video",img);
    //     aip::get_file_content("./1,jpg",&image);
    //     result  = client.license_plate(image,aip::null);
    //     if(cv::waitKey(30)>=0) break;
    // }
    // cap.release();
    
    
    return 0;
    
}
