#ifndef _Platecheck_H_
#define _Platecheck_H_
#include"easypr.h"

class Platecheck
{
private:
    easypr::CPlateRecognize pr;

public:
    Platecheck();
    ~Platecheck();
    void init_easypr();
    int check_plate_easypr(cv::Mat &img,vector<easypr::CPlate> &plateVec);
    
};

Platecheck::Platecheck()
{
    init_easypr();
}
Platecheck::~Platecheck()
{
}

void Platecheck::init_easypr()
{
    pr.LoadChineseANN("./model/ann_chinese.xml");
    pr.LoadChineseMapping("./model/province_mapping");
    pr.LoadGrayChANN("./model/annCh.xml");
    pr.LoadANN("./model/ann.xml");
    pr.LoadSVM("./model/svm_hist.xml");
    pr.setResultShow(0);
    pr.setDetectShow(easypr::PR_DETECT_CMSER|easypr::PR_DETECT_SOBEL);
}

int Platecheck::check_plate_easypr(cv::Mat &img,vector<easypr::CPlate> &plateVec)
{
    return pr.plateRecognize(img,plateVec);
}

#endif