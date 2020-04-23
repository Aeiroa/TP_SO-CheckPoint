
#include "tp0.h"
#include "utils.h"

int main(void)
{

	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;



	logger = iniciar_logger();

	log_info(logger,"soy un log");

	config = leer_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");

	log_info(logger,"Leí la IP %s y puerto %s\n",ip,puerto);



	conexion = crear_conexion(ip,puerto);



	enviar_mensaje("The cake is a lie",conexion);



	char *mensaje = recibir_mensaje(conexion);



	log_info(logger,"El mensaje recibido es: %s\n", mensaje);

	terminar_programa(conexion, logger, config);
}


t_log* iniciar_logger(void){

	t_log *logger = log_create("tp0.log","logger",true,LOG_LEVEL_INFO);
	if(logger == NULL){
		printf("No pude crear el logger \n");
		exit(1);
	}

	return logger;
}




t_config* leer_config(void){

	t_config* config = config_create("/home/utnso/Game-watch-client/tp0.config");
	if(config == NULL){
		printf("No pude leer la config \n");
		exit(2);
	}

	return config;
}



void terminar_programa(int conexion, t_log* logger, t_config* config){

	if(logger != NULL){
		log_destroy(logger);
	}

	if(config != NULL){
		config_destroy(config);
	}

	liberar_conexion(conexion);
}

