#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int extrairalpha (int x, int l1, int l2, int d){
  double alpha = (float)255*(float)1/(float)2*((float)tanh(((float)x-(float)l1)/(float)d)-(float)tanh(((float)x-(float)l2)/(float)d));
  return static_cast<int>(alpha);
}

int main(int, char**){
  Mat imagem,teste,imagemborrada;
  Mat image(256,256, CV_8U, 255);
  Mat imagem_nativa(256,256, CV_8U, 255);
  int width, height;
  Mat resultadopos(256,256, CV_16U);
  Mat resultadoneg(256,256, CV_16U);
  Mat blended;
  float l1 =150;
  float l2 =180;
  float d = 0.5;
  imagem= imread("carros.png",CV_LOAD_IMAGE_COLOR);
  if(!imagem.data)
    cout << "nao abriu carros.png" << endl;
  imagemborrada= imread("carrosborrada.png",CV_LOAD_IMAGE_COLOR);
  if(!imagem.data)
    cout << "nao abriu carrosborrada.png" << endl;

  width=image.size().width;
  height=image.size().height;

  for(int i = 0; i < width; i++){
    for(int j = 0; j<height; j++){
      image.at<uchar>(i, j) = extrairalpha(i, l1, l2, d);
    }
  }

  for(int i=0; i<width; i++){
    for(int j=0; j<height; j++){
      imagem_nativa.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
    }
  }

  cvtColor(image, image, CV_GRAY2RGB);
  cvtColor(imagem_nativa, imagem_nativa, CV_GRAY2RGB);

  multiply(imagem, image, resultadopos, 1.0, CV_16U);
  multiply(imagemborrada, imagem_nativa, resultadoneg, 1.0, CV_16U);

  addWeighted(resultadopos, 0.5, resultadoneg, 0.5, 100.0, blended);
  imwrite("tiltshit_res.png", blended); 

  imwrite("tiltshift_result.png", blended);

  imshow("janela", blended);
  waitKey();
  return 0;
}