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

	int conexion;
	char* ip;
	char* puerto;

	t_log* logger = iniciar_logger();
	log_info(logger, "Soy un log");

	t_config* config = leer_config();

	//asignar valor de config a la variable valor
	char* clave = config_get_string_value(config, "CLAVE");
	log_info(logger, clave);

	//Loggear valor de config

	leer_consola(logger);

	/*----------------------------------PARTE 3-------------------------------------------*/
	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.
	//crear conexion
	conexion = crear_conexion(
					config_get_string_value(config, "IP"),
					config_get_string_value(config, "PUERTO")
				);

	enviar_mensaje(clave, conexion);


	paquete(conexion);

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
	t_paquete* paquete = crear_paquete();

	char* leido = readline(">");
	if (strncmp(leido,"", 1) != 0) {
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
	}
	free(leido);
	enviar_paquete(conexion, paquete);
	return eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}

