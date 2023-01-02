#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<ctime>
#include<fstream>
#include <cmath>

class PPM{
    private:
        int largeur;
        int hauteur;
        int valeur_max = 255;
        int*** data = nullptr;

    public:
        static int nbimg;

        PPM();
        PPM(int hauteur, int largeur, int minpix, int maxpix);
        PPM(PPM const &img);
        ~PPM();

        void sethauteur(int hauteur){this->hauteur=hauteur;};
        void setlargeur(int largeur){this->largeur=largeur;};
        int gethauteur(){return hauteur;};
        int getlargeur(){return largeur;};
        int*** getdata(){return data;};

        void initImage();
        void supprImage();
        void creeImage(int minpix=0, int maxpix=255);

        void afficherImage();

        void ecrireFichier(char* nom_fichier);
        void setpixel(int y, int x, int r, int g, int b);
        void dessinRect(int x1, int y1, int x2, int y2, int r, int g, int b);
        void dessinLigne(int x1, int x2, int line, int r, int g, int b);
        void dessinCroix(int x, int y, int r, int g, int b);

        void lectureFichier(char* nom_fichier);
        void seuil(int r, int g, int b);

        int moyenne(int x, int y, int size, int rgb);
        void flou(int size);
};
int PPM::nbimg = 0;
