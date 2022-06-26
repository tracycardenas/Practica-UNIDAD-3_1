
#include "LBPDescriptor.hpp"
#include "lbplibrary.hpp"

#include <iostream>
#include <cstdlib>

// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp> // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp> // Lectura y escritura de videos

#include <opencv2/objdetect/objdetect.hpp> // Para realizar detección de objetos


#include <random>

#include <cmath>
#include <cstring>
#include <sstream> // Librería para manejo de flujos de texto y datos. Permite realizar conversiones de tipo.
#include <vector> // Librería para uso de arreglos dinámicos.
#include <fstream> // Librería para manejo de archivos (lectura y escritura)

#include <filesystem>
//#include <opencv2/opencv.hpp> // Permite cargar todas las librerías de OpenCV

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV para llamar a los métodos de forma más directa
using namespace lbplibrary;

double calculateDistance(vector<int> x, vector<int> y)
{
    int i1,conta=1,contb=1;    
    float resta=0,distancia;   //Defino ambos arrays y 2 contadores


    for (i1=0;i1<x.size();i1++)    //Bucle para restar componentes y elevarlas a 2
        {
        resta=resta+pow(x[i1]-y[i1],2);
        }
    distancia=sqrt(resta);
    return distancia;
}
double minElement(vector<double> v){
    double min = INT_MAX;
    for (double i: v){
        if (min > i){
            min = i;
        }
    }
    return min;
}

int main(int argc, char *argv[]){

    vector<vector<int>> histogramas;
    LBPDescriptor *lbp = new LBPDescriptor();
    LBP *lbp2;
	lbp2 = new OLBP;
    ofstream MyFile("Histogramas.txt");

    vector<string> ficheros = lbp->listarDir("/home/computacion/Descargas/VisionPorComputador/BoletinPractica3/Clases");
    for(string carpetas:ficheros){
        vector<string> ficherosClases = lbp->listarDir(carpetas);
        for(string pathImagenes:ficherosClases){
            Mat img = imread(pathImagenes);
            resize(img, img, Size(320, 240));

            string n1,n2,n3,n4,n5,n6,n7,n8,n9,n10;
            stringstream ficheror(pathImagenes);
            getline(ficheror, n1,'/');
            getline(ficheror, n2,'/');
            getline(ficheror, n3,'/');
            getline(ficheror, n4,'/');
            getline(ficheror, n5,'/');
            getline(ficheror, n6,'/');
            getline(ficheror, n7,'/');
            getline(ficheror, n8,'/');
            getline(ficheror, n9,'/');
            

            //Metodo para transformar a espacio de color Cielab

            cvtColor(img, img, COLOR_BGR2Lab);
            imshow(n9+" | "+n8, img);
            show_multi_histogram(img);
            Mat img_lbp;
            

            lbp2->run(img, img_lbp);
            normalize(img_lbp, img_lbp, 0, 255, cv::NORM_MINMAX, CV_8UC1);

            imshow("lbp", img_lbp);
            imwrite("/home/computacion/Descargas/VisionPorComputador/BoletinPractica3/LBP_HIST/lbp_"+n8+"_"+n9,img_lbp);
            Mat lpb_histograma = show_histogram("lbp_hist", img_lbp);
            imwrite("/home/computacion/Descargas/VisionPorComputador/BoletinPractica3/LBP_HIST/lbpHisto_"+n8+"_"+n9,lpb_histograma);

            

            //Calculo de Histograma / Descriptor LBP
            MyFile<<"***************************************************************************************\n";
            MyFile<<"Hstograma para "+n9+" que pertenece a la " +n8+"\n";
            MyFile<<"\n";
            

            vector<int> histo1 = lbp->histogramaLBP(img);
            
            for(int i=0;i<256;i++){
                MyFile<<to_string(histo1[i])+" |";
                
            }
            histogramas.push_back(histo1);

            MyFile<<" \n";
            MyFile<<"\n";
                
            
            waitKey(0);
            destroyAllWindows();

        }

        
    }
    
    //CALCULO DE DISTANCIA EUCLIDEA PARA COMPARAR HISTOGRAMAS
    //ARREGLO histogramas
    //Posicion 0 -> Img 1 Clase 2
    //Posicion 1 -> Img 2 Clase 2
    //Posicion 2 -> Img 1 Clase 1
    //Posicion 3 -> Img 2 Clase 1

    float distancia;
    MyFile<<"---------------------------------------------------------------\n";
    MyFile<<"CALCULO DE DISTANCIAS EUCLIDEAS \n";
    MyFile<<"Imagenes: \n";

    distancia = calculateDistance(histogramas[0],histogramas[1]);
    MyFile<<"   -Img 1 (Clase 2) | Img 2 (Clase 2) = "+to_string(distancia)+"\n";
    distancia = calculateDistance(histogramas[0],histogramas[2]);
    MyFile<<"   -Img 1 (Clase 2) | Img 1 (Clase 1) = "+to_string(distancia)+"\n";
    distancia = calculateDistance(histogramas[0],histogramas[3]);
    MyFile<<"   -Img 1 (Clase 2) | Img 2 (Clase 1) = "+to_string(distancia)+"\n";

    MyFile<<"\n";
    distancia = calculateDistance(histogramas[1],histogramas[0]);
    MyFile<<"   -Img 2 (Clase 2) | Img 1 (Clase 2) = "+to_string(distancia)+"\n";
    distancia = calculateDistance(histogramas[1],histogramas[2]);
    MyFile<<"   -Img 2 (Clase 2) | Img 1 (Clase 1) = "+to_string(distancia)+"\n";
    distancia = calculateDistance(histogramas[1],histogramas[3]);
    MyFile<<"   -Img 2 (Clase 2) | Img 2 (Clase 1) = "+to_string(distancia)+"\n";

    MyFile<<"Con las distancias calculadas, como se puede visualizar, las menores distancias corresponden a imagenes de  \n";
    MyFile<<"la misma clase, mientras que cuando son clases diferentes el valor de la distancia es alto \n";
    MyFile<<"\n";
    MyFile<<"Con esto podemos decir que el descriptor LBP esta teniendo buenos resultados al comparar los histogramas de ambas clases \n";


    MyFile.close();

    waitKey();

    destroyAllWindows();

    //CLASIFICACION DE OTRO GRUPO DE IMAGENES CON COMPARACION DE HISTOGRAMAS
    vector<string> imagenesClasificar = lbp->listarDir("/home/computacion/Descargas/VisionPorComputador/BoletinPractica3/ImagenesClasificar");
    string clase;
    float distance, distance2, distance3, distance4;

    for(string imgs:imagenesClasificar){
        Mat imgNew = imread(imgs);
        cvtColor(imgNew, imgNew, COLOR_BGR2Lab);
        vector<int> histoImg = lbp->histogramaLBP(imgNew);
        vector<double> distanciasIMg;
        for (int i = 0 ; i<4;i++){
            distance = calculateDistance(histogramas[i],histoImg);
            distanciasIMg.push_back(distance);
        }
/*
        cout<<"Distancia con respecto a la Clase 1= "<<distanciasIMg[2]<<endl;
        cout<<"Distancia con respecto a la Clase 1= "<<distanciasIMg[3]<<endl;
        cout<<"Distancia con respecto a la Clase 2= "<<distanciasIMg[0]<<endl;
        cout<<"Distancia con respecto a la Clase 2= "<<distanciasIMg[1]<<endl;*/
        cout<<"IMAGEN ->"<<imgs<<endl;
        double min = minElement(distanciasIMg);
        if(min == distanciasIMg[2]){
            cout<<"Pertenece a la Clase 1"<<endl;
            cout<<"--------------------------------------------------"<<endl;
        }
        if(min == distanciasIMg[3]){
            cout<<"Pertenece a la Clase 1"<<endl;
            cout<<"--------------------------------------------------"<<endl;
        }
        if(min == distanciasIMg[0]){
            cout<<"Pertenece a la Clase 2"<<endl;
            cout<<"--------------------------------------------------"<<endl;
        }
        if(min == distanciasIMg[1]){
            cout<<"Pertenece a la Clase 2"<<endl;
            cout<<"--------------------------------------------------"<<endl;
        }
        

    }


    delete lbp;

    return 0;
}
