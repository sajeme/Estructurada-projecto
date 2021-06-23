#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
char delimitacion[] = "::: ";
int main(int argc, char *argv[]) {
	char sexo[10];
	int edad;
	float peso;
	int line=0,cont=0;
	char linea[250];
	printf("sex: ");
	gets(sexo);
	fflush(stdin);
	printf("edad: ");
	scanf("%d", &edad);
	fflush(stdin);
	printf("peso: ");
	scanf("%f", &peso);
	FILE *sArchi;
	fflush(stdin);
		if(strcmp(sexo,"Hombre")==0){
			if(edad>=18&&edad<49){
				if(peso>=44&&peso<58){
					sArchi=fopen("18 49 anios/Hombre/44 58 kg .txt","r");
				}else{
					if(peso>=58&&peso<66){
						sArchi=fopen("18 49 anios/Hombre/58 66 kg .txt","r");
					}else{
						if(peso>=66&&peso<83){
							sArchi=fopen("18 49 anios/Hombre/66 83 kg .txt","r");
						}else{
							if(peso>=83&&peso<98){
								sArchi=fopen("18 49 anios/Hombre/83 98 kg .txt","r");
							}else{
								if(peso>=98&&peso<116){
									sArchi=fopen("18 49 anios/Hombre/98 116 kg .txt","r");
								}else{
									sArchi=fopen("18 49 anios/Hombre/mayor de 116 kg .txt","r");
								}
							}
						}
					}
				}
			}else{
				if(edad>=49&&edad<60){
					if(peso>=44&&peso<58){
						sArchi=fopen("49 60 anios/Hombre/44 58 kg .txt","r");
					}else{
						if(peso>=58&&peso<66){
							sArchi=fopen("49 60 anios/Hombre/58 66 kg .txt","r");
						}else{
							if(peso>=66&&peso<83){
								sArchi=fopen("49 60 anios/Hombre/66 83 kg .txt","r");
							}else{
								if(peso>=83&&peso<98){
									sArchi=fopen("49 60 anios/Hombre/83 98 kg .txt","r");
								}else{
									if(peso>=98&&peso<116){
										sArchi=fopen("49 60 anios/Hombre/98 116 kg .txt","r");
									}else{
										sArchi=fopen("49 60 anios/Hombre/mayor de 116 kg .txt","r");
									}
								}
							}
						}
					}
				}else{
					if(edad<18){
						if(peso>=44&&peso<58){
							sArchi=fopen("menores 18 anios/Hombre/44 58 kg .txt","r");
						}else{
							if(peso>=58&&peso<66){
								sArchi=fopen("menores 18 anios/Hombre/58 66 kg .txt","r");
							}else{
								if(peso>=66&&peso<83){
									sArchi=fopen("menores 18 anios/Hombre/66 83 kg .txt","r");
								}else{
									if(peso>=83&&peso<98){
										sArchi=fopen("menores 18 anios/Hombre/83 98 kg .txt","r");
									}else{
										if(peso>=98&&peso<116){
											sArchi=fopen("menores 18 anios/Hombre/98 116 kg .txt","r");
										}else{
											sArchi=fopen("menores 18 anios/Hombre/mayor de 116 kg .txt","r");
										}
									}
								}
							}
						}
					}else{
						if(edad>60){
							if(peso>=44&&peso<58){
								sArchi=fopen("mayores 60 anios/44 58 kg .txt","r");
							}else{
								if(peso>=58&&peso<66){
									sArchi=fopen("mayores 60 anios/58 66 kg .txt","r");
								}else{
									if(peso>=66&&peso<83){
										sArchi=fopen("mayores 60 anios/66 83 kg .txt","r");
									}else{
										if(peso>=83&&peso<98){
											sArchi=fopen("mayores 60 anios/83 98 kg .txt","r");
										}else{
											if(peso>=98&&peso<116){
												sArchi=fopen("mayores 60 anios/98 116 kg .txt","r");
											}else{
												sArchi=fopen("mayores 60 anios/mayor de 116 kg .txt","r");
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
					sArchi=fopen("18 49 anios/Mujer/44 58 kg .txt","r");
				}else{
					if(peso>=58&&peso<66){
						sArchi=fopen("18 49 anios/Mujer/58 66 kg .txt","r");
					}else{
						if(peso>=66&&peso<83){
							sArchi=fopen("18 49 anios/Mujer/66 83 kg .txt","r");
						}else{
							if(peso>=83&&peso<98){
								sArchi=fopen("18 49 anios/Mujer/83 98 kg .txt","r");
							}else{
								if(peso>=98&&peso<116){
									sArchi=fopen("18 49 anios/Mujer/98 116 kg .txt","r");
								}else{
									sArchi=fopen("18 49 anios/Mujer/mayor de 116 kg .txt","r");
								}
							}
						}
					}
				}
			}else{
				if(edad>=49&&edad<60){
					if(peso>=44&&peso<58){
						sArchi=fopen("49 60 anios/Mujer/44 58 kg .txt","r");
					}else{
						if(peso>=58&&peso<66){
							sArchi=fopen("49 60 anios/Mujer/58 66 kg .txt","r");
						}else{
							if(peso>=66&&peso<83){
								sArchi=fopen("49 60 anios/Mujer/66 83 kg .txt","r");
							}else{
								if(peso>=83&&peso<98){
									sArchi=fopen("49 60 anios/Mujer/83 98 kg .txt","r");
								}else{
									if(peso>=98&&peso<116){
										sArchi=fopen("49 60 anios/Mujer/98 116 kg .txt","r");
									}else{
										sArchi=fopen("49 60 anios/Mujer/mayor de 116 kg .txt","r");
									}
								}
							}
						}
					}
				}else{
					if(edad<18){
						if(peso>=44&&peso<58){
							sArchi=fopen("menores 18 anios/Mujer/44 58 kg .txt","r");
						}else{
							if(peso>=58&&peso<66){
								sArchi=fopen("menores 18 anios/Mujer/58 66 kg .txt","r");
							}else{
								if(peso>=66&&peso<83){
									sArchi=fopen("menores 18 anios/Mujer/66 83 kg .txt","r");
								}else{
									if(peso>=83&&peso<98){
										sArchi=fopen("menores 18 anios/Mujer/83 98 kg .txt","r");
									}else{
										if(peso>=98&&peso<116){
											sArchi=fopen("menores 18 anios/Mujer/98 116 kg .txt","r");
										}else{
											sArchi=fopen("menores 18 anios/Mujer/mayor de 116 kg .txt","r");
										}
									}
								}
							}
						}
					}else{
						if(edad>60){
							if(peso>=44&&peso<58){
								sArchi=fopen("mayores 60 anios/44 58 kg .txt","r");
							}else{
								if(peso>=58&&peso<66){
									sArchi=fopen("mayores 60 anios/58 66 kg .txt","r");
								}else{
									if(peso>=66&&peso<83){
										sArchi=fopen("mayores 60 anios/66 83 kg .txt","r");
									}else{
										if(peso>=83&&peso<98){
											sArchi=fopen("mayores 60 anios/83 98 kg .txt","r");
										}else{
											if(peso>=98&&peso<116){
												sArchi=fopen("mayores 60 anios/98 116 kg .txt","r");
											}else{
												sArchi=fopen("mayores 60 anios/mayor de 116 kg .txt","r");
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
		while (fgets(linea, sizeof(linea), sArchi) != NULL)
		{//usuario y contraseña se separan en 2 tokens
			//en el arvhicos estan como "Usuario":::"Contraseña" el ::: es el delimitador del token
			line++;
			const char* val1 = strtok(linea, delimitacion);
			const char* val2 = strtok(linea, NULL);
			printf("Ejercicio: %s, Calorias: %s\n",val1,val2);
			cont=0;
		}
		fflush(stdin);		
		
		return 0;
		
		//final ptm
		}


