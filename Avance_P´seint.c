/*Avances proyecto
Funcionalidades hasta ahora(1=ya hecho 1/2=esta codificado mas no implementado 0=Aun no se codifica)
1Registro 1Login 1Manejo de datos con ficheros y tokens 1Archivos de texto con ejercicios separados por rangos
1/2Despliegue de ejercicios(Aun no implementada del todo segun rangos de edad,sexo y peso)
1/2Creacion de reporte de resultados por usuario(Aun no se incrusta al codigo)
0Creacion de reporte de resultados en general
Elaboro: Andres Mena Salazar, Julian Chan palomo
version 1.0
Fecha 17/06/2021
*/
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
//Delimitacion usada a la hora de leer el texto de archivos tranformando pedazitos de este en tokens
char delimitacion[] = "::: ";
//Archivo de texto con la contrase�a y nombre de los usuarios(no se modifica el paradero)
char Direccion[] = "cuentas.db";
//Archivo de texto con los datos de edad, peso, estatura y sexo(no se modifica el paradero)
char Direccion2[] = "datos.db";
//Funciones a usar
void MenuDisplay();
void MenuSeleccion();
void Registro();
void InicioSesion();
void reporteusuario(char nombre[30]);
void despliegueLogin(char nombre[30]);
/*void despliegueEjercicios(char nombre[30]);*/
void removerEspaciosblanco(char *s);

//estructura de datos para la hora del registro y luego se guarda en txt
struct login                           
{
	char nombre[50];
	int edad;
	double peso;
	double estatura;
	char password[20];
};

int main(int argc, char *argv[]) {
	//llamado al menu
	MenuDisplay();
	return 0;
}

void MenuDisplay(){//menu del sistema
	printf("---------------------------------------------------------\n");
	printf("--------------------------TonLess------------------------\n");
	printf("---------------------------------------------------------\n");
	printf("1. Registrarse\n");
	printf("2. Logearse\n");
	printf("3. Salir\n");
	MenuSeleccion();
}
	
void Registro(){
	//abrir archivo donde se anexara nuevo usuario
	FILE *log;
	
	log=fopen(Direccion,"a");
	if (log == NULL)
	{
		fputs("Error al abrir el archivo. Por favor revisa que la ruta de creacion sea correcta.", stderr);
		exit(0);
	}else{//"a" es para anexar algun nuevo dato al texto ya que si se usa "w" se estaria sobreescribiendo
		log=fopen(Direccion,"a");
		struct login lg;
		printf("Hola, bienvenido al sistema de ejercicios Tonless. Necesitamos capturar unos datos para el registro\n");
		printf("\nIngresa tu nombre(Servira de usuario):\n");
		gets(lg.nombre);
		fflush(stdin);
		printf("\nIngresa tu edad:\n");
		scanf("%d",&lg.edad);
		fflush(stdin);
		printf("\nIngresa tu peso:\n");
		scanf("%lf",&lg.peso);
		fflush(stdin);
		printf("\nIngresa tu estatura:\n");
		scanf("%lf",&lg.estatura);
		fflush(stdin);
		printf("\nAhora por favor ingresa tu contrase�a(no mas de 20 caracteres)\n");
		gets(lg.password);
		fflush(stdin);
		//se guardan el usuario y contrase�a en cuenta.db
		fprintf(log,"%s:::%s\n",lg.nombre,lg.password);
		fclose(log);
		printf("\nEl registro fue hecho de manera correcta, %s\n",lg.nombre);
		log=fopen(Direccion2,"a");
		//se guardan edad peso, estatura y sexo en datos .db
		fprintf(log,"%s:::%d:::%g:::%g:::%s\n",lg.nombre,lg.edad,lg.peso,lg.estatura,lg.password);
		fclose(log);
		printf("Presiona cualquier tecla para continuar...");
		getchar();
		fflush(stdin);
		system("CLS");
		//se manda al usuario directo a la funcion login
		InicioSesion();
	}	
	
	
}

void InicioSesion(){
	char linea[250],p[250];
	int Confirm=0;//una confirmacion que indica que el usuario y contrase�a son correctos
	char username[30],password[20];
	FILE *log;
	
	log = fopen(Direccion,"r");
	if (log == NULL)
	{
		fputs("Error al abrir el archivo. Por favor revisa que la ruta de creacion sea correcta.", stderr);
		exit(0);
	}
//se piden credenciales de inicio de sesion
	printf("\nIngresa tus credenciales para iniciar sesion\n\n");
	fflush(stdin);
	printf("Username: ");
	gets(username);
	fflush(stdin);
	printf("\nPassword: ");
	gets(password);
	fflush(stdin);
	//se abre el archivo que tiene los usuarios y contrase�as
	FILE * sArchi = fopen(Direccion,"r");
	while (fgets(linea, sizeof(linea), sArchi) != NULL)
	{//usuario y contrase�a se separan en 2 tokens
		//en el arvhicos estan como "Usuario":::"Contrase�a" el ::: es el delimitador del token
		const char* val1 = strtok(linea, delimitacion);
		const char* val2 = strtok(NULL, delimitacion);
		strcpy(p,val1);
		if(strcmp(p,username)==0){//se pregunta si la primera linea tiene el mismo usuario
			Confirm++;}//primera confirmacion
		strcpy(p,val2);
		removerEspaciosblanco(p);//se remueven posibles espacios de la contrase�a
		removerEspaciosblanco(password);
		if(strcmp(p,password)==0){//se pregunta si las contrase�as coinciden
			Confirm++;}//La confirmacion deberia pasar a 2 si el usuario es correcto
	}
	fflush(stdin);
	fclose(sArchi);
	if(Confirm==2){//confirmando el login
		despliegueLogin(username);
	}else{//se manda el usuario al menu
		printf("\nDatos ingresados incorrectos, regresando al menu........\n");
			MenuDisplay();
	}
}
	
void removerEspaciosblanco(char *s){
	int  i,k=0;
	
	for(i=0;s[i];i++)
	{
		s[i]=s[i+k];
		if(s[i]=='   '|| s[i]=='\n')
		{
			k++;
			i--;
		}
	}
}
	
void despliegueLogin(char nombre[30]){
/*	int edad;*/
/*	double estatura, peso;*/
/*	char p[250],linea[250];*/
	printf("\nInicio de sesi�n Correcto. Bienvenido %s", nombre);
/*	FILE * sArchi = fopen(Direccion,"r");*/
/*	while (fgets(linea, sizeof(linea), sArchi) != NULL)*/
/*	{*/
/*		const char* val1 = strtok(linea, delimitacion);*/
/*		strcpy(p,val1);*/
/*		if(strcmp(p,nombre)==0){*/
/*			edad=strtok(p, delimitacion);*/
/*		}*/
/*	}*/
/*	fflush(stdin);*/
/*	fclose(sArchi);*/
	printf(",�Qu� quieres hacer?\n1.- Elegir ejercicios\n2.- Generar reporte de usuario\n (otro boton)Regresar al menu\n",nombre);
	int option;
	scanf("%d", &option);
	fflush(stdin);
	switch(option){
	case 1:
		system("CLS");//Despliegue de ejercicios segun parametros
		despliegueEjercicios(nombre);
		break;
	case 2:
		system("CLS");//Generacion del reporte del usuario
		reporteusuario(nombre);
		break;
	default:
		printf("\nHasta luego\n");
		MenuDisplay();//ir al menu nuevamente
		break;
	}
	}

	
void reporteusuario(char nombre[30]){
/*	char destino[100]="Reporte Usuarios\";
	strncat (destino, nombre, 30 );
	strncat (destino, ".txt", 4);
	removerEspaciosblanco(destino);
	FILE *sArchi;
	sArchi=fopen(destino,"w")//archivo de texto personalizado para el usuario
	
	*/
}
	
void MenuSeleccion(){//Seleccionar la opcion que quieras hacer lo que te lleva a otra funcion correspondiente
	int option;
	scanf("%d", &option);
	fflush(stdin);
	switch(option){
	case 1:
		system("CLS");//crear nuevos usuarios
		Registro();
		break;
	case 2:
		system("CLS");//Iniciar sesion si ya se tiene un usuario existente
		InicioSesion();
		break;
	case 3:
		printf("\nHasta luego\n");
		exit(0);//salida del sistema
	default:
		system("CLS");
		printf("\nIntentalo de nuevo rey\n");
		MenuDisplay();
}
}

void despliegueEjercicios(char nombre[30]){
	/*
	FILE *sArchi;
	if(edad>=18&&edad<49){
	
	if(peso>=44&&peso<58){
	sArchi=fopen("44 58 kg .txt","r");
		}else{if(peso>=58&&peso<66){
	sArchi=fopen("58 66 kg .txt","r");
	}else{if(peso>=66&&peso<83){
	sArchi=fopen("66 83 kg .txt","r");
			}else{if(peso>=83&&peso<98){
	sArchi=fopen("83 98 kg .txt","r");
			}else{if(peso>=98&&peso<116){
	sArchi=fopen("98 116 kg .txt","r");
			}else{
	sArchi=fopen("mayor 116 kg .txt","r");
			}	}
			}
		}
		}
		}else{if(edad>=49&&edad<60){
					if(peso>=44&&peso<58){
					sArchi=fopen("44 58 kg .txt","r");
				}else{if(peso>=58&&peso<66){
					sArchi=fopen("58 66 kg .txt","r");
				}else{if(peso>=66&&peso<83){
					sArchi=fopen("66 83 kg .txt","r");
				}else{if(peso>=83&&peso<98){
					sArchi=fopen("83 98 kg .txt","r");
				}else{if(peso>=98&&peso<116){
					sArchi=fopen("98 116 kg .txt","r");
				}else{
					sArchi=fopen("mayor 116 kg .txt","r");
				}	}
				}
				}
				}
		}else{if(edad<18){
				if(peso>=44&&peso<58){
				sArchi=fopen("44 58 kg .txt","r");
			}else{if(peso>=58&&peso<66){
				sArchi=fopen("58 66 kg .txt","r");
			}else{if(peso>=66&&peso<83){
				sArchi=fopen("66 83 kg .txt","r");
			}else{if(peso>=83&&peso<98){
				sArchi=fopen("83 98 kg .txt","r");
			}else{if(peso>=98&&peso<116){
				sArchi=fopen("98 116 kg .txt","r");
			}else{
				sArchi=fopen("mayor 116 kg .txt","r");
			}	}
			}
			}
			}
		}
			}else{if(edad>60){
					if(peso>=44&&peso<58){
					sArchi=fopen("44 58 kg .txt","r");
				}else{if(peso>=58&&peso<66){
					sArchi=fopen("58 66 kg .txt","r");
				}else{if(peso>=66&&peso<83){
					sArchi=fopen("66 83 kg .txt","r");
				}else{if(peso>=83&&peso<98){
					sArchi=fopen("83 98 kg .txt","r");
				}else{if(peso>=98&&peso<116){
					sArchi=fopen("98 116 kg .txt","r");
				}else{
					sArchi=fopen("mayor 116 kg .txt","r");
				}	}
				}
				}
				}
			}
			}
			
			}	
	}
	*/
	}

