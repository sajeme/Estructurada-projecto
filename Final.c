/*Avances proyecto
Funcionalidades hasta ahora(1=ya hecho 1/2=esta codificado mas no implementado 0=Aun no se codifica)
1Registro 1Login 1Manejo de datos con ficheros y tokens 1Archivos de texto con ejercicios separados por rangos
1Despliegue de ejercicios
1/2Creacion de reporte de resultados por usuario(Aun no se incrusta al codigo)
0Creacion de reporte de resultados en general
Elaboro: Andres Mena Salazar, Julian Chan palomo
version 1.0
Fecha 17/06/2021
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//Delimitacion usada a la hora de leer el texto de archivos tranformando pedazitos de este en tokens
char delimitacion[] = ":::";
//Archivo de texto con la contraseña y nombre de los usuarios(no se modifica el paradero)
char Direccion[] = "cuentas.db";
//Archivo de texto con los datos de edad, peso, estatura y sexo(no se modifica el paradero)
char Direccion2[] = "datos.db";
int numusers=250;
char usuarios[250][3][250]={0};
char nombres[250][50];
int dias[250]={0};
double calHechas;
double totalCal[250]={0};
double pesoperdido;
int Eleccion[100][3]={0};
//Funciones a usar
void MenuDisplay();
void MenuSeleccion();
void Registro();
void InicioSesion();
void generadoReporte(char Archtxt[250],int posicion);
void reporteusuario(char nombre[30]);
void despliegueLogin(char nombre[30]);
void despliegueEjercicios(char sexo[10],int edad, float peso,int posicion);
void removerEspaciosblanco(char *s);
void alterarPeso(int posicion);
void reporteGeneral();
//estructura de datos para la hora del registro y luego se guarda en txt
struct login                           
{
	char nombre[50];
	int edad;
	double peso;
	double estatura;
	int sexo;
	char password[20];
};

int main(int argc, char *argv[]) {
	//llamado al menu
	MenuDisplay();
	return 0;
}

void MenuDisplay(){//menu del sistema
	for(;;){
	printf("Proyecto programacion estructurada\n");
	printf("---------------------------------------------------------\n");
	printf("--------------------------TonLess------------------------\n");
	printf("---------------------------------------------------------\n");
	printf("1. Registrarse\n");
	printf("2. Logearse\n");
	printf("3. Salir\n");
	MenuSeleccion();
	}
}
	
void Registro(){
	//abrir archivo donde se anexara nuevo usuario
	FILE *log;
	
	log=fopen(Direccion2,"a");
	if (log == NULL)
	{
		fputs("Error al abrir el archivo. Por favor revisa que la ruta de creacion sea correcta.", stderr);
		exit(0);
	}else{//"a" es para anexar algun nuevo dato al texto ya que si se usa "w" se estaria sobreescribiendo
		struct login lg;
		printf("Hola, bienvenido al sistema de ejercicios Tonless. Necesitamos capturar unos datos para el registro\n");
		printf("\nIngresa tu nombre(Servira de usuario):\n");
		gets(lg.nombre);
		fflush(stdin);
		printf("\nIngresa tu edad(int):\n");
		scanf("%d",&lg.edad);
		fflush(stdin);
		printf("\nIngresa tu peso(float):\n");
		scanf("%lf",&lg.peso);
		fflush(stdin);
		printf("\nIngresa tu estatura(float):\n");
		scanf("%lf",&lg.estatura);
		fflush(stdin);
		do{
		printf("\nIngresa tu sexo(int) Hombre=1 Mujer=2:\n");
		scanf("%d",&lg.sexo);
		}while(lg.sexo!=1&&lg.sexo!=2);
		fflush(stdin);
		printf("\nAhora por favor ingresa tu contraseña(no mas de 20 caracteres)\n");
		gets(lg.password);
		fflush(stdin);
		//se guardan el usuario,edad,peso,estatura,sexo y contraseña en datos.db
		fprintf(log,"\n%s:::%d:::%g:::%g:::%d:::%s",lg.nombre,lg.edad,lg.peso,lg.estatura,lg.sexo,lg.password);
		fclose(log);
		printf("\nEl registro fue hecho de manera correcta, %s\n",lg.nombre);
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
	int Confirm=0,cont=0,lin=0;//una confirmacion que indica que el usuario y contraseña son correctos
	char username[30],password[20];
//se piden credenciales de inicio de sesion
	printf("\nIngresa tus credenciales para iniciar sesion\n\n");
	fflush(stdin);
	printf("Username: ");
	gets(username);
	fflush(stdin);
	printf("\nPassword: ");
	gets(password);
	fflush(stdin);
	//se abre el archivo que tiene los usuarios y contraseñas
	FILE * sArchi = fopen(Direccion2,"r");
	while (fgets(linea, sizeof(linea), sArchi) != NULL)
	{//usuario y contraseña se separan en 2 tokens
		//en el arvhicos estan como "Usuario":::"Contraseña" el ::: es el delimitador del token
		const char* val1 = strtok(linea, delimitacion);
		while(val1!=NULL){
			cont++;
			strcpy(p,val1);
			removerEspaciosblanco(p);
			if(cont==1){
				strcpy(nombres[lin],p);
				if(strcmp(p,username)==0){//se pregunta si la primera linea tiene el mismo usuario
					Confirm++;
				}
			}
			if(cont==6&&Confirm==1){
				if(strcmp(p,password)==0){//se pregunta si la primera linea tiene el mismo usuario
					Confirm++;}else{Confirm=0;}
			}
			val1=strtok(NULL, delimitacion);
		}
		lin++;
		cont=0;
	}
	numusers=lin;
	fflush(stdin);
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
		if(s[i]=='   '|| s[i]=='\n'|| s[i]=='\t')
		{
			k++;
			i--;
		}
	}
}
	
void despliegueLogin(char nombre[30]){
	for(;;){
	int edad,cont=0,gen=0,Confirm=0,posicion=0,line=0;
	double estatura, peso;
	char p[250],linea[250],sexo[10],est[10],pes[10],ed[10];
	printf("\nInicio de sesión Correcto. Bienvenido %s", nombre);
	FILE * sArchi = fopen(Direccion2,"r");
	while (fgets(linea, sizeof(linea), sArchi) != NULL)
	{
		const char* val1 = strtok(linea, delimitacion);
		while(val1!=NULL){
			cont++;
			strcpy(p,val1);
			removerEspaciosblanco(p);
			if(strcmp(p,nombre)==0){//se pregunta si la primer token tiene el mismo usuario
				Confirm++;
			}
			if(cont==2&&Confirm==1){//se agarra su edad
				strcpy(ed,p);
				edad=atoi(ed);
			}
			if(cont==3&&Confirm==1){//se agarra su peso
				strcpy(pes,p);
				peso=atof(pes);
			}
			if(cont==4&&Confirm==1){//se agarra su estatura
				strcpy(est,p);
				estatura=atof(est);
				posicion=line;
			}
			if(cont==5&&Confirm==1){//se agarra su sexo
				strcpy(sexo,p);
				gen=atoi(sexo);
				if(gen==1){
					strcpy(sexo,"Hombre");
				}else{strcpy(sexo,"Mujer");}
			}
			val1=strtok(NULL, delimitacion);
		}
		line++;
		Confirm=0;
		cont=0;
	}
	fflush(stdin);
	fclose(sArchi);
	printf("\nEdad: %d anios. Peso: %g kg. Estatura: %g mts. Sexo: %s.\n",edad,peso,estatura,sexo);
	printf(",¿Qué quieres hacer?\n1.- Elegir ejercicios\n2.- Generar reporte de usuario\n3.-Reporte general todos usuarios\n (otro numero)Regresar al menu\n",nombre);
	int option;
	scanf("%d", &option);
	fflush(stdin);
	switch(option){
	case 1:
		if(dias[posicion]==0){
			system("CLS");//Despliegue de ejercicios segun parametros
			despliegueEjercicios(sexo,edad,peso,posicion);
			printf("\n\nPresiona cualquier tecla para continuar...");
			getchar();
			fflush(stdin);
			system("CLS");
			break;	
		}else{ 	
			printf("\nEstimado %s, ¿Realizó sus ejercicios?(1=Si,2=No):",nombre);
			int a;
			scanf("%d", &a);
			fflush(stdin);
			switch(a){
			case 1:
				system("CLS");//Despliegue de ejercicios segun parametros
				alterarPeso(posicion);
				despliegueEjercicios(sexo,edad,peso,posicion);
				printf("\n\nPresiona cualquier tecla para continuar...");
				getchar();
				fflush(stdin);
				system("CLS");
				break;
			default:
				printf("\nRegresando al login\n");
				InicioSesion();
				break;
			}
			break;
		}
		break;
	case 2:
		//Generacion del reporte del usuario
		system("CLS");
		reporteusuario(nombre);
		
		printf("\n\nPresiona cualquier tecla para continuar...");
		getchar();
		fflush(stdin);
		system("CLS");
		break;
	case 3:
		system("CLS");
		reporteGeneral();
		printf("\n\nPresiona cualquier tecla para continuar...");
		getchar();
		fflush(stdin);
		system("CLS");
		break;
	default:
		printf("\nHasta luego\n");
		system("CLS");
		MenuDisplay();
		break;
	}
		}
	}

	
void reporteusuario(char nombre[30]){
	char c;
	char destino[100]="Reporte Usuarios\\";
	strncat (destino, nombre, 30 );
	strncat (destino, ".txt", 4);
	FILE *sArchi;
	sArchi=fopen(destino,"r");//archivo de texto personalizado para el usuario
	c=fgetc(sArchi);
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(sArchi);
	}
	fclose(sArchi);
	
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
}
}

void despliegueEjercicios(char sexo[10],int edad, float peso,int posicion){
	printf("Ejercicios Disponibles: \n\n");
	char linea[250];
	int line=0,i=0;
	char Archtxt[250];
	FILE *sArchi;
	fflush(stdin);
		if(strcmp(sexo,"Hombre")==0){
			if(edad>=18&&edad<49){
				if(peso>=44&&peso<58){
					strcpy(Archtxt,"18 49 anios\\Hombre\\44 58 kg.txt");
				}else{
					if(peso>=58&&peso<66){
						strcpy(Archtxt,"18 49 anios\\Hombre\\58 66 kg.txt");
					}else{
						if(peso>=66&&peso<83){
							strcpy(Archtxt,"18 49 anios\\Hombre\\66 83 kg.txt");
						}else{
							if(peso>=83&&peso<98){
								strcpy(Archtxt,"18 49 anios\\Hombre\\83 98 kg.txt");
							}else{
								if(peso>=98&&peso<116){
									strcpy(Archtxt,"18 49 anios\\Hombre\\98 116 kg.txt");
								}else{
									strcpy(Archtxt,"18 49 anios\\Hombre\\mayor de 116 kg.txt");
								}
							}
						}
					}
				}
			}else{
				if(edad>=49&&edad<60){
					if(peso>=44&&peso<58){
						strcpy(Archtxt,"49 60 anios\\Hombre\\44 58 kg.txt");
					}else{
						if(peso>=58&&peso<66){
							strcpy(Archtxt,"49 60 anios\\Hombre\\58 66 kg.txt");
						}else{
							if(peso>=66&&peso<83){
								strcpy(Archtxt,"49 60 anios\\Hombre\\66 83 kg.txt");
							}else{
								if(peso>=83&&peso<98){
									strcpy(Archtxt,"49 60 anios\\Hombre\\83 98 kg.txt");
								}else{
									if(peso>=98&&peso<116){
										strcpy(Archtxt,"49 60 anios\\Hombre\\98 116 kg.txt");
									}else{
										strcpy(Archtxt,"49 60 anios\\Hombre\\mayor de 116 kg.txt");
									}
								}
							}
						}
					}
				}else{
					if(edad<18){
						if(peso>=44&&peso<58){
							strcpy(Archtxt,"menores 18 anios\\Hombre\\44 58 kg.txt");
						}else{
							if(peso>=58&&peso<66){
								strcpy(Archtxt,"menores 18 anios\\Hombre\\58 66 kg.txt");
							}else{
								if(peso>=66&&peso<83){
									strcpy(Archtxt,"menores 18 anios\\Hombre\\66 83 kg.txt");
								}else{
									if(peso>=83&&peso<98){
										strcpy(Archtxt,"menores 18 anios\\Hombre\\83 98 kg.txt");
									}else{
										if(peso>=98&&peso<116){
											strcpy(Archtxt,"menores 18 anios\\Hombre\\98 116 kg.txt");
										}else{
											strcpy(Archtxt,"menores 18 anios\\Hombre\\mayor de 116 kg.txt");
										}
									}
								}
							}
						}
					}else{
						if(edad>60){
							if(peso>=44&&peso<58){
								strcpy(Archtxt,"mayores 60 anios\\44 58 kg.txt");
							}else{
								if(peso>=58&&peso<66){
									strcpy(Archtxt,"mayores 60 anios\\58 66 kg.txt");
								}else{
									if(peso>=66&&peso<83){
										strcpy(Archtxt,"mayores 60 anios\\66 83 kg.txt");
									}else{
										if(peso>=83&&peso<98){
											strcpy(Archtxt,"mayores 60 anios\\83 98 kg.txt");
										}else{
											if(peso>=98&&peso<116){
												strcpy(Archtxt,"mayores 60 anios\\98 116 kg.txt");
											}else{
												strcpy(Archtxt,"mayores 60 anios\\mayor de 116 kg.txt");
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else{
			if(edad>=18&&edad<49){
				if(peso>=44&&peso<58){
					strcpy(Archtxt,"18 49 anios\\Mujer\\44 58 kg.txt");
				}else{
					if(peso>=58&&peso<66){
						strcpy(Archtxt,"18 49 anios\\Mujer\\58 66 kg.txt");
					}else{
						if(peso>=66&&peso<83){
							strcpy(Archtxt,"18 49 anios\\Mujer\\66 83 kg.txt");
						}else{
							if(peso>=83&&peso<98){
								strcpy(Archtxt,"18 49 anios\\Mujer\\83 98 kg.txt");
							}else{
								if(peso>=98&&peso<116){
									strcpy(Archtxt,"18 49 anios\\Mujer\\98 116 kg.txt");
								}else{
									strcpy(Archtxt,"18 49 anios\\Mujer\\mayor de 116 kg.txt");
								}
							}
						}
					}
				}
			}else{
				if(edad>=49&&edad<60){
					if(peso>=44&&peso<58){
						strcpy(Archtxt,"49 60 anios\\Mujer\\44 58 kg.txt");
					}else{
						if(peso>=58&&peso<66){
							strcpy(Archtxt,"49 60 anios\\Mujer\\58 66 kg.txt");
						}else{
							if(peso>=66&&peso<83){
								strcpy(Archtxt,"49 60 anios\\Mujer\\66 83 kg.txt");
							}else{
								if(peso>=83&&peso<98){
									strcpy(Archtxt,"49 60 anios\\Mujer\\83 98 kg.txt");
								}else{
									if(peso>=98&&peso<116){
										strcpy(Archtxt,"49 60 anios\\Mujer\\98 116 kg.txt");
									}else{
										strcpy(Archtxt,"49 60 anios\\Mujer\\mayor de 116 kg.txt");
									}
								}
							}
						}
					}
				}else{
					if(edad<18){
						if(peso>=44&&peso<58){
							strcpy(Archtxt,"menores 18 anios\\Mujer\\44 58 kg.txt");
						}else{
							if(peso>=58&&peso<66){
								strcpy(Archtxt,"menores 18 anios\\Mujer\\58 66 kg.txt");
							}else{
								if(peso>=66&&peso<83){
									strcpy(Archtxt,"menores 18 anios\\Mujer\\66 83 kg.txt");
								}else{
									if(peso>=83&&peso<98){
										strcpy(Archtxt,"menores 18 anios\\Mujer\\83 98 kg.txt");
									}else{
										if(peso>=98&&peso<116){
											strcpy(Archtxt,"menores 18 anios\\Mujer\\98 116 kg.txt");
										}else{
											strcpy(Archtxt,"menores 18 anios\\Mujer\\mayor de 116 kg.txt");
										}
									}
								}
							}
						}
					}else{
						if(edad>60){
							if(peso>=44&&peso<58){
								strcpy(Archtxt,"mayores 60 anios\\44 58 kg.txt");
							}else{
								if(peso>=58&&peso<66){
									strcpy(Archtxt,"mayores 60 anios\\58 66 kg.txt");
								}else{
									if(peso>=66&&peso<83){
										strcpy(Archtxt,"mayores 60 anios\\66 83 kg.txt");
									}else{
										if(peso>=83&&peso<98){
											strcpy(Archtxt,"mayores 60 anios\\83 98 kg.txt");
										}else{
											if(peso>=98&&peso<116){
												strcpy(Archtxt,"mayores 60 anios\\98 116 kg.txt");
											}else{
												strcpy(Archtxt,"mayores 60 anios\\mayor de 116 kg.txt");
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		fflush(stdin);
		sArchi=fopen(Archtxt,"r");
		while (fgets(linea, sizeof(linea), sArchi) != NULL)
		{
			line++;
			const char* val1 = strtok(linea, delimitacion);
			const char* val2 = strtok(NULL, delimitacion);
			printf("%d.-Ejercicio: %s, Calorias: %s\n",line,val1,val2);
		}
		fflush(stdin);
		fclose(sArchi);
		printf("\nPor favor, selecciona 3 ejercicios a realizar \n");
		do{
			printf("\nPrimer Ejercicio: ");
			scanf("%d",&Eleccion[posicion][0]);
			fflush(stdin);
		}while(Eleccion[posicion][0]<=0||Eleccion[posicion][0]>line);
		do{
			printf("\nSegundo Ejercicio: ");
			scanf("%d",&Eleccion[posicion][1]);
			fflush(stdin);
		}while(Eleccion[posicion][1]<=0||Eleccion[posicion][1]>line);
		do{
			printf("\nTercer Ejercicio: ");
			scanf("%d",&Eleccion[posicion][2]);
			fflush(stdin);
		}while(Eleccion[posicion][2]<=0||Eleccion[posicion][2]>line);	fflush(stdin);
		for(i=0;i<3;i++){
			Eleccion[posicion][i]--;
		}
		dias[posicion]++;
		generadoReporte(Archtxt,posicion);
	}
	
	void alterarPeso(int posicion){
		char linea[250],nombre[50],ed[3],pes[10],est[10],sexo[10],pass[20],p[250];
		int Confirm=0,cont=0;
		double peso,pesoperdido;
		srand(time(NULL));
		pesoperdido=((double)rand()/((double)RAND_MAX))*(0.07-0.02)+0.02;
		FILE * sArchi = fopen(Direccion2,"r");
		while (fgets(linea, sizeof(linea), sArchi) != NULL)
		{
		const char* val1 = strtok(linea, delimitacion);
		while(val1!=NULL){
			cont++;
			strcpy(p,val1);
			removerEspaciosblanco(p);
			if(strcmp(nombres[posicion],p)==0){//se pregunta si la primer token tiene el mismo usuario
				Confirm++;
				strcpy(nombre,p);
			}
			if(cont==2&&Confirm==1){//se agarra su edad
				strcpy(ed,p);
			}
			if(cont==3&&Confirm==1){//se agarra su peso
				strcpy(pes,p);
				peso=atof(pes);
			}
			if(cont==4&&Confirm==1){//se agarra su estatura
				strcpy(est,p);
			}
			if(cont==5&&Confirm==1){//se agarra su sexo
				strcpy(sexo,p);
			}
			if(cont==6&&Confirm==1){
				strcpy(pass,p);
			}
			val1=strtok(NULL, delimitacion);
		}
		Confirm=0;
		cont=0;
		}
		peso=peso-pesoperdido;
		fflush(stdin);
		char newline[100]={0};
		removerEspaciosblanco(newline);
		char newline1[100]={0};
		removerEspaciosblanco(newline1);
		strncat (newline, nombre, 30 );
		strncat (newline, delimitacion, 3);
		strncat (newline, ed, 3);
		strncat (newline, delimitacion, 3);
		
		strncat (newline1, delimitacion, 3);
		strncat (newline1, est, 5);
		strncat (newline1, delimitacion, 3);
		strncat (newline1, sexo, 3);
		strncat (newline1, delimitacion, 3);
		strncat (newline1, pass, 20);
		cont=0;
		fclose(sArchi);
		sArchi=fopen(Direccion2,"r");
		FILE * temp = fopen("temp.txt","w");
		while ((fgets(linea, sizeof(linea), sArchi)) != NULL)
		{
			cont++;
			/* If current line is line to replace */
			if (cont == posicion+1){
				fputs(newline, temp);
				fprintf(temp,"%g",peso);
				fputs(newline1, temp);
				fputs("\n", temp);}
			else
				fputs(linea, temp);
		}
		fclose(sArchi);
		fclose(temp);
		remove(Direccion2);
		rename("temp.txt",Direccion2);
	}
		
	void generadoReporte(char Archtxt[250],int posicion){
		int line=0,i=0,days,weeks=1;
		double cal=0;
		char linea[250],p[250];
		system("CLS");
		printf("Ejercicios a realizar: \n\n");
		for(i=0;i<3;i++){
			FILE *sArchi;
			sArchi=fopen(Archtxt,"r");
		while (fgets(linea, sizeof(linea), sArchi) != NULL)
		{
			const char* exer = strtok(linea, delimitacion);
			const char* calr = strtok(NULL, delimitacion);
			if(Eleccion[posicion][i]==line){
					strcpy(p,exer);
					printf("%s\n",p);
					strcpy(usuarios[i][dias[posicion]],p);
					strcpy(p,calr);
					cal=atof(p);
					calHechas=cal+calHechas;
					break;
			}
			line++;
		}
		line=0;
		fclose(sArchi);
		}
		FILE *sArchi;
		char destino[100]="Reporte Usuarios\\";
		strncat (destino, nombres[posicion], 30 );
		strncat (destino, ".txt", 4);
		printf("\nEl reporte de calorias hechos de este dia se encuentra en: %s",destino);
		if(dias[posicion]==1){
			sArchi=fopen(destino,"w");//archivo de texto personalizado para el usuario
			fputs("\t\tDia 1\t\tDia 2\t\tDia 3\t\tDia 4\t\tDia 5\t\tDia 6\t\tDia 7\nweek 1",sArchi);
			fprintf(sArchi,"\t\t%g",calHechas);
			fputs("cal",sArchi);
			fclose(sArchi);
		}else{
			days=dias[posicion];
			if(days%7==0){
				sArchi=fopen(destino,"a");
				fprintf(sArchi,"\t\t%g",calHechas);
				fputs("cal\nweek",sArchi);
				weeks=(days/7)+weeks;
				fprintf(sArchi,"%d",weeks);
				fclose(sArchi);
			}else{
				sArchi=fopen(destino,"a");
				fprintf(sArchi,"\t\t%g",calHechas);
				fputs(" cal",sArchi);
				fclose(sArchi);
			}
			
		}
		totalCal[posicion]=calHechas+totalCal[posicion];
		calHechas=0;
	}
		
	void reporteGeneral(){
	int i;
	char c;
	char destino[100]="Reporte General";
	strncat (destino, ".txt", 4);
	printf("\n");
	FILE *sArchi;
	sArchi=fopen(destino,"w");
	for(i=0;i<numusers;i++){
		fprintf(sArchi,"\nUsuario: %s Calorias totales: %g\n",nombres[i],totalCal[i]);
		i++;
	}
	fclose(sArchi);
	sArchi=fopen(destino,"r");//archivo de texto personalizado para el usuario
	c=fgetc(sArchi);
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(sArchi);
	}
	fclose(sArchi);
	}

	
