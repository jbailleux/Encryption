/*
 * IhmConsoleV2.cpp
 *
 *  Created on: 18 févr. 2015
 *      Author: jérémy
 */

#include "CryptageMessage.hpp"
#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include <sstream>
using namespace std;


string clef;
string texteInit="";
string textePostTrait="";
bool clefDeclaree=false;


void creationEtEcritureFichier(string const nom){
	ofstream fichier;
	fichier.open(nom.c_str(),ios::out);
	if(fichier){
		fichier<<textePostTrait;
		cout<<"Fichier bien enregistre sous le nom : "<<nom<<endl;
	}else
		cout<<"Problème lors de l'enregistrement du texte post traitement !"<<endl;
}

void ouvertureEtLectureFichier(string const nom){
	ifstream fichier;
    fichier.open(nom.c_str(), ios::in); // on ouvre le fichier en lecture
	if(fichier){  // si l'ouverture a réussi
    	cout<<"Votre fichier : "<<nom<< " a bien été ouvert."<<endl;
        stringstream txt;	// variable contenant l'intégralité du fichier
        txt << fichier.rdbuf();    // copier l'intégralité du fichier dans le buffer
        texteInit=txt.str();
    	fichier.close();  // on ferme le fichier
    }
    else
    	cout << "Impossible d'ouvrir le fichier !" << endl;
}

void listerFichierPresents(){
    DIR * rep = opendir(".");
    if (rep != NULL){
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL){
        	cout<<"- nom du fichier : "<< ent->d_name<<endl;}
        closedir(rep);
    }
}


void chargerFichier(){
	cout<<"Voici les fichiers presents dans votre repertoire."<<endl;
	listerFichierPresents();
	cout<<"Lequel souhaitez vous charger? (n'oubliez pas l'extension, s'il y en a une)"<<endl;
	string nom;
	cin>>nom;
	cin.ignore();
	ouvertureEtLectureFichier(nom);
}

void enregistrerFichier(){
	string nom;
	cout<<"Voici les fichiers presents dans votre repertoire."<<endl;
	listerFichierPresents();
	cout<<"Sous quel nom voulez vous enregistrer votre fichier? (Attention, si le nom est deja pris, l'ancien fichier sera ecrase!) "<<endl;
	cin>>nom;
	cin.ignore();
	creationEtEcritureFichier(nom);
}

void crypter(){
	CryptageMessage t(texteInit,clef);
	t.cryptage();
	textePostTrait=t.getTexteApresTraitement();
	cout<<"Cryptage reussi !"<<endl;
}



void decrypter(){
	CryptageMessage t(texteInit,clef);
	t.decryptage();
	textePostTrait=t.getTexteApresTraitement();
	cout<<"Decryptage reussi !"<<endl;
}

void demanderClef(){
	clefDeclaree=true;
	clef="a";
	cout<<"Entrez votre clef :"<<endl;
	cin>>clef;
	cin.ignore(1,'\n');
	while (clef.size()!=16){
		cout<<"La clef doit avoir une longueur de 16 caractères exactements!"<<endl;
		cout<<"Ré-entrer votre clef :"<<endl;
		cin>>clef;
		cin.ignore(1,'\n');
	}
}



 void menu(){
	int choix=0;
	while ((choix!=5)){// boucle parfois à l'infini
		cout<<endl;
		cout<<"Que voulez vous faire?"<<endl;
		cout<<" 1 : Choisir un fichier."<<endl;
		cout<<" 2 : Crypter votre message."<<endl;
		cout<<" 3 : Decrypter votre message."<<endl;
		cout<<" 4 : Changer votre clef."<<endl;
		cout<<" 5 : Quitter."<<endl;
		cin>>choix;
		switch (choix){
			case 1: {
				chargerFichier();
				break;}
			case 2: {
				if (clefDeclaree){
					crypter();
					enregistrerFichier();
				}else
					cout<<"Enregistrez d'abord votre clef !"<<endl;

				break;}
			case 3: {
				if (clefDeclaree){
					decrypter();
					enregistrerFichier();
				}else
					cout<<"Enregistrez d'abord votre clef !"<<endl;
				break;}
			case 4: {
				demanderClef();
				break;}
		}
	}
}


int main(){
	menu();
	cout<<"Merci d'avoir utilise ce programme."<<endl;
}
