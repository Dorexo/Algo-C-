#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<ctime>
#include<fstream>
#include <cmath>

using namespace std;


#include "PPM.h"



//====================================================================================================================//

void PPM::initImage(){
    if(data == nullptr){
        data=new int**[hauteur];
        for(int i=0;i<hauteur;i++){
            data[i]=new int*[largeur];
            for (int j = 0; j < largeur; ++j) {
                data[i][j]=new int[3];
            }
        }
    }
}
void PPM::supprImage(){
    if(data != nullptr){
        for(int i=0;i<hauteur;i++){
            for (int j = 0; j < largeur; ++j) {
                delete[] data[i][j];
            }
            delete[] data[i];
        }
        delete[] data;
    }
    data=nullptr;
}
void PPM::creeImage(int minpix, int maxpix){
    srand(time(NULL));
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            data[i][j][0]=rand()%maxpix+minpix;
            data[i][j][1]=rand()%maxpix+minpix;
            data[i][j][2]=rand()%maxpix+minpix;
        }
    }
}

PPM::PPM(){
    sethauteur(0);
    setlargeur(0);
    nbimg++;
}
PPM::PPM(int hauteur, int largeur, int minpix, int maxpix){
    sethauteur(hauteur);
    setlargeur(largeur);
    initImage();
    creeImage(minpix,maxpix);
    nbimg++;
}
PPM::PPM(const PPM &img){
    sethauteur(img.hauteur);
    setlargeur(img.largeur);
    initImage();
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            data[i][j][0]=img.data[i][j][0];
            data[i][j][1]=img.data[i][j][1];
            data[i][j][2]=img.data[i][j][2];
        }
    }
    nbimg++;
}
PPM::~PPM(){
    supprImage();
    nbimg--;
}

void PPM::afficherImage(){
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            cout<<data[i][j][0]<<" "<<data[i][j][1]<<" "<<data[i][j][2]<<endl;
        }
        cout<<endl;
    }
}

void PPM::ecrireFichier(char* nom_fichier){
    ofstream myfile;
    myfile.open (nom_fichier);
    myfile << "P3\n";
    myfile << largeur << " " << hauteur <<"\n"<<valeur_max<<"\n";
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            myfile<<data[i][j][0]<<" "<<data[i][j][1]<<" "<<data[i][j][2]<<" ";
        }
        myfile<<"\n";
    }
    myfile.close();
}

void PPM::setpixel(int y, int x, int r, int g, int b){
    if(y>=0 && x>=0 && y<hauteur && x<largeur){
        data[y][x][0]=r;
        data[y][x][1]=g;
        data[y][x][2]=b;
    }
}

void PPM::dessinRect(int x1, int y1, int x2, int y2, int r, int g, int b){
    int ii, jj, a, c;
    if(x1>x2){
        jj = x2;
        c = x1;
    }else{
        jj = x1;
        c = x2;
    }
    if(y1>y2){
        ii = y2;
        a = y1;
    }else{
        ii = y1;
        a = y2;
    }
    for (int i=ii; i < a+1; ++i){
        for(int j=jj; j < c+1; ++j){
            setpixel(i,j,r,g,b);
        }
    }
}

void PPM::dessinLigne(int x1, int x2, int line, int r, int g, int b){
    for (int i = 0; i < line; ++i) {
        setpixel(x2,x1,r,g,b);
        x1++;
    }
}

void PPM::dessinCroix(int x, int y, int r, int g, int b){
    setpixel(y-1,x-1,r,g,b);
    setpixel(y-1,x+1,r,g,b);
    setpixel(y,x,r,g,b);
    setpixel(y+1,x-1,r,g,b);
    setpixel(y+1,x+1,r,g,b);
}

void PPM::lectureFichier(char* nom_fichier) {
    ifstream monfichier;
    string ligne;
    stringstream s;
    monfichier.open(nom_fichier);
    if (monfichier.is_open()){
        getline(monfichier,ligne);
        s << monfichier.rdbuf();
        s >> largeur >> hauteur >> valeur_max;
        supprImage();
        initImage();
        for (int i = 0; i < hauteur; ++i) {
            for (int j = 0; j < largeur; ++j) {
                s >> data[i][j][0] >> data[i][j][1] >> data[i][j][2];
            }
        }
    }
    monfichier.close();
}

void PPM::seuil(int r, int g, int b){
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            if(data[i][j][0]>r && data[i][j][1]>g && data[i][j][2]>b){
                data[i][j][0]=valeur_max;
                data[i][j][1]=valeur_max;
                data[i][j][2]=valeur_max;
            }else{
                data[i][j][0]=0;
                data[i][j][1]=0;
                data[i][j][2]=0;
            }
        }
    }
}

int PPM::moyenne(int x, int y, int size, int rgb){
    int moy=0;
    int count=0;
    for (int i = y-size; i < y+size; ++i) {
        for (int j = x-size; j < x+size; ++j) {
            if(i>=0 && j>=0 && i<hauteur && j<largeur){
                moy=moy+data[i][j][rgb];
                count++;
            }
        }
    }
    if(moy==0){
        return data[y][x][rgb];
    }else{
        return moy/count;
    }
}
void PPM::flou(int size){
    PPM image(*this);
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            int moy0 = image.moyenne(j,i,size,0);
            int moy1 = image.moyenne(j,i,size,1);
            int moy2 = image.moyenne(j,i,size,2);
            data[i][j][0]= moy0;
            data[i][j][1]= moy1;
            data[i][j][2]= moy2;
        }
    }
}