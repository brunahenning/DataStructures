#include<iostream>
#include "Pilha.h"
#include <string>
#include <algorithm>

using namespace std;

bool palindromo(string palavra){

	palavra.erase(remove(palavra.begin(), palavra.end(), ' '), palavra.end());	///Trim spaces
	palavra.erase(remove(palavra.begin(), palavra.end(), ','), palavra.end());	///No epecial characters
	palavra.erase(remove(palavra.begin(), palavra.end(), '\''), palavra.end());	///No epecial characters
	palavra.erase(remove(palavra.begin(), palavra.end(), '\"'), palavra.end());	///No epecial characters
	transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);		///All the same chars

	pil::Pilha<char> pilha1;
	len::init(pilha1.pilha);

	unsigned int palavra_size = palavra.length();
	unsigned int odd_axis = 0;

	if((palavra_size % 2) != 0 ){
		odd_axis = palavra_size/2;
		cout << "Eixo em " << palavra[odd_axis] << endl;
	}

	if(odd_axis == 0){
		for(unsigned int I = 0 ; I < palavra_size/2 ; I++){
			pil::push(pilha1 , palavra[I]);
		}
		for(unsigned int I = palavra_size/2 ; I < palavra_size ; I++){
			if(palavra[I] != pil::pop(pilha1)) return 0;
		}
		return 1;
	}else{
		for(unsigned int I = 0 ; I < palavra_size/2 ; I++){
			pil::push(pilha1 , palavra[I]);
		}
		for(unsigned int I = palavra_size/2 + 1 ; I < palavra_size ; I++){
			if(palavra[I] != pil::pop(pilha1)) return 0;
		}
		return 1;
	}
	

}


int main(){

	//pil::Pilha<int> pilha1;

	//pil::push(pilha1,123);
	//pil::push(pilha1,321);
	//pil::push(pilha1,345);

	//cout << "peek: " << pil::peek(pilha1) << endl;

	//cout << "pop: " <<  pil::pop(pilha1) << endl;
	//cout << "pop: " <<  pil::pop(pilha1) << endl;
	//cout << "pop: " <<  pil::pop(pilha1) << endl;
	

	cout << palindromo("Red rum, sir, is murder") << endl;

	

	return 0;

}
