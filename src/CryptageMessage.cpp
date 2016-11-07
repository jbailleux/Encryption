/*
 * CryptageMessage.hpp
 *
 *  Created on: 25 févr. 2015
 *      Author: jérémy & cécile
 */


#include <string>
#include <iostream>
#include "CryptageMessage.hpp"
#include "Misty1.hpp"

using namespace std;

CryptageMessage::CryptageMessage(const string texteInitial,const string clef){
		setClef(clef);
		setTexteInitial( texteInitial);
}

CryptageMessage::~CryptageMessage() {}

void CryptageMessage::setClef(std::string c){clef=c;}

void CryptageMessage::setTexteInitial( const std::string texte){texteInitial=texte;}

string CryptageMessage::getTexteInitial()const{return texteInitial;}

string CryptageMessage::getClef()const {return clef;}


void CryptageMessage::cryptage(){

//n est la longueur de la chaine de caractere initiale

	string texte=getTexteInitial();

	int n=texte.length();
	int m;
// sousP (pour sous parties) est le nombre de case dans lesquelles seront stocke 8 par 8 les elements du texte initial
	int sousP;
	sousP=(n/8);
// au nombre d'element ne formant pas un groupe de 8 caracteres
	int restD;
	restD=n%8;
//string dans lequel sera stocke le texte decoupe
	string Inter;
	int i=0;
	if (restD ==0){
		while (i<sousP){
			for (m=0;m<8;m++){
				Inter.push_back(texte[m+i*8]);
			}
			Misty1 msg(Inter,clef,1);
			msg.setTexte(Inter);
			msg.cryptage();
			texteApresTraitementCry += msg.getTexteApresTraitement();
			i++;
		}
	}
	else{
		while (i<sousP){
			for (m=0;m<8;m++){
				Inter.push_back(texte[m+i*8]);
			}

		Misty1 msg(Inter,clef,1);
		msg.setTexte(Inter);
		msg.cryptage();
		texteApresTraitementCry += msg.getTexteApresTraitement();
		Inter.clear();
		i++;
	}
//Remplissage par le reste des elements dans le tableau de sortie
		for (m=0;m<restD;m++){
			Inter.push_back(texte[m+i*8]);
		}
//BOURRAGE du reste du tableau par le caractere '*'
		for(m=restD;m<8;m++){
			Inter.push_back('*');
		}
		Misty1 msg(Inter,clef,1);
		msg.setTexte(Inter);
		msg.cryptage();
		texteApresTraitementCry += msg.getTexteApresTraitement();
		Inter.clear();
		}

}


string CryptageMessage::getTexteApresTraitement() const {return texteApresTraitementCry;}


void CryptageMessage::decryptage(){
	string texte=getTexteInitial();
	int n=texte.length();
	int m;
	int sousP;
	sousP=(n/8);
	int restD;
	restD=n%8;
	string Inter;
	int i=0;
	if (restD ==0){
		while (i<sousP){
			for (m=0;m<8;m++){
				Inter.push_back(texte[m+i*8]);
			}
			Misty1 msg(Inter,clef,1);
			msg.setTexte(Inter);
			msg.decryptage();
			texteApresTraitementCry += msg.getTexteApresTraitement();
			Inter.clear();
			i++;
		}
	}
	else{
		while (i<sousP){
			for (m=0;m<8;m++){
				Inter.push_back(texte[m+i*8]);
			}
		Misty1 msg(Inter,clef,1);
		msg.setTexte(Inter);
		msg.decryptage();
		texteApresTraitementCry+= msg.getTexteApresTraitement();
		Inter.clear();
		i++;
	}
		for (m=0;m<restD;m++){
			Inter.push_back(texte[m+i*8]);
		}
		for(m=restD;m<8;m++){
			Inter.push_back('*');
		}
		Misty1 msg(Inter,clef,1);
		msg.setTexte(Inter);
		msg.decryptage();
		texteApresTraitementCry += msg.getTexteApresTraitement();
		}
}

