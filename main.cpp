#include <stdio.h>  
#include <iomanip>
#include <direct.h>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;


string getCurrentDir() {
    char buff[MAX_PATH];
    GetModuleFileName(NULL, buff, MAX_PATH);
    string::size_type position = string(buff).find_last_of( "\\/" );
    return string(buff).substr(0, position)+string("\\data\\");
}

int main(){
    SetWindowPos(GetConsoleWindow(), NULL, 5000, 5000, 0, 0, 0);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

    while(1){

        Mat3b img1 = imread(getCurrentDir()+"0.png");
        Mat3b bckimg = imread(getCurrentDir()+"black.png");

        time_t now = time(0);
        struct tm newtime;
        localtime_s(&newtime,&now);
        int hr = newtime.tm_hour; int min = newtime.tm_min; int sec = newtime.tm_sec;
        string hour = to_string(hr);
        if(hour.length()<2){
            hour='0'+hour;
        }
        string minu = to_string(min);
        if(minu.length()<2){
            minu='0'+minu;
        }
        string secd = to_string(sec);
        if(secd.length()<2){
            secd='0'+secd;
        }
        string time = hour + minu + secd;

        int j=350;

        for(int i=0; i<6; i++){

            Mat insertImage1(bckimg, Rect(j,410,img1.cols,img1.rows));
            string imageName= time[i]+string(".png");
            imread(getCurrentDir() + imageName).copyTo(insertImage1);
            j+=150;

            if(i == 1 || i==3){
                Mat insertImage1(bckimg, Rect(j,410,img1.cols,img1.rows));
                string imageName = "blank.png";
                imread(getCurrentDir() + imageName).copyTo(insertImage1);
                j+=150;
            }
        }
        
        // imshow("Result", bckimg);
        int k = waitKey(50);
        imwrite(getCurrentDir()+"temp.jpg",bckimg);
        string s = getCurrentDir()+"temp.jpg";

        SystemParametersInfo( SPI_SETDESKWALLPAPER, 0, (void*)s.c_str(), SPIF_UPDATEINIFILE );

        if(k == 27){
            break;
        }
    }

    return 0;
    
}