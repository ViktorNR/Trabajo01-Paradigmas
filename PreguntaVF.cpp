#include "PreguntaVF.h"

#include <iostream>

void PreguntaVF::setJustificacion(std::string justificacion)
{
	this->justificacion = justificacion;
}

std::string PreguntaVF::getJustificacion()
{
	return this->justificacion;
}

void PreguntaVF::setVoF(char vof)
{
	this->vof = vof;
}

char PreguntaVF::getVoF()
{
	return this->vof;
}

void PreguntaVF::mostrarInformacion()
{
	PreguntaBase::mostrarInformacion();

	std::cout << "4. La respuesta es: " << static_cast<char>(std::toupper(getVoF())) << std::endl;

	if(!justificacion.empty())
	{
		std::cout << "5. Justificacion: " << getJustificacion() << std::endl;
		return;
	}

	std::cout << "El enunciado es verdadero, no existe justificacion." << std::endl;
}

PreguntaVF::PreguntaVF(std::string enunciado, Taxonomia taxonomia, float duracion, char vof, std::string justificacion) : PreguntaBase(enunciado, taxonomia, duracion)
{
	this->setEnunciado(enunciado);
	this->setTaxonomia(taxonomia);
	this->setDuracion(duracion);
	this->setVoF(vof);
	this->setJustificacion(justificacion);
}
