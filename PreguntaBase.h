#pragma once
#include <string>
#include "BloomEnum.h"


class PreguntaBase
{
private:
	std::string enunciado;
	Taxonomia taxonomia;
	float duracion;

public:
	void setEnunciado(std::string enunciado);
	std::string getEnunciado();

	void setTaxonomia(Taxonomia taxonomia);
	Taxonomia getTaxonomia();

	void setDuracion(float duracion);
	float getDuracion();

	virtual void mostrarInformacion() = 0;



	std::string ReturnTaxName(Taxonomia taxonomia);


protected:
	PreguntaBase(std::string enunciado, enum Taxonomia taxonomia, float duracion);
};
