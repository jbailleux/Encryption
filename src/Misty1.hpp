/*
 * Misty1.hpp
 *
 *  Created on: 5 févr. 2015
 *      Author: Jérémy & Cécile
 */

#ifndef MISTY1_HPP_
#define MISTY1_HPP_

#include <stdint.h>
#include <string>

typedef char u8b;
typedef int16_t u16b;
typedef int32_t u32b;
typedef int64_t u64b;

class Misty1 {
public:
	Misty1(std::string, std::string, int);
	virtual ~Misty1();

	void setClef(std::string);
	std::string getClef() const;

	void setTexte(std::string);
	std::string getTexte() const;

	std::string getTexteApresTraitement() const;

	void setNombreTour(const int);
	int getNombreTour() const;

	void cryptage();
	void decryptage();

private:
	u8b K[16];
	u16b EK[32];
	int nombreTour; // compris entre 1 et 36 inclus
	std::string clef; // de longueur 16
	std::string texte; // de longueur 8
	std::string texteApresTraitement; // de longueur 8

	void setTexteApresTraitement(const std::string);

	std::string bitToString(const u64b);
	u64b stringToBit()const;

	void constructionK(const std::string);
	void constructionEK(const u8b K[16]);

	u8b* getK();


	u32b FO(const u32b FO_IN,const  int k); 
	u16b FI(const u16b FI_IN,const u16b FI_KEY );
	u32b FL(const u32b FL_IN, const int k); 
	u32b FLINV(const u32b FLINV_IN, const int k);
	u64b chiffrementBloc64(const u64b P);
	u64b dechiffrementBloc64(const u64b C); 
};


#endif /* MISTY1_HPP_ */
