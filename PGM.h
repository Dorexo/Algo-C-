#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<ctime>
#include<fstream>
#include <cmath>

class PGM{
    private:
        int largeur;
        int hauteur;
        int valeur_max = 255;
        int** data = nullptr;

    public:
        static int nbimg;

        PGM();
        PGM(int hauteur, int largeur, int minpix, int maxpix);
        PGM(PGM const &img);
        ~PGM();

        void sethauteur(int hauteur){this->hauteur=hauteur;};
        void setlargeur(int largeur){this->largeur=largeur;};
        int gethauteur(){return hauteur;};
        int getlargeur(){return largeur;};
        int** getdata(){return data;};

        void initImage();
        void supprImage();
        void creeImage(int minpix=0, int maxpix=255);

        void afficherImage();

        void ecrireFichier(char* nom_fichier);
        void setpixel(int y, int x, int val);
        void dessinRect(int x1, int y1, int x2, int y2, int val);
        void dessinLigne(int x1, int x2, int line, int val);
        void dessinCroix(int x, int y, int val);

        void lectureFichier(char* nom_fichier);
        void seuil(int seuil);

        int moyenne(int x, int y, int size);
        void flou(int size);

        void selection(int tab[], int n);
        int median(int x, int y, int size);
        void filtrerImage(int k);
};
int PGM::nbimg = 0;
