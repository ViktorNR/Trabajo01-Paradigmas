#pragma once
#include <map>

#include "PreguntaBase.h"

class PreguntaVF : public PreguntaBase
{
private:
	std::string justificacion;
	char vof;
public:
	void setJustificacion(std::string justificacion);
	std::string getJustificacion();

	void setVoF(char vof);
	char getVoF();

	void mostrarInformacion() override;


	PreguntaVF(std::string enunciado, enum Taxonomia taxonomia, float duracion, char vof, std::string justificacion);
};