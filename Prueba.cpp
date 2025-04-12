#include "Prueba.h"

#include <iostream>

#include "PreguntaSeleccion.h"
#include "PreguntaVF.h"

#define separador "<-------------------------------------------------->"

Prueba::Prueba()
{
	iniciarPrueba();
}

std::vector<std::unique_ptr<PreguntaBase>>& Prueba::getListaPreguntas()
{
	return this->lista_preguntas;
}

int Prueba::menuPedirOpcion()
{
    std::cout << separador << std::endl;
    // Declaración de variables.
    int opcion = 0;
    int minimo = 1;
    int maximo = 8;
    bool valido = false;

    // Asegurar que se repitan las opciones hasta que se escoja una válida.
    while (!valido || opcion < minimo || opcion > maximo) {

        std::cout << "\nMenu de opciones:\n";
        std::cout << ("1. Crear item.\n");
        std::cout << ("2. Mostrar preguntas.\n");
        std::cout << ("3. Actualizar item.\n");
        std::cout << ("4. Borrar item.\n");
        std::cout << ("5. Consultar item.\n");
        std::cout << ("6. Buscar segun taxonomia de Bloom.\n");
        std::cout << ("7. Calcular tiempo total de prueba. \n");
        std::cout << ("8. Salir.\n\n");

        std::cout << "Ingrese opcion (entero entre 1 y 6): ";

        std::cin >> opcion;

        // Limpiar entrada estándar para que no quede el salto de línea
        // residual.
        //while (getchar() != '\n');

        // Si la opción no es válida, informar al ususario.
        if (opcion < minimo || opcion > maximo) {
            std::cout << "La opcion ingresada no es valida. \n";
        }
        else valido = true;
    }

    return opcion;
}

//1
void Prueba::generarPregunta()
{
    int tipo_pregunta;


    // Variables preguntas general.
    std::string enunciado;
    Taxonomia taxonomia;
    int taxonomia_int;
    float duracion;

    // Seleccion Multiple
    std::map<char, std::string> alternativas;
    std::string alternativa;
    char letras[] = { 'a', 'b', 'c', 'd', 'e' };
    char correcta;

    // VoF
    std::string justificacion;
    char vof;



    std::cout << "Escriba el tipo de pregunta.\n 1. Pregunta Seleccion Multiple. \n 2. Pregunta Verdaro o Falso. \n" << std::endl;
    std::cout << "Ingrese aqui su opcion: ";
    std::cin >> tipo_pregunta;

    while (tipo_pregunta != 1 && tipo_pregunta != 2)
    {
        std::cout << "Opcion invalida. Intente de nuevo: ";
        std::cin >> tipo_pregunta;
    }


    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
    std::cout << "Escriba el enunciado de la pregunta: ";
    std::getline(std::cin, enunciado);


    // Seleccion multiple
    if (tipo_pregunta == 1)
    {
        // Una alternativa por letra (a - e)
        for (const char letra : letras)
        {
            std::cout << "Escriba la pregunta para la alternativa '" << letra << "': ";
            std::getline(std::cin, alternativa);
            alternativas.insert({ letra, alternativa });
        }
        // Hacer que escoja la alternativa correcta.


        // Mostrar las alternativas para que se elija la correcta.
        for (auto alternativa : alternativas)
        {
            std::cout << alternativa.first << ") " << "\"" << alternativa.second << "\" \n";
        }
        std::cout << "Escriba la alternativa correcta: ";
        std::cin >> correcta;

		// Validar la letra ingresada.
        while (alternativas.find(correcta) == alternativas.end())
        {
            std::cout << "Letra invalida. Intente de nuevo: ";
            std::cin >> correcta;
        }
    }
    // Verdadero o Falso.
    else
    {
        // Que pasa si ingresa un valor que no sea ni V o F??? Hay que arreglarlo!
        std::cout << "Ingrese si el enunciado es verdero (V) o falso (F): ";
        std::cin >> vof;

        vof = std::toupper(vof);
        while (vof != 'V' && vof != 'F')
        {
            std::cout << "Entrada invalida. Ingrese V o F: ";
            std::cin >> vof;
            vof = std::toupper(vof);
        }


        if (vof == 'F')
        {
            std::cout << "Ingrese justificacion: ";
            std::cin.ignore();
            std::getline(std::cin, justificacion);
        }
    }

    std::cout << "1. RECORDAR" << "\n";
    std::cout << "2. ENTENDER" << "\n";
    std::cout << "3. APLICAR" << "\n";
    std::cout << "4. ANALIZAR" << "\n";
    std::cout << "5. EVALUAR" << "\n";
    std::cout << "6. CREAR" << "\n";
    std::cout << "Elija la Taxonomia (1 - 6): ";
    std::cin >> taxonomia_int;

    while (taxonomia_int < 1 || taxonomia_int > 6)
    {
        std::cout << "Valor invalido. Intente nuevamente (1-6): ";
        std::cin >> taxonomia_int;
    }


    std::cout << "Elija la duracion (en segundos): ";
    std::cin >> duracion;

    while (duracion <= 0)
    {
        std::cout << "Duracion invalida. Intente nuevamente: ";
        std::cin >> duracion;
    }


    if (tipo_pregunta == 1)
    {
        this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(enunciado, static_cast<Taxonomia>(taxonomia_int), duracion, correcta, alternativas));
        return;
    }

    this->lista_preguntas.push_back(std::make_unique<PreguntaVF>(enunciado, static_cast<Taxonomia>(taxonomia_int), duracion, vof, justificacion));
}

//2
void Prueba::mostrarPreguntas()
{
    std::cout << "Mostrando preguntas: \n";

    for (int i = 0; i < this->lista_preguntas.size(); i++)
    {
        std::cout << i + 1 << ". " << this->lista_preguntas[i]->getEnunciado() << std::endl;
    }

    std::cout << "\n";
}

//3
void Prueba::actualizarPrueba()
{
    int numero;
    int actualizar;
    int valido = this->lista_preguntas.size();

    while (true)
    {
        mostrarPreguntas();
        std::cout << "Ingrese el numero de la pregunta cuyos datos desea actualizar: ";
        //std::cin.ignore();
        std::cin >> numero;
        int indice_pregunta = numero - 1;

        if (numero == 0)
        {
            return;
        }

        // Abajo de == 0,sino da nullptr
        PreguntaSeleccion* pregunta_seleccion = dynamic_cast<PreguntaSeleccion*>(this->lista_preguntas[indice_pregunta].get());
        PreguntaVF* pregunta_vf = dynamic_cast<PreguntaVF*>(this->lista_preguntas[indice_pregunta].get());


        if (numero > valido)
        {
            std::cout << separador << std::endl;
            std::cout << "Numero de pregunta fuera de rango, intente de nuevo" << std::endl;
            continue;
        }

        this->lista_preguntas[indice_pregunta]->mostrarInformacion();
        std::cout << "Ingrese un numero segun el dato que desea actualizar: ";
        std::cin.ignore();
        std::cin >> actualizar;

        if (actualizar == 5 && std::tolower(pregunta_vf->getVoF()) == 'v')
        {
            std::cout << "Los enunciados Verdaderos no tienen justificacion, intente de nuevo..." << std::endl;
            continue;
        }





        switch (actualizar)
        {
        case 1:
            // Brackets por maldito compilador...
	        {
	            std::string enunciado;
	            std::cout << "Ingrese el nuevo enunciado: " << std::endl;
	            std::cin.ignore();
	            std::getline(std::cin, enunciado);

	            if (enunciado.empty())
	            {
	                std::cout << "No ingreso ningun enunciado, no se actualizara..." << std::endl;
	                break;
	            }

	            this->lista_preguntas[indice_pregunta]->setEnunciado(enunciado);
                break;
	        }
      

        case 2:
            std::cout << "1. RECORDAR" << "\n";
            std::cout << "2. ENTENDER" << "\n";
            std::cout << "3. APLICAR" << "\n";
            std::cout << "4. ANALIZAR" << "\n";
            std::cout << "5. EVALUAR" << "\n";
            std::cout << "6. CREAR" << "\n";
            std::cout << "Elija la nueva Taxonomia (1 - 6): ";

            int taxonomia_int;
            std::cin >> taxonomia_int;

            if(taxonomia_int >= 7 || taxonomia_int <= 0)
            {
                std::cout << "Taxonomia fuera de rango!" << std::endl;
                break;
            }

            this->lista_preguntas[indice_pregunta]->setTaxonomia(static_cast<Taxonomia>(taxonomia_int));

            if(this->lista_preguntas[indice_pregunta]->getTaxonomia() == static_cast<Taxonomia>(taxonomia_int))
            {
                std::cout << "La taxonomia elegida ya correspondia a la pregunta." << std::endl;
                break;
            }

            std::cout << "Taxonomia cambiada con exito!" << std::endl;
            break;

        case 3:
            float duracion;
            std::cout << "Ingrese la nueva duracion de la pregunta (en segundos): ";
            std::cin >> duracion;

            if (duracion == 0)
            {
                std::cout << "La pregunta no puede resolverse en 0 segundos, introduzca como minimo un 1." << std::endl;
                break;
            }

            this->lista_preguntas[indice_pregunta]->setDuracion(duracion);
            std::cout << "Duracion cambiada con exito!" << std::endl;
            break;

        case 4:
        {
            if (pregunta_seleccion)
            {
                int opcion;
                pregunta_seleccion->mostrarAlternativas();
                std::cout << "Ingrese 1 si desea cambiar TODAS las alternativas, 2 si solo desea cambiar una: ";
                std::cin.ignore();
                std::cin >> opcion;
                char single_alternativa;
                std::string alternativa;
                char letras[] = { 'a', 'b', 'c', 'd', 'e' };
                if (opcion == 1)
                {


                    std::cin.ignore();
                    for (const char letra : letras)
                    {
                        std::cout << "Escriba la pregunta para la alternativa '" << letra << "': ";
                        std::getline(std::cin, alternativa);
                        pregunta_seleccion->cambiarAlternativa(letra, alternativa);
                    }
                    std::cout << "Alternativas cambiadas correctamente!" << std::endl;
                    std::cout << "Recuerde que la alternativa correcta sigue siendo: " << pregunta_seleccion->getCorrecta() << "!" << std::endl;
                    break;
                }
                if (opcion == 2)
                {
                    bool valido = false;
                    std::cin.ignore();
                    std::cout << "Elija la alternativa a cambiar (a, b, c, d, e): ";
                    std::cin >> single_alternativa;
                    std::cin.ignore();
                    for (auto letra : letras)
                    {
                        if (letra == single_alternativa)
                        {
                            valido = true;
                            std::cout << "Escriba la alternativa: ";
                            std::getline(std::cin, alternativa);
                            pregunta_seleccion->cambiarAlternativa(letra, alternativa);
                            std::cout << "Alternativa cambiada con exito!" << std::endl;
                            break;
                        }
                    }
                    if (valido)
                    {
                        break;
                    }




                }
                std::cout << "Ingreso no valido, intentelo de nuevo..." << std::endl;
                break;

            }

            if (pregunta_vf)
            {
                std::string justificacion;
                if (std::tolower(pregunta_vf->getVoF()) == 'v')
                {
                    std::cout << "El enunciado era Verdadero, cambiando a Verdadero... ingrese justificacion:" << std::endl;
                    std::cin.ignore();
                    std::getline(std::cin, justificacion);

                    pregunta_vf->setVoF('F');
                    pregunta_vf->setJustificacion(justificacion);
                    break;
                }

                std::cout << "El enunciado era Falso, cambiando a Verdadero..." << std::endl;
                pregunta_vf->setVoF('V');
                pregunta_vf->setJustificacion("");
                break;

            }
        }



        case 5:
            char correcta;
            char letras[] = { 'a', 'b', 'c', 'd', 'e' };
            bool valido = false;
            std::string justificacion;

            if(pregunta_seleccion)
            {
                std::cout << "Ingrese la nueva alternativa correcta: ";
                std::cin >> correcta;

                for (char letra : letras)
                {
                    if (letra == correcta)
                    {
                        pregunta_seleccion->setCorrecta(correcta);
                        valido = true;
                    }
                }

                if (valido)
                {
                    std::cout << "No ingreso una letra correcta, intentelo de nuevo..." << std::endl;
                    break;
                }
            }

            if(pregunta_vf)
            {
                std::cout << "Ingrese una nueva justificacion: ";
                std::cin.ignore();
                std::getline(std::cin, justificacion);

                if(justificacion.empty())
                {
                    std::cout << "La justificacion no puede estar vacia para un enunciado falso, intente de nuevo..." << std::endl;
                }
                else
                {
                    pregunta_vf->setJustificacion(justificacion);
                }
                break;
            }
        }

        std::cout << separador << std::endl;


    }
    
}

//4
void Prueba::borrarPregunta()
{
    int numero_pregunta;

    while (true)
    {
        int valido = this->lista_preguntas.size();
        mostrarPreguntas();
        std::cout << "Ingrese el numero de la pregunta que desea borrar (ingrese 0 para volver al menu): ";
        std::cin.ignore();
        std::cin >> numero_pregunta;

        if (numero_pregunta == 0)
        {
            return;
        }

        if (numero_pregunta > valido)
        {
            std::cout << separador << std::endl;
            std::cout << "Numero de pregunta fuera de rango, intente de nuevo" << std::endl;
            continue;
        }

        this->lista_preguntas.erase(this->lista_preguntas.begin() + (numero_pregunta - 1));
        std::cout << "Pregunta " << numero_pregunta << " borrada con exito! \n";

    }
}

//5
void Prueba::consultarItem()
{
    int consulta;
    int valido = this->lista_preguntas.size();
    while (true)
    {
        mostrarPreguntas();
        std::cout << "Ingrese el numero de la pregunta que desea consultar mas informacion (0 para volver al menu): ";
        std::cin >> consulta;

        if (consulta == 0)
        {
            return;
        }

        if (consulta > valido)
        {
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "Numero de pregunta fuera de rango, intente de nuevo" << std::endl;
            continue;
        }

        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Mostrando informacion de la pregunta: \n" << std::endl;

        this->lista_preguntas[consulta - 1]->mostrarInformacion();
        std::cout << "-------------------------------------------" << std::endl;
    }
}

//6
void Prueba::consultarPorTaxonomia()
{
    int consulta;
    std::vector<PreguntaBase*> lista_taxonomia;
    while (true)
    {
        lista_taxonomia.clear();
        std::cout << "1. RECORDAR" << "\n";
        std::cout << "2. ENTENDER" << "\n";
        std::cout << "3. APLICAR" << "\n";
        std::cout << "4. ANALIZAR" << "\n";
        std::cout << "5. EVALUAR" << "\n";
        std::cout << "6. CREAR" << "\n";
        std::cout << "Ingrese el nivel taxonomico (1-6) que desea buscar (0 para volver al menu): ";
        std::cin >> consulta;

        if (consulta == 0)
        {
            return;
        }

        if (consulta > 6)
        {
            std::cout << "Numero de taxonomia fuera de rango, intente de nuevo" << std::endl;
            std::cout << separador << std::endl;
            continue;
        }

        for (auto& pregunta : this->lista_preguntas)
        {
            if (pregunta->getTaxonomia() == consulta)
            {
                lista_taxonomia.push_back(pregunta.get());
            }
        }

        if (lista_taxonomia.size() != 0)
        {
            std::cout << "Estas son las preguntas segun la Taxonomia elegida: \n" << std::endl;

            for (int i = 0; i < lista_taxonomia.size(); i++)
            {
                std::cout << i + 1 << ". " << lista_taxonomia[i]->getEnunciado() << std::endl;
            }
            std::cout << separador << std::endl;
        }
        else
        {
            std::cout << "No se encontraron preguntas de tipo " << this->getTaxNameByInt(consulta) << std::endl;
            std::cout << separador << std::endl;
        }

    }
}

//7
int Prueba::tiempoPrueba()
{
    float tiempoTotal = 0;

    for (auto& pregunta : this->lista_preguntas)
    {
        tiempoTotal += pregunta->getDuracion();
    }

    return tiempoTotal;
}


void Prueba::iniciarPrueba()
{
    if (Dev_PreguntasDefault == 1)
    {
        Dev_crearPreguntasManual();
        std::cout << "PREGUNTAS MANUALES POR DEFAULT ACTIVADAS!" << std::endl;
        std::cout << "Cambiar Dev_PreguntasDefault a 0 para desactivarlas!" << std::endl;
    }
    else
    {
        std::cout << "Dev: existen preguntas de testeo que se agregan automaticamente, para anadirlas cambie Dev_PreguntasDefault a 1 dentro de Prueba.h" << std::endl;
    }

    int opcion = 0;
    // Menu

    while (opcion != 8)
    {

        opcion = menuPedirOpcion();
        std::cout << "\n";
        std::cout << separador << std::endl;
        switch (opcion)
        {
        case 1:
            generarPregunta();
            break;

        case 2:
            mostrarPreguntas();
            break;

        case 3:
            actualizarPrueba();
            break;

        case 4:
            borrarPregunta();
            break;

        case 5:
            consultarItem();
            break;

        case 6:
            consultarPorTaxonomia();
            break;

        case 7:
            std::cout << "El tiempo total de la prueba es de: " << tiempoPrueba() / 60 << " minutos. \n";
            break;

        case 8:
            std::cout << "Terminando programa..." << std::endl;
            break;
        }


    }
}

void Prueba::Dev_crearPreguntasManual()
{
    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Que musico invento la pieza musical Fur Elise?",
        Taxonomia::RECORDAR,
        20.0f,
        'a',
        std::map<char, std::string>
    {
        {'a', "Ludwig van Beethoven"},
        { 'b', "Wolfgang Amadeus Mozart" },
        { 'c', "Johann Sebastian Bach" },
        { 'd', "Frederic Chopin" },
        { 'e', "Daddy Yankee" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Cual es el 10% del numero 20.1?",
        Taxonomia::APLICAR,
        20.0f,
        'c',
        std::map<char, std::string>
    {
        {'a', "2.011"},
        { 'b', "201" },
        { 'c', "2,01" },
        { 'd', "0,201" },
        { 'e', "210" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Cual de los siguientes numeros equivale a 3/4",
        Taxonomia::APLICAR,
        20.0f,
        'e',
        std::map<char, std::string>
    {
        {'a', "0,34"},
        { 'b', "3,4" },
        { 'c', "1,25" },
        { 'd', "0,25" },
        { 'e', "0,75" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Cual de los siguientes elementos es un gas noble?",
        Taxonomia::RECORDAR,
        20.0f,
        'c',
        std::map<char, std::string>
    {
        {'a', "Oxigeno"},
        { 'b', "Nitrogeno" },
        { 'c', "Neon" },
        { 'd', "Cloro" },
        { 'e', "Carbono" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Que autor escribio 'Cien anos de soledad'?",
        Taxonomia::ENTENDER,
        25.0f,
        'b',
        std::map<char, std::string>
    {
        {'a', "Mario Vargas Llosa"},
        { 'b', "Gabriel Garcia Marquez" },
        { 'c', "Julio Cortazar" },
        { 'd', "Isabel Allende" },
        { 'e', "Jorge Luis Borges" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaSeleccion>(
        "Seleccione la opcion que mejor representa una estrategia para resolver un conflicto interpersonal en el trabajo:",
        Taxonomia::EVALUAR,
        30.0f,
        'd',
        std::map<char, std::string>
    {
        {'a', "Ignorar el problema y esperar que desaparezca"},
        { 'b', "Confrontar agresivamente al compañero" },
        { 'c', "Acusar al compañero con el supervisor sin hablar con el" },
        { 'd', "Escuchar activamente y proponer una solucion conjunta" },
        { 'e', "Evitar al compañero en todo momento" }
    }
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaVF>(
        "La fotosintesis es el proceso mediante el cual las plantas producen su propio alimento usando luz solar.",
        Taxonomia::ANALIZAR,
        15.0f,
        'v',
        ""
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaVF>(
        "El ADN se encuentra unicamente en el nucleo de las celulas animales.",
        Taxonomia::ANALIZAR,
        20.0f,
        'f',
        "El ADN tambien se encuentra en las mitocondrias, no exclusivamente en el nucleo."
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaVF>(
        "Los pinguinos pueden volar cortas distancias cuando huyen de depredadores.",
        Taxonomia::RECORDAR,
        20.0f,
        'f',
        "Los pinguinos no pueden volar, sus alas estan adaptadas para nadar, no para volar."
    ));

    this->lista_preguntas.push_back(std::make_unique<PreguntaVF>(
        "El agua hierve a 100 grados Celsius al nivel del mar.",
        Taxonomia::RECORDAR,
        10.0f,
        'v',
        ""
    ));
}

std::string Prueba::getTaxNameByInt(int taxonomia)
{
    switch (taxonomia)
    {
    case RECORDAR:   return "RECORDAR";
    case ENTENDER: return "ENTENDER";
    case APLICAR:   return "APLICAR";
    case ANALIZAR: return "ANALIZAR";
    case EVALUAR: return "EVALUAR";
    case CREAR: return "CREAR";
    }
}
