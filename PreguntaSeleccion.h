#pragma once

#include <map>

#include "PreguntaBase.h"

class PreguntaSeleccion : public PreguntaBase
{
private:
	std::map<char, std::string> alternativas;
	char correcta;

public:
	void setAlternativas(std::map<char, std::string> alternativas);
	void cambiarAlternativa(char letra, std::string& texto);
	std::map<char, std::string> getAlternativas();

	void setCorrecta(char correcta);
	char getCorrecta();
	std::string getAlternativaDeLetra(char letra);
	void mostrarAlternativas();

	void mostrarInformacion() override;


	PreguntaSeleccion(std::string enunciado, Taxonomia taxonomia, float duracion, char correcta, std::map<char, std::string> alternaivas);
	
};
