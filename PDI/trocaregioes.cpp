#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cv.h>
using namespace cv;
using namespace std;
int main(int argc, char const *argv[])
{
Mat image ;
int altura, largura;
image=imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
if(!image.data){
	cout<<"nao abriu biel.png"<<endl;
}
altura = image.rows;
largura = image.cols;
cout<<"ALTURA: "<< altura<<" LARGURA: " << largura<<endl;
//salvando trechos da imagem antiga em 4 matrizes diferentes.
Mat imagem_final(altura,largura,DataType<uchar>::type);
Mat A = image(Rect(0,0,altura/2,largura/2));
Mat B = image(Rect(altura/2,0,altura/2,largura/2));
Mat C = image(Rect(0,largura/2,altura/2,largura/2));
Mat D = image(Rect(altura/2,largura/2,altura/2,largura/2));
//redistribuindo as partes copiadas da matriz antiga (foto origina) nos quadrantes da imagem final.
A.copyTo(imagem_final(Rect(altura/2,largura/2,altura/2,largura/2)));
B.copyTo(imagem_final(Rect(0,largura/2,altura/2,largura/2)));
C.copyTo(imagem_final(Rect(altura/2,0,altura/2,largura/2)));
D.copyTo(imagem_final(Rect(0,0,altura/2,largura/2)));
//Criando a janela de exibição entitulada de janela_final
imshow("janela_final",imagem_final);
waitKey();
return 0;
}