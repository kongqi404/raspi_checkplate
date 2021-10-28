#include<iostream>
#include<ocr.h>
#include<Turnstile_operate.hpp>
#include<Platecheck.hpp>
#include<netoperator.h>
#include<assert.h>
#include<pthread.h>
#include<show_screen.h>
#define MAXLINE 8192
#define MAX_PLATE_SIZE 50
#define MAX_IMAGE_SIZE 314572800
// send ip
char ip[16] = "127.0.0.1";
// send port
char port_client[6] = "9918";
Platecheck Pc;
Turnstile_operate Ts;
// 0 means default 1 means always open -1 means always close  
bool ts_condition = 0;
std::string encode_image(cv::Mat &img)
{
    std::vector<unsigned char> data_encode;
    cv::imencode(".jpg",img,data_encode);
    std::string image1(data_encode.begin(),data_encode.end());
    return image1;
}

// baidu ocr api abstract
Json::Value baiduocr(cv::Mat &img,aip::Ocr &client)
{
    std::string image1 = encode_image(img);
    Json::Value res =  client.license_plate(image1,aip::null);
    return res;
}
Json::Value buf_to_json(char *buf)
{
    std::string json_str = buf;
    Json::Value res = json_str;
    return res;
} 
#define BUTTON 7

void init_button()
{
    pinMode(BUTTON,INPUT);
    
}

void *button_listen(void *args)
{
    while(1)
    {
        if(!digitalRead(BUTTON))
        {
            Ts.ts_start();
            delay(1000);
        }
    }
}
int main()
{
    //baidu api client
    aip::Ocr client("25031553","77nFYZZWBBG3cVj9j0rsKV48","2XE5eOll5DjAD7iOpGwWVRY5rH2l1BSy");

    //easypr abstract class
    pthread_t server_thread,button_thread;
    char buf[MAXLINE];
    // listen service
    init_button();
    assert(pthread_create(&server_thread,NULL,open_listen_service,NULL)==0);
    assert(pthread_create(&button_thread,NULL,button_listen,NULL)==0);
    // receive plate classess
    vector<easypr::CPlate> plateVec;

    init_led();

    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
    {
        fprintf(stderr,"camera open failed");
        return -1;
    }
    cv::namedWindow("Video");
    char *plate_char,*plate_img;
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
        int result=Pc.check_plate_easypr(img,plateVec);
        // std::cout << plateVec.size()<<std::endl;
        for(auto plate : plateVec)
        {
            int s = plate.getPlateStr().size();
            if(plate.getPlateStr().size()>10)
            {
                plate_char = new char[plate.getPlateStr().size()];
                plate_char = (char *)plate.getPlateStr().data();
                show_plate(plate_char);
                send_text(ip,port_client,plate_char);
                get_buf(buf);
                //avoid can't recive data
                delay(1000);

                Json::Value recv_data  = buf_to_json(buf);
                if(recv_data["ts_condition"].asInt()==0)
                {
                    
                    Ts.ts_start();
                    set_ts_condition(0);
                }
                else if(recv_data["ts_condition"].asInt()==1)
                {

                    Ts.ts_normally_open();
                    set_ts_condition(1);
                }
                else
                {
                    Ts.ts_normally_close();
                    set_ts_condition(-1);
                }
                show_car_info((char *)recv_data["car_info"].asString().c_str());                
            }
            //std::cout<<plate_char<<std::endl;
        }

        if(cv::waitKey(30)>=0) break;
    
    }
    cap.release();
    
    
    return 0;
    
}
