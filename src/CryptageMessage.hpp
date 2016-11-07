/*
 * CryptageMessage.hpp
 *
 *  Created on: 25 f�vr. 2015
 *      Author: j�r�my & c�cile
 */

#ifndef CRYPTAGEMESSAGE_HPP_
#define CRYPTAGEMESSAGE_HPP_
#include <string>

using namespace std;

class CryptageMessage {
public:

	CryptageMessage(const string,const string);
	virtual ~CryptageMessage();

	void cryptage(); 
	void decryptage(); 

	string getTexteInitial()const;
	string getTexteApresTraitement() const;
	string getClef()const;

private:
	void setClef(const string);
	void setTexteInitial( const std::string); 
	std::string clef;
	std::string texteInitial;
	std::string texteApresTraitementCry;
};

#endif /* CRYPTAGEMESSAGE_HPP_ */
