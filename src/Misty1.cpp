/*
 * Misty1.cpp
 *
 *  Created on: 5 févr. 2015
 *      Author: Jérémy et Cécile
 */
#include "Misty1.hpp"
#include "TableS7S9.cpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdint.h>

typedef char u8b;
typedef int16_t u16b;
typedef int32_t u32b;
typedef int64_t u64b;

// Constructeur et destructeur

Misty1::Misty1(std::string texte, std::string clef, int n) {
	if ((texte.size()==8) && (clef.size()==16) && (n>=1)&& (n<=36)){
		setClef(clef);
		setTexte(texte);
		setNombreTour(n);
	}else
		{std::cout<<"Clef, texte ou nombre de tour pas de la bonne taille lors de la création d'une instance Misty1. "<<std::endl;
			std::cout<<(texte.size()==8)<<" "<<(clef.size()==16)<<" "<<((n>=1)&& (n<=36))<<std::endl;

		}
}

Misty1::~Misty1() {}

// FIN Constructeur et destructeur

// Getter et Setter

void Misty1::setNombreTour(int n){
	if ((n>=1)&&(n<=36)){
		nombreTour=n;
	}else {
		std::exit(0);}
}
int Misty1::getNombreTour()const {return nombreTour;}

void Misty1::setTexteApresTraitement(const std::string t){texteApresTraitement=t;}
std::string Misty1::getTexteApresTraitement()const {return texteApresTraitement;}

void Misty1::setTexte( std::string t){
	if (t.size()==8){
		texte=t;
	}else{
		std::cout<<" Erreur setTexte: texte.size!=8 "<<std::endl;
		std::exit(0);}
}
std::string Misty1::getTexte() const{return texte;}


void Misty1::setClef(std::string c){
	if ( (c.size()==16)){
		clef=c;
		constructionK(clef);
		constructionEK(getK());
	}else{
		std::cout<<" Erreur setClef : clef.size!=16"<<std::endl;
		std::exit(0);
	}
}
std::string Misty1::getClef() const{return clef;}

u8b* Misty1::getK(){return K;}

// FIN Getter et Setter


// Fonction de traitement non propre à la méthode Misty1

std::string Misty1::bitToString(const u64b T){
	std::string t="";
	for(int i=0;i<=7;i++){t+=(unsigned char) (T>>(8*(7-i)) ) ;}
	return t;
}

u64b Misty1::stringToBit()const{
	if(texte.size()==8){
		u64b p=0x00000000;
		std::cout<<std::endl;
		for(int i=0;i<=7;i++){
			u64b tmp=(texte[i]&0x0000000ff);// Très important le &0x0000000ff, sans lui on ne sait pas ce que prennent les 56 premiers bits!
			tmp=tmp<<((7-i)*8);
			p=p|tmp;
		}
		return p;
	}else{
		std::cout<<" Impossible de générer le bloc de 64b correspondant au texteClaire : texteClaire.size!=8 "<<std::endl;
		std::exit(0);
		return 0;}
}

void Misty1::cryptage(){setTexteApresTraitement(bitToString(chiffrementBloc64(stringToBit())));}

void Misty1::decryptage(){setTexteApresTraitement(bitToString(dechiffrementBloc64(stringToBit())));}

void Misty1::constructionK(std::string clef){
	for(int i=0;i<=15;i++){K[i]=clef[i];}
}

// FIN Fonction de traitement non propre à la méthode Misty1


// Fonction Propre à Misty1

void Misty1::constructionEK(const u8b K[16]){
	for(int i=0;i<8;i++)
		EK[i] =(K[i*2]*256) + K[i*2+1];
	for(int i=0; i<8; i++){
		EK[i+8] = FI(EK[i],EK[(i+1)%8]);
		EK[i+16] = (EK[i+8] & 0x1ff);
		EK[i+24] = EK[i+8] >> 9;
	}
}

u16b Misty1::FI(const u16b FI_IN,const u16b FI_KEY ){
	u16b d9= (FI_IN >> 7)& 0x1ff;
	u16b d7= FI_IN & 0x7F;
	d9=S9[d9]^d7;
	d7=(((u16b)S7[d7]) ^ d9)&0x7f;
	d7=d7^((FI_KEY>>9)&0x7f);
	d9=d9^(FI_KEY & 0x1ff);
	d9=S9[d9]^d7;
	u16b FI_OUT=0x00;
	FI_OUT=FI_OUT|d7;
	FI_OUT=FI_OUT<<9;
	FI_OUT=FI_OUT|(d9);
	return FI_OUT;
}

u32b Misty1::FO(const u32b FO_IN,const  int k){
	u16b t0=(FO_IN >> 16);
	u16b t1=(FO_IN & 0xffff);
	t0=t0^EK[k];
	t0=FI(t0,EK[(k+5)%8+8]);
	t0=t0^t1;
	t1=t1^EK[(k+2)%8];
	t1=FI(t1,EK[(k+1)%8+8]);
	t1=t1^t0;
	t0=t0^EK[(k+7)%8];
	t0=FI(t0,EK[(k+3)%8+8]);
	t0=t0^t1;
	t1=t1^EK[(k+4)%8];
	u32b FO_OUT=0x0000;
	FO_OUT=t1&0x00ffff;
	FO_OUT=FO_OUT<<16;
	FO_OUT=FO_OUT|(t0&0x00ffff);
	return FO_OUT;
}

u32b Misty1::FL(const u32b FL_IN, const int k){
	u16b d0=(FL_IN>>16);
	u16b d1=(FL_IN & 0xFFFF);
	if ((k%2)==0){
		d1=d1^(d0&(EK[k/2]));
		d0=d0^(d1|(EK[(k/2+6)%8+8]));
	}else{
		d1=d1^(d0&(EK[((k-1)/2+2)%8+8]));
		d0=d0^(d1|(EK[((k-1)/2+4)%8]));
	}
	u32b FL_OUT=d0&0x00ffff;
	FL_OUT=FL_OUT<<16;
	FL_OUT=FL_OUT| (d1&0x00ffff);
	return FL_OUT;
}

u32b Misty1::FLINV(const u32b FLINV_IN, const int k){
	u16b d0=((FLINV_IN>>16)&0x00ffff);
	u16b d1=(FLINV_IN&0xffff);
	if ((k%2)==0){
		d0=d0^(d1|(EK[(k/2+6)%8+8]));
		d1=d1^(d0&(EK[k/2]));
	}else{
		d0=d0^(d1|(EK[((k-1)/2+4)%8]));
		d1=d1^(d0&(EK[((k-1)/2+2)%8+8]));
	}
	u32b FLINV_OUT=0x00ffff&d0;
	FLINV_OUT=FLINV_OUT<<16;
	FLINV_OUT=FLINV_OUT|(d1&0x00ffff);
	return FLINV_OUT;
}

u64b Misty1::chiffrementBloc64(const u64b P){
	u32b d0=(P>>32);
	u32b d1=(P&0x0000ffffffff);

	for(int i=0;i<getNombreTour();i++){
		if ((i%2)==0){
			d0=FL(d0,i);
			d1=FL(d1,i+1);
			d1=d1^FO(d0,i);
		}else{
			d0=d0^FO(d1,i);
		}
	}

	d0=FL(d0,getNombreTour());
	d1=FL(d1,getNombreTour()+1);

	u64b C=0x0000ffffffff;
	C=C&(d1&0x0000ffffffff);
	C=C<<32;
	C=C|(d0&0x0000ffffffff);
	return C;
}

u64b Misty1::dechiffrementBloc64(const u64b C){
	u32b d1=(u32b) ((C>>32)&0x0000ffffffff);
	u32b d0=(u32b) (C&0x0000ffffffff);

	d0=FLINV(d0,getNombreTour());
	d1=FLINV(d1,getNombreTour()+1);

	for(int i=getNombreTour()-1;i>=0;i--){
		if ((i%2)==0){
			d1=d1^FO(d0,i);
			d0=FLINV(d0,i);
			d1=FLINV(d1,i+1);
		}else{
			d0=d0^FO(d1,i);
		}
	}

	u64b P=0x0000ffffffff;
	P=P&(d0&0x0000ffffffff);
	P=P<<32;
	P=P|(d1&0x0000ffffffff);
	return P;
}
// FIN Fonction Propre à Misty1













