/*
 * main.c
 *
 *	Resolución de tp 2020
 *
 */

#include "tp0.h"
#include <commons/log.h>
#include <commons/config.h>

int main(void)
{
	/*------------------------------PARTE 2-------------------------------------------*/

	// Inicializo variables
	int conexion;
	char* clave;
	t_log* logger;
	t_config* config;
 
	// Inicializo logger y logueo un primer texto
	logger = iniciar_logger();
	log_info(logger, "Soy un log");

	// Inicializo config y muestro el valor de key clave
	config = leer_config();

	clave = config_get_string_value(config, "CLAVE");
	log_info(logger, clave);

	// Dejo la consola esperando y guardando valores que el usuario ingrese
	leer_consola(logger);

	/*----------------------------------PARTE 3-------------------------------------------*/

	//crear conexion a servidor
	conexion = crear_conexion(
					config_get_string_value(config, "IP"),
					config_get_string_value(config, "PUERTO")
				);

	// Se envia a servidor el valor de clave
	enviar_mensaje(clave, conexion);

	// Se guardan los valores que ingrese el usuario en paquete
	armar_paquete(conexion);

	// Por último, liberamos el programa de lo que estuvimos usando
	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger()
{
	return log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);
}

t_config* leer_config()
{
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	void _loggear(char* leido) {
		log_info(logger, leido);
	}
	_usar_consola((void*)_loggear);

}

void armar_paquete(int conexion)
{
	// Se inicializa paquete
	t_paquete* paquete = crear_super_paquete();

	void _agregar_a_paquete(char* leido) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	}

	//Se guarda los valores de consola en paquete
	_usar_consola((void*)_agregar_a_paquete);

	// Se envian los valores guardados al servidor
	enviar_paquete(paquete, conexion);

	// Libero recursos
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}

void _usar_consola(void(*funcion)(char*)) {
	char* leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		funcion(leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}
