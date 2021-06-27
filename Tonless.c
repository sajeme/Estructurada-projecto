/* proyecto
Sistema de desppliegue de ejercicios que calendariza calorias hechas por usuario, altera pesos y da reportes generales
Elaboro: Andrés Mena Salazar y Julian Chan Palomo
version 4.0
Fecha 26/06/2021
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//Delimitacion usada a la hora de leer el texto de archivos tranformando pedazitos de este en tokens
char delimitacion[] = ":::";
//Archivo de texto con los datos de nombre,edad, peso, estatura, sexo y contraseña
char Direccion2[] = "datos.db";
int numusers=250;//usuarios maximos
char nombres[250][50];//guarda nombres
int dias[250]={0};//guarda conteo de dias por usuario
double calHechas;//calorias hechas en 1 dia y se escribe en el txt
double totalCal[250]={0};//total calorias por usuario mientras el programa este abierto
double pesoperdido;//randomizado del peso perdido
int Eleccion[100][3]={0};//eleccion de ejercicios
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
	system("color 0C");
	printf("\n\t\t\t\t\tProyecto programacion estructurada\n\n");
	printf(" \t\t__________________________________________________________________________________\n");
	printf("\t\t|..................................................................................|\n");
	printf("\t\t|.._________...._________...._........_...._........._______..._______...._______..|\n");
	printf("\t\t|.|___   ___|..|  _____  |..|  \\.....| |..| |.......|  ____|..|  _____|..|  _____|.|\n");
	printf("\t\t|.....| |......| |.....| |..| |\\\\....| |..| |.......| |.......| |........| |.......|\n");
	printf("\t\t|.....| |......| |.....| |..| |.\\\\...| |..| |.......| |____...| |_____ ..| |.......|\n");
	printf("\t\t|.....| |......| |.....| |..| |..\\\\..| |..| |.......|  ____|..|_____  |..|_____  |.|\n");
	printf("\t\t|.....| |......| |.....| |..| |...\\\\ | |..| |.......| |.............| |........| |.|\n");
	printf("\t\t|.....| |......| |.....| |..| |....\\\\| |..| |.......| |.............| |........| |.|\n");
	printf("\t\t|.....|_|......|_________|..|_|.....\\ _|..|______|..|______|..|_______|..|_______|.|\n");
	printf("\t\t|..................................................................................|\n");
	printf("\t\t|__________________________________________________________________________________|\n");
	printf("\n\t\t\t\tEjercita tu cuerpo, mente y espiritu con TONLESS\n\n");
	printf("\n\t\t\t\t\t\t   1. Registrarse\n");
	printf("\t\t\t\t\t\t   2. Logearse\n");
	printf("\t\t\t\t\t\t   3. Salir\n\n");
	printf("\t\t\t\t    Ingrese la opcion que desea realizar: ");
	MenuSeleccion();
}
	
void Registro(){
	system("color 07");
	//abrir archivo donde se anexara nuevo usuario
	FILE *log;
	//"a" es para anexar algun nuevo dato al texto ya que si se usa "w" se estaria sobreescribiendo
	log=fopen(Direccion2,"a");
	if (log == NULL)
	{
		fputs("Error al abrir el archivo. Por favor revisa que la ruta de creacion sea correcta.", stderr);
		exit(0);
	}else{
		struct login lg;
		printf("\n\t\t\t\t\t\tRegistro\n");
		printf("\t\t\t\t\t   __________________\n\n");
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
		printf("\nEl registro fue hecho de manera correcta, %s\n\n",lg.nombre);
		printf("Presiona cualquier tecla para continuar...");
		getchar();
		fflush(stdin);
		system("CLS");
		//se manda al usuario directo a la funcion login
		InicioSesion();
	}	
	
	
}

void InicioSesion(){
	system("color 07");//le damos color al cmd
	printf("\n\t\t\t\t\t\tInicio de sesion\n");
	printf("\t\t\t\t\t   __________________________\n\n");
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
		printf("\nDatos ingresados incorrectos, regresando al menu.\n");
		printf("\nPresione cualquier tecla para continuar...");
		getchar();
		fflush(stdin);
		system("CLS");
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
	system("color 0B");
	int edad,cont=0,gen=0,Confirm=0,posicion=0,line=0;
	double estatura, peso;
	char p[250],linea[250],sexo[10],est[10],pes[10],ed[10];
	system("cls");
	printf("\n\t\t\t\t\t\tMenu principal\n");
	printf("\t\t\t\t\t   _______________________\n\n");	
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
	printf("\nEdad: %d anios. Peso: %g kg. Estatura: %g mts. Sexo: %s.\n\n",edad,peso,estatura,sexo);
	printf(",¿Qué quieres hacer?\n1.- Elegir ejercicios\n2.- Generar reporte de usuario\n3.-Reporte general todos usuarios\n (otro numero)Regresar al menu\n\n\nIngrese la opcion que desea realizar:\n",nombre);
	int option;//el peso se va modificando cada que confirma ejercicios hechos
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
			printf("\nEstimado %s, ¿Realizó sus ejercicios anteriores?(1=Si,2=No):",nombre);//se pregunta si realizo sus ejercicios previos
			int a;
			scanf("%d", &a);
			fflush(stdin);
			switch(a){
			case 1:
				system("CLS");//Altera el peso del archivo .db
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
		system("CLS");//reporte de todos los usuarios
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
	system("color 0E	");
	char c;
	char destino[100]="Reporte Usuarios\\";
	strncat (destino, nombre, 30 );
	strncat (destino, ".txt", 4);
	FILE *sArchi;
	sArchi=fopen(destino,"r");//archivo de texto personalizado para el usuario
	c=fgetc(sArchi);//solo lee el archivo
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
		printf("\n\n\t\t\t\t\t\t\tHasta luego.\n");
		exit(0);//salida del sistema
	default:
		system("CLS");
		printf("\nPor favor, ingrese una opción disponible.\n");
		MenuDisplay();
}
}

void despliegueEjercicios(char sexo[10],int edad, float peso,int posicion){
	system("color 03");
	printf("Ejercicios Disponibles: \n\n");
	char linea[250];
	int line=0,i=0;
	char Archtxt[250];
	FILE *sArchi;
	fflush(stdin);//busca los ejercicios entre las carpetas dependiendo de edad, sexo y peso
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
		sArchi=fopen(Archtxt,"r");//muestra la lista de ejercicios
		while (fgets(linea, sizeof(linea), sArchi) != NULL)
		{
			line++;
			const char* val1 = strtok(linea, delimitacion);
			const char* val2 = strtok(NULL, delimitacion);
			printf("%d.-Ejercicio: %s, Calorias: %s\n",line,val1,val2);
		}
		fflush(stdin);
		fclose(sArchi);//los seleccionas
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
		srand(time(NULL));//genera una perdida de peso aleatoria(las calorias que gastan al dia estan pensadas para que se pierda ese rango de peso)
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
				removerEspaciosblanco(pass);
			}
			val1=strtok(NULL, delimitacion);
		}
		Confirm=0;
		cont=0;
		}//se modifica el sexo
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
		removerEspaciosblanco(newline1);
		cont=0;
		fclose(sArchi);
		sArchi=fopen(Direccion2,"r");
		FILE * temp = fopen("temp.txt","w");//se crea un archivo temporal donde estara el nuevo peso y se renombrara como datos.db
		while ((fgets(linea, sizeof(linea), sArchi)) != NULL)
		{
			cont++;
			if (cont == posicion+1){//usuario correcto en el if afirmativo de abajo
				if(cont==numusers){
				fputs(newline, temp);
				fprintf(temp,"%g",peso);
				fputs(newline1, temp);
				}else{//si no es el usuario correcto
					fputs(newline, temp);
					fprintf(temp,"%g",peso);
					fputs(newline1, temp);
					fputs("\n",temp);
				}
				}
			else
				fputs(linea, temp);
		}
		fclose(sArchi);
		fclose(temp);
		remove(Direccion2);//se borra el anterior datos.db
		rename("temp.txt",Direccion2);//se renombra el temporal
	}
		
	void generadoReporte(char Archtxt[250],int posicion){
		int line=0,i=0,days,weeks=1;
		double cal=0;
		char linea[250],p[250];
		system("CLS");
		printf("Ejercicios a realizar: \n\n");//muestra los ejercicios a hacer
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
					strcpy(p,calr);
					cal=atof(p);//suma las 3 calorias de los 3 ejercicios por dia
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
		if(dias[posicion]==1){//si es su primera vez se crea el archivo de texto
			sArchi=fopen(destino,"w");//archivo de texto personalizado para el usuario
			fputs("\t|\tDia 1\t|\tDia 2\t|\tDia 3\t|\tDia 4\t|\tDia 5\t|\tDia 6\t|\tDia 7\nweek 1",sArchi);
			fprintf(sArchi,"\t|\t%g",calHechas);
			fputs("cal",sArchi);
			fclose(sArchi);
		}else{//aqui va reescribiendo si no es la primera vez
			days=dias[posicion];
			if(days%7==0){
				sArchi=fopen(destino,"a");
				fprintf(sArchi,"\t|\t%g",calHechas);
				fputs("cal\nweek",sArchi);
				weeks=(days/7)+weeks;
				fprintf(sArchi," %d",weeks);
				fclose(sArchi);
			}else{
				sArchi=fopen(destino,"a");
				fprintf(sArchi,"\t|\t%g",calHechas);
				fputs("cal",sArchi);
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
	for(i=0;i<numusers;i++){//reescribe las calorias hechas por todos los usuarios mientras el programa este ABIERTO
		fprintf(sArchi,"\n| Usuario: %s Calorias totales: %g\n",nombres[i],totalCal[i]);
		//quite contador
	}
	fclose(sArchi);
	sArchi=fopen(destino,"r");//archivo de texto de todos los usuarios
	c=fgetc(sArchi);
	printf("______________________________________________________________\n");
	printf("______________________________________________________________\n");
	while (c != EOF)//lee el archivo de texto
	{
		printf ("%c", c);
		c = fgetc(sArchi);
	}
	printf("______________________________________________________________\n");
	printf("______________________________________________________________\n");
	fclose(sArchi);
	}

	
