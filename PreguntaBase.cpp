#include "PreguntaBase.h"

#include <iostream>

PreguntaBase::PreguntaBase(std::string enunciado, Taxonomia taxonomia, float duracion)
{
	this->setEnunciado(enunciado);
	this->setTaxonomia(taxonomia);
	this->setDuracion(duracion);
}

void PreguntaBase::setEnunciado(std::string enunciado)
{
	this->enunciado = enunciado;
}

std::string PreguntaBase::getEnunciado()
{
	return this->enunciado;
}

void PreguntaBase::setTaxonomia(Taxonomia taxonomia)
{
	this->taxonomia = taxonomia;
}

Taxonomia PreguntaBase::getTaxonomia()
{
	return this->taxonomia;
}

void PreguntaBase::setDuracion(float duracion)
{
	this->duracion = duracion;
}

float PreguntaBase::getDuracion()
{
	return this->duracion;
}

void PreguntaBase::mostrarInformacion()
{
	std::cout << "1. Enunciado: " << getEnunciado() << std::endl;

	std::cout << "2. La taxonomia de esta pregunta es: " << ReturnTaxName(getTaxonomia()) << std::endl;

	std::cout << "3. La duracion de la pregunta es de: " << getDuracion() << " segundos" << std::endl;

	
}

std::string PreguntaBase::ReturnTaxName(Taxonomia taxonomia)
{
	switch (taxonomia)
	{
	case RECORDAR:   return "Recordar";
	case ENTENDER: return "Entender";
	case APLICAR:   return "Aplicar";
	case ANALIZAR: return "Analizar";
	case EVALUAR: return "Evaluar";
	case CREAR: return "Crear";
	}
}
