#pragma once
#include <memory>
#include <vector>

#include "PreguntaBase.h"

#ifndef Dev_PreguntasPrueba
#define Dev_PreguntasPrueba 0
#endif

class Prueba
{
private:
	int Dev_PreguntasDefault;
	std::vector<std::unique_ptr<PreguntaBase>> lista_preguntas;
public:
	Prueba();

	// Menu
	std::vector<std::unique_ptr<PreguntaBase>>& getListaPreguntas();
	int menuPedirOpcion();
	void generarPregunta();
	void mostrarPreguntas();
	void actualizarPrueba();
	void borrarPregunta();
	void consultarItem();
	void consultarPorTaxonomia();
	int tiempoPrueba();
	void iniciarPrueba();
	void Dev_crearPreguntasManual();

	//Utils
	std::string getTaxNameByInt(int taxonomia);

};
