#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects=0,nobjectscomburaco=0,tonNpossuiBuraco=150,tonPossuiBuraco=80;
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;
//criando a margem de 1 pixel em tom 255 (branco)
for(int x=0;x<height;++x){
  for (int y = 0; y < width; ++y)
  {
    if(x==0 || x== height-1){
      image.at<uchar>(x,y)=255;
    }
    else if(y==0 || y==width-1){
      image.at<uchar>(x,y)=255;
    }
  }
}
//Tira todas as bolhas que tocam a margem criada e a mesma
floodFill(image,p,0);
//Cria o plano de fundo com valor diferente do aplicado aos buracos das bolhas
floodFill(image,p,1);
// busca  e rotulação dos objetos presentes na imagem, assumindo que todos não tem buraco 
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
		nobjects++;
		p.x=j;
		p.y=i;
		floodFill(image,p,tonNpossuiBuraco);
	  }
	}
}
//busca objetvos com buraco, dentro do universo dos objetos que foram encontrados  e rotulados antes
for (int x = 0; x < height; ++x)
{
  for (int y = 0; y < width; ++y)
  {
    if(image.at<uchar>(x,y)== tonNpossuiBuraco || image.at<uchar>(x,y)== tonPossuiBuraco){
      p.x=y;
      p.y=x;
    }
    else if(image.at<uchar>(x,y)==0){
      if (image.at<uchar>(p.y,p.x)==tonNpossuiBuraco)
      {
        floodFill(image,p,tonPossuiBuraco);
        nobjectscomburaco++;
      }
      p.x=y;
      p.y=x;
      floodFill(image,p,tonPossuiBuraco);
    }
  }
}
  cout<<"Elementos sem buraco(s): "<<(nobjects-nobjectscomburaco)<<endl;
  cout<<"Elementos com buraco(s):" << nobjectscomburaco<<endl;
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}
