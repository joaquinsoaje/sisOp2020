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
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;

	t_log* logger = iniciar_logger();
	log_info(logger, "Soy un log");

	t_config* config = leer_config();

	//asignar valor de config a la variable valor
	char* valor = config_get_string_value(config, "CLAVE");
	log_info(logger, valor);

	//Loggear valor de config

	leer_consola(logger);

	terminar_programa(1, logger, config);

	log_info(logger, "Se borro todo");

	return 0;

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion

	//enviar CLAVE al servirdor

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
	//El primero te lo dejo de yapa
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
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
