#include "PreguntaSeleccion.h"

#include <iostream>

void PreguntaSeleccion::setAlternativas(std::map<char, std::string> alternativas)
{
	this->alternativas = alternativas;
}

void PreguntaSeleccion::cambiarAlternativa(char letra, std::string& texto)
{
	this->alternativas[letra] = texto;
}

std::map<char, std::string> PreguntaSeleccion::getAlternativas()
{
	return this->alternativas;
}

void PreguntaSeleccion::setCorrecta(char correcta)
{
	this->correcta = correcta;
}

char PreguntaSeleccion::getCorrecta()
{
	return this->correcta;
}

std::string PreguntaSeleccion::getAlternativaDeLetra(char letra)
{
	return getAlternativas().find(letra)->second;
}

void PreguntaSeleccion::mostrarAlternativas()
{
	std::cout << "4. Las alternativas son:" << std::endl;
	for (auto alternativa : getAlternativas())
	{
		std::cout << alternativa.first << ") " << "\"" << alternativa.second << "\" \n";
	}
}

void PreguntaSeleccion::mostrarInformacion()
{
	PreguntaBase::mostrarInformacion();

	this->mostrarAlternativas();

	std::cout << "5. La alternativa correcta es: " << getCorrecta() << ")" << " " << (getAlternativaDeLetra(getCorrecta())) << std::endl;

}

PreguntaSeleccion::PreguntaSeleccion(std::string enunciado, Taxonomia taxonomia, float duracion, char correcta, std::map<char, std::string> alternaivas) : PreguntaBase(enunciado, taxonomia, duracion)
{
	this->setEnunciado(enunciado);
	this->setTaxonomia(taxonomia);
	this->setDuracion(duracion);
	this->setCorrecta(correcta);
	this->setAlternativas(alternaivas);
}
