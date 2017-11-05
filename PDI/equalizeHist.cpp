#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image,imagegray,copia;
  int width, height;
  VideoCapture cap;

  Mat hist,hist2;
  int nbins = 128;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(1);

  if(!cap.isOpened()){
    cout << "No camera ";
    return -1;
  }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImg(histh, histw, CV_8UC1, Scalar(0,0,0));
  Mat histImg2(histh, histw, CV_8UC1, Scalar(0,0,0));

  while(1){
    cap >> image;

    cvtColor(image,imagegray,CV_BGR2GRAY);
    equalizeHist(imagegray,copia);

    calcHist(&imagegray, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
     calcHist(&copia, 1, 0, Mat(), hist2, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, histImg2.rows, NORM_MINMAX, -1, Mat());

    histImg.setTo(Scalar(0));
    histImg2.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImg,
           Point(i, histh),
           Point(i, histh-cvRound(hist.at<float>(i))),
           Scalar(128), 1, 8, 0);
    }
     for(int i=0; i<nbins; i++){
      line(histImg2,
           Point(i, histh),
           Point(i, histh-cvRound(hist2.at<float>(i))),
           Scalar(128), 1, 8, 0);
    }


    histImg.copyTo(imagegray(Rect(0, 0 ,nbins, histh)));
    histImg2.copyTo(copia(Rect(0, 0 ,nbins, histh)));

    imshow("NoEqualHist", imagegray);
    imwrite("noequalhist.png",imagegray);
    imshow("equalizeHist",copia);
    imwrite("equalhist.png", copia);
    
    if(waitKey(30) >= 0) break;
  }
  return 0;
}