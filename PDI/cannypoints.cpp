#include <iostream>
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace cv;
#define STEP 5
#define JITTER 4
#define RAIO 4

int main(int argc, char**argv){
  int width, height,gray;
  int x,y;

  int r = 1,l=20;//l=limiar inferior e r= raio dos circulos ambos para a iteração inicial de um total de n
  vector<int> yrange;
  vector<int> xrange;
  Mat image, frame, pontos, border;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  srand(time(0));
    if(!image.data){
    cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.png";
    exit(0);
    }
  
  width=image.size().width;
  height=image.size().height;


  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  pontos = Mat(height, width, CV_8U, Scalar(255));
  random_shuffle(xrange.begin(), xrange.end());

  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = image.at<uchar>(x,y);
      circle(pontos,
             cv::Point(y,x),
             RAIO,
             CV_RGB(gray,gray,gray),
             -1,
             CV_AA);
    }
  } 
  imshow("pontilhismo 1ª iteracao", pontos);

  imwrite("cannypoints1.png", pontos);
  
   for(int a=0; a<10; a++){
    Canny(image, border, l, 3*l);
    l=l*10;//serão 10 iterações
    for(int i=1; i<width; i++){
      for(int j=1; j<height; j++){
        if(border.at<uchar>(i,j) == 255){
          gray = image.at<uchar>(i,j);
          circle(pontos,
                 cv::Point(j,i),
                 r,
                 CV_RGB(gray,gray,gray),
                 -1,
                 CV_AA);
        }
      }
    }
    r=r+1;
  }
imshow("pontilhismo ultima iteracao",pontos);
imwrite("cannypoints2.png",pontos);

  waitKey();
  
  return 0;
}
