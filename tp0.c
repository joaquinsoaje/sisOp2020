/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h> //quizá no haga falta

int main(void)
{
	/*------------------------------PARTE 2-------------------------------------------*/

	// Inicializo variables
	int conexion;
	char* ip;
	char* puerto;
	char* clave;
	t_log logger;
	t_config* config;
 
	// Inicializo logger y logueo un primer texto
	logger = iniciar_logger();
	log_info(logger, "Soy un log");

	// Inicializo config y muestro el valor que tiene de clave
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

	// Se guardan los valores que ingrese el usuario por consola y se envian al servidor
	paquete(conexion);

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
	char* leido = readline(">");
	if (strncmp(leido,"", 1) != 0) {
		log_info(logger, leido);
		free(leido);
		leer_consola(logger);
	}
	return free(leido);
}

void paquete(int conexion)
{
	t_paquete* paquete = crear_super_paquete();
	char* leido = readline(">");

	if (strncmp(leido,"", 1) != 0) {
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
		leido = readline(">");
	}

	free(leido);
	enviar_paquete(conexion, paquete);

	return eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}

