#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<ctime>
#include<fstream>
#include <cmath>

using namespace std;


#include "PGM.h"


int main(){




    PGM ballons;
    char ball[30] = "balloons_noisy.ascii.pgm";
    ballons.lectureFichier(ball);

    PGM copy2(ballons);
    copy2.filtrerImage(10);
    char cpy2[30] = "cop.pgm";
    copy2.ecrireFichier(cpy2);

    return 0;
}

//====================================================================================================================//

void PGM::initImage(){
    if(data== nullptr){
        data=new int*[hauteur];
        for(int i=0;i<hauteur;i++){
            data[i]=new int[largeur];
        }
    }
}
void PGM::supprImage(){
    if(data!= nullptr){
        for(int i=0;i<hauteur;i++){
            delete[] data[i];
        }
        delete[] data;
    }
}
void PGM::creeImage(int minpix, int maxpix){
    srand(time(NULL));
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            data[i][j]=rand()%maxpix+minpix;
        }
    }
}

PGM::PGM(){
    sethauteur(0);
    setlargeur(0);
    nbimg++;
}
PGM::PGM(int hauteur, int largeur, int minpix, int maxpix){
    sethauteur(hauteur);
    setlargeur(largeur);
    initImage();
    creeImage(minpix,maxpix);
    nbimg++;
}
PGM::PGM(const PGM &img){
    sethauteur(img.hauteur);
    setlargeur(img.largeur);
    initImage();
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            data[i][j]=img.data[i][j];
        }
    }
    nbimg++;
}
PGM::~PGM(){
    supprImage();
    nbimg--;
}

void PGM::afficherImage(){
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}

void PGM::ecrireFichier(char* nom_fichier){
    ofstream myfile;
    myfile.open (nom_fichier);
    myfile << "P2\n";
    myfile << largeur << " " << hauteur <<"\n"<<valeur_max<<"\n";
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            myfile<<data[i][j]<<" ";
        }
        myfile<<"\n";
    }
    myfile.close();
}

void PGM::setpixel(int y, int x, int val){
    if(y>=0 && x>=0 && y<hauteur && x<largeur){
        data[y][x]=val;
    }
}

void PGM::dessinRect(int x1, int y1, int x2, int y2, int val){
    int ii, jj, a, b;
    if(x1>x2){
        jj = x2;
        b = x1;
    }else{
        jj = x1;
        b = x2;
    }
    if(y1>y2){
        ii = y2;
        a = y1;
    }else{
        ii = y1;
        a = y2;
    }
    for (int i=ii; i < a+1; ++i){
        for(int j=jj; j < b+1; ++j){
            setpixel(i,j,val);
        }
    }
}

void PGM::dessinLigne(int x1, int x2, int line, int val){
    for (int i = 0; i < line; ++i) {
        setpixel(x2,x1,val);
        x1++;
    }
}

void PGM::dessinCroix(int x, int y, int val){
    setpixel(y-1,x-1,val);
    setpixel(y-1,x+1,val);
    setpixel(y,x,val);
    setpixel(y+1,x-1,val);
    setpixel(y+1,x+1,val);
}

void PGM::lectureFichier(char* nom_fichier) {
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
                s >> data[i][j];
            }
        }
    }
    monfichier.close();
}

void PGM::seuil(int seuil){
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            if(data[i][j]>seuil){
                data[i][j]=valeur_max;
            }else{
                data[i][j]=0;
            }
        }
    }
}

int PGM::moyenne(int x, int y, int size){
    int moy=0;
    int count=0;
    for (int i = y-size; i < y+size; ++i) {
        for (int j = x-size; j < x+size; ++j) {
            if(i>=0 && j>=0 && i<hauteur && j<largeur){
                moy=moy+data[i][j];
                count++;
            }
        }
    }
    if(moy==0){
        return data[y][x];
    }else{
        return moy/count;
    }
}
void PGM::flou(int size){
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            data[i][j]= moyenne(j,i,size);
        }
    }
}

void PGM::selection(int arr[], int n){
    for (int j = 0; j < n; ++j) {
        int min = j;
        for (int i = j+1; i < n; ++i) {
            if(arr[i]<arr[min]){
                min = i;
            }
        }
        int temp = arr[min];
        arr[min] = arr[j];
        arr[j] = temp;
    }
}
int PGM::median(int x, int y, int size){
    int tab[size*size];
    int a;
    for (int i = y-((int)(size/2)); i < y+((int)(size/2)); ++i) {
        a=0;
        for (int j = x-((int)(size/2)); j < x+((int)(size/2)); ++j) {
            if(i>=0 && j>=0 && i<hauteur && j<largeur){
                tab[a]=data[i][j];
                a++;
            }
        }
    }
    selection(tab,a);
    int med;
    if (a%2==0){
        med = tab[((int)(a/2+1))-1];
    }else{
        med = tab[((int)(a+1/2))-1];
    }
    return med;
}
void PGM::filtrerImage(int k){
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            data[i][j] = median(j,i,k);
        }
    }
}
