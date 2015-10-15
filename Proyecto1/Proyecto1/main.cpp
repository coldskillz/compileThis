//
//  main.cpp
//  Proyecto1
//
//  Created by Christian de J Moreno Marín on 13/10/15.
//  Copyright © 2015 Christian de J Moreno Marín. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;


//Funciones

int main_m();
int main_casos();
int ensamblador();
int comp(char *b);
int validal(char *b);
int validacom(char *b);
int comptemp(char *b);
int mystrcmp(const char *s1, const char *s2);
int valida_res(char *b);
int generatokens(char *b);
int valida_inm(char *b);
int valida_inmhex(char *b);
int valida_inmoct(char *b);
int agrega_etiq(char *b);
int accion_mnemonico(int c, char *ntoken);
int accion_inmediato(int a, char *b);
int valida_hexa(char *b);
int valida_octa(char *b);
int IsAllHex (char* must_be_hex);
int valida_indexx(char *b);
int valida_indexy(char *b);
int accion_dirext(int a, int d, char *b);
int enc_etiq(char *b );
int valida_dirext(char *b);
int rutina_rel(char *ntoken);
int rutina_inh(int a,char *ntoken);
int rutina_i_d_xy_ext(char *ntoken);
int rutina_xy_ext(char *ntoken);
int rutina_d_xy(char *ntoken);
int rutina_d_xy_ext(char *ntoken);
int rutina_equ_etiq(char *ntoken);
int agrega_etiq_equ(char *b,char *c);
int enc_etiq2(char *b );
int rutina_org(char *ntoken);



//Variables
FILE *fp1;
FILE *fp2;
char buffer[50];
char *token;
char linea[200];
char palabra[80];
char token1[80];
char token2[80];
char token3[80];
char opera[80];
char etiquetas[100][50];
char valetiq[100][50];
char etiquetasequ[100][50];
char valetiqequ[100][50];
char separador[] = " \t";
char separador2[] = "";
int mem=0xff23;
long int ato;
int k,k2,pos=0,posetiq=0;
char *c;
int s;
string operas;
string token3s;
string temps;
char temp[80];

int inm=0x0;
int dir=0x0;
int indx=0x0;
int indy=0x0;
int ext=0x0;
int rel=0x0;
int inh=0x0;





int main(){
    
    system("cls");
    printf("\nCOMPILADOR BASICO MC68HC11\n");
    printf("\nProfesor: M.I. Pedro Ignacio Rincon Gomez\n");
    printf("\nGrupo: 6\n");
    printf("\nSemestre 2011-2\n");
    printf("\nAlumno:\n");
    printf("\nGonzalez Gonzalez Ricardo\n");
    printf("\nVilla Becerril Cesar Enrique\n");
    getche();
    main_m();
    return 0;
    
}


int ensamblador(){
    
    char archivoe[40];
    
    
    //Menu
    
    printf("Escribe el nombre del archivo donde se encuentra el codigo fuente:");
    scanf("%s",archivoe);
    
    if (archivoe == NULL)
    {
        printf("El archivo no existe \n");
        exit (EXIT_FAILURE);
    }
    else
        
    {
        
        fp1 = fopen(archivoe, "r");
        fp2 = fopen("codigobjeto.txt", "w");
        
        
        //area de pruebas
        
        //printf("%s",reservada[0]);
        //_getche();
        
        //termina area de pruebas
        
        
        do
        {
            /* Obtiene una linea del archivo */
            c = fgets(linea, 200, fp1);
            
            if (validal(linea)==1){
                printf("Error:etiqueta no valida\n");
                fprintf(fp2,"Error:etiqueta no valida\n");
            }
            else{
                
                if (validacom(linea)==0){}
                
                else{
                    printf("\nlinea%s\n", linea); /* la despliega en pantalla */
                    _getche();
                    generatokens(linea);
                    //valida_index(token2);
                    //_getche();
                    k=valida_res(token1);
                    //printf("estado:%i",k);
                    
                    if(k==200){
                        
                        //printf("estado2:%s",token2);
                        //s = fprintf(fp2,token2);
                        //fclose(fp2);
                        if(strncmp(token2,"VACIO",5)==0){
                            agrega_etiq(token1);
                            //printf("\nETIQUETA1:%s",etiquetas[pos-1]);
                            //printf("\nLOCALIDAD:%s",valetiq[pos-1]);
                            //printf("\nPOSICION:%i",pos);
                            mem=mem+0x1;
                            //_getche();
                        }
                        else{
                            k2=valida_res(token2);
                            if(k2==200){
                                printf("Error: se esperaba DIRECTIVA\n");
                                fprintf(fp2,"Error:se esperaba DIRECTIVA\n");
                            }
                            else{
                                accion_mnemonico(k2,token3);
                                agrega_etiq(token1);
                                mem=mem+0x1;
                            }
                            
                        }
                    }
                    
                    else{
                        
                        if(k==154){
                            fprintf(fp2,"\n*Fin del codigo fuente");
                            fclose(fp1);
                            fclose(fp2);
                            printf("Fin del codigo fuente");
                            _getch();
                            main_m();
                        }
                        
                        else{
                            accion_mnemonico(k2,token2);
                            mem=mem+0x1;
                        }
                        
                        
                    }
                    
                    
                }
            }
            //_getch();
            //k=comp(palabra);
            //printf("%i",k);
            //printf("%s",reservada[k]);
            //_getch();
            
            
            
        }while (c != NULL || c=="END");            /* Se repite hasta encontrar EOF */
        
    }
    
    fclose(fp1);
    fclose(fp2);
    _getch();
    
    return 0;
    
}





int comptemp(char *b){
    int a;
    a=strncmp(strupr(b),token,10);
    return(a);
}

int comp(char *b)
{
    int a,r=0;
    do{
        a=strncmp(strupr(b),"LD4D",4);
        r++;
    }while((a!=0));
    //while((r<=5) && (a!=0));
    return(a);
}

int validal(char *b){
    
    int valido=0;
    if (isdigit(b[0])){
        valido=1;
    }
    else{
        valido=0;
    }
    return(valido);
}

int validastrinhexa(char *b){
    
    int valido=0;
    if (isxdigit(b[0])){
        //printf("error: Etiqueta no valida");
        valido=1;
    }
    else{
        valido=0;
    }
    return(valido);
}


int IsAllHex (char* must_be_hex)
{
    //char copy_of_param [64];
    
    //return (
    //strtok (
    //strcpy (copy_of_param, must_be_hex),
    //"ABCDEFabcdef0123456789") == NULL);
    int valido;
    char *a;
    char c[50];
    
    a = strpbrk (must_be_hex,"GHIJKLMN—OPQRSTUVWXYZghijklmnÒopqrstuvwxyz!&/()=?°ø");
   	if(a!=NULL){
        valido=1;}
    else{
        //strcpy(c,a);
        valido=0;
    }
    return (valido);
}





int validacom(char *b){
    int a;
    a=strncmp(strupr(b),"*",1);
    return(a);
}



int mystrcmp(const char *s1, const char *s2)
{
    int i = 0;
    do {
        if(s1[i] != s2[i])
            return 5;
    } while(s1[i++] != '\0');
    return 0;
}

int generatokens(char *b){
    
    token = strtok(b,separador);
    strcpy(token1,token);
    printf( "Token:%s \n", token1);
    token = strtok( NULL, separador);
    if(token != NULL){
        strcpy(token2,token);
        printf( "Token2:%s \n", token2);
        token = strtok( NULL, separador);
    }
    else{
        strcpy(token2,"VACIO");
    }
    if(token != NULL){
        strcpy(token3,token);
        printf( "Token3:%s \n", token3);
    }
    else{
        strcpy(token3,"VACIO");
    }
}

int valida_inm(char *b){
    int a;
    a=strncmp(strupr(b),"#",1);
    return(a);
}

int valida_hexa(char *b){
    int a;
    a=strncmp(strupr(b),"$",1);
    return(a);
}

int valida_octa(char *b){
    int a;
    a=strncmp(strupr(b),"%",1);
    return(a);
}

int valida_inmhex(char *b){
    int a;
    a=strncmp(strupr(b),"#$",2);
    return(a);
}

int valida_inmoct(char *b){
    int a;
    a=strncmp(strupr(b),"#%",2);
    return(a);
}

int valida_indexx(char *b){
    int valido;
    char *a;
    char c[50];
    
    a = strpbrk (b,"X");
   	if(a!=NULL){
        strcpy(c,a);
        valido=0;}
    else{
        valido=1;
    }
    return (valido);
}

int valida_indexy(char *b){
    int valido;
    char *a;
    char c[50];
    
    a = strpbrk (b,"Y");
   	if(a!=NULL){
        strcpy(c,a);
        valido=0;}
    else{
        valido=1;
    }
    return (valido);
}



int agrega_etiq(char *b){
    
    strcpy(etiquetas[pos],b);
    sprintf(valetiq[pos],"%s%X","$",mem);
    pos++;
}


int agrega_etiq_equ(char *b,char *c){
    
    sprintf(etiquetas[pos],"%s",b);
    sprintf(valetiq[pos],"%s",c);
    sprintf(etiquetasequ[pos],"%s%s",b,"\n");
    pos++;
}



int valida_res(char *b){
    int a=200;
    if (strncmp(strupr(b),"ABA\n",10)==0 || strncmp(strupr(b),"ABA",10)==0){
        a=1;  }
    if (strncmp(strupr(b),"ABX\n",10)==0 || strncmp(strupr(b),"ABX",10)==0){
        a=2;  }
    if (strncmp(strupr(b),"ABY\n",10)==0 || strncmp(strupr(b),"ABY",10)==0){
        a=3;  }
    if (strncmp(strupr(b),"ADCA",10)==0){
        a=4;  }
    if (strncmp(strupr(b),"ADCB",10)==0){
        a=5;  }
    if (strncmp(strupr(b),"ADDA",10)==0){
        a=6;  }
    if (strncmp(strupr(b),"ADDB",10)==0){
        a=7;  }
    if (strncmp(strupr(b),"ADDD",10)==0){
        a=8;  }
    if (strncmp(strupr(b),"ANDA",10)==0){
        a=9;}
    if (strncmp(strupr(b),"ANDB",10)==0){
        a=10;}
    if (strncmp(strupr(b),"ASL",10)==0){
        a=11;}
    if (strncmp(strupr(b),"ASLA\n",10)==0 || strncmp(strupr(b),"ASLA",10)==0){
        a=12;}
    if (strncmp(strupr(b),"ASLB\n",10)==0 || strncmp(strupr(b),"ASLB",10)==0){
        a=13;}
    if (strncmp(strupr(b),"ASLD\n",10)==0 || strncmp(strupr(b),"ASLD",10)==0){
        a=14;}
    if (strncmp(strupr(b),"ASR",10)==0){
        a=15;}
    if (strncmp(strupr(b),"ASRA\n",10)==0 || strncmp(strupr(b),"ASRA",10)==0){
        a=16;}
    if (strncmp(strupr(b),"ASRB\n",10)==0 || strncmp(strupr(b),"ASRB\n",10)==0){
        a=17;}
    if (strncmp(strupr(b),"BBC",10)==0){
        a=18;}
    if (strncmp(strupr(b),"BCLR",10)==0){
        a=19;}
    if (strncmp(strupr(b),"BCS",10)==0){
        a=20;}
    if (strncmp(strupr(b),"BEQ",10)==0){
        a=21;}
    if (strncmp(strupr(b),"BGE",10)==0){
        a=22;}
    if (strncmp(strupr(b),"BGT",10)==0){
        a=23;}
    if (strncmp(strupr(b),"BHL",10)==0){
        a=24;}
    if (strncmp(strupr(b),"BHS",10)==0){
        a=25;}
    if (strncmp(strupr(b),"BITA",10)==0){
        a=26;}
    if (strncmp(strupr(b),"BITB",10)==0){
        a=27;}
    if (strncmp(strupr(b),"BLE",10)==0){
        a=28;}
    if (strncmp(strupr(b),"BLO",10)==0){
        a=29;}
    if (strncmp(strupr(b),"BLS",10)==0){
        a=30;}
    if (strncmp(strupr(b),"BIT",10)==0){
        a=31;}
    if (strncmp(strupr(b),"BMI",10)==0){
        a=32;}
    if (strncmp(strupr(b),"BNE",10)==0){
        a=33;}
    if (strncmp(strupr(b),"BPI",10)==0){
        a=34;}
    if (strncmp(strupr(b),"BRA",10)==0){
        a=35;}
    if (strncmp(strupr(b),"BRCLR",10)==0){
        a=36;}
    if (strncmp(strupr(b),"BRN",10)==0){
        a=37;}
    if (strncmp(strupr(b),"BRSET",10)==0){
        a=38;}
    if (strncmp(strupr(b),"BSET",10)==0){
        a=39;}
    if (strncmp(strupr(b),"BSR",10)==0){
        a=40;}
    if (strncmp(strupr(b),"BVC",10)==0){
        a=41;}
    if (strncmp(strupr(b),"BVS",10)==0){
        a=42;}
    if (strncmp(strupr(b),"CBA\n",10)==0 || strncmp(strupr(b),"CBA",10)==0){
        a=43;}
    if (strncmp(strupr(b),"CLC\n",10)==0 || strncmp(strupr(b),"CLC",10)==0){
        a=44;}
    if (strncmp(strupr(b),"CLI\n",10)==0 || strncmp(strupr(b),"CLI",10)==0){
        a=45;}
    if (strncmp(strupr(b),"CLR",10)==0){
        a=46;}
    if (strncmp(strupr(b),"CLRA\n",10)==0 || strncmp(strupr(b),"CLRA",10)==0){
        a=47;}
    if (strncmp(strupr(b),"CLRB\n",10)==0 || strncmp(strupr(b),"CLRB",10)==0){
        a=48;}
    if (strncmp(strupr(b),"CLV\n",10)==0 || strncmp(strupr(b),"CLV",10)==0){
        a=49;}
    if (strncmp(strupr(b),"CMPA",10)==0){
        a=50;}
    if (strncmp(strupr(b),"CMPB",10)==0){
        a=51;}
    if (strncmp(strupr(b),"COM",10)==0){
        a=52;}
    if (strncmp(strupr(b),"COMA\n",10)==0 || strncmp(strupr(b),"COMA",10)==0){
        a=53;}
    if (strncmp(strupr(b),"COMB\n",10)==0 || strncmp(strupr(b),"COMB",10)==0){
        a=54;}
    if (strncmp(strupr(b),"CPD",10)==0){
        a=55;}
    if (strncmp(strupr(b),"CPX",10)==0){
        a=56;}
    if (strncmp(strupr(b),"CPY",10)==0){
        a=57;}
    if (strncmp(strupr(b),"DAA\n",10)==0 || strncmp(strupr(b),"DAA",10)==0){
        a=58;}
    if (strncmp(strupr(b),"DEC",10)==0){
        a=59;}
    if (strncmp(strupr(b),"DECA\n",10)==0 || strncmp(strupr(b),"DECA",10)==0){
        a=60;}
    if (strncmp(strupr(b),"DECB\n",10)==0 || strncmp(strupr(b),"DECB",10)==0){
        a=61;}
    if (strncmp(strupr(b),"DES\n",10)==0 || strncmp(strupr(b),"DES",10)==0){
        a=62;}
    if (strncmp(strupr(b),"DEX\n",10)==0 || strncmp(strupr(b),"DEX",10)==0){
        a=63;}
    if (strncmp(strupr(b),"DEY\n",10)==0 || strncmp(strupr(b),"DEY",10)==0){
        a=64;}
    if (strncmp(strupr(b),"EORA",10)==0){
        a=65;}
    if (strncmp(strupr(b),"EORB",10)==0){
        a=66;}
    if (strncmp(strupr(b),"FDIV\n",10)==0 || strncmp(strupr(b),"FDIV",10)==0){
        a=67;}
    if (strncmp(strupr(b),"LDIV\n",10)==0 || strncmp(strupr(b),"LDIV",10)==0){
        a=68;}
    if (strncmp(strupr(b),"INC",10)==0){
        a=69;}
    if (strncmp(strupr(b),"INCA\n",10)==0 || strncmp(strupr(b),"INCA",10)==0){
        a=70;}
    if (strncmp(strupr(b),"INCB\n",10)==0 || strncmp(strupr(b),"INCB",10)==0){
        a=71;}
    if (strncmp(strupr(b),"INS\n",10)==0 || strncmp(strupr(b),"INS",10)==0){
        a=72;}
    if (strncmp(strupr(b),"INX\n",10)==0 || strncmp(strupr(b),"INX",10)==0){
        a=73;}
    if (strncmp(strupr(b),"INY\n",10)==0 || strncmp(strupr(b),"INY",10)==0){
        a=74;}
    if (strncmp(strupr(b),"JMP",10)==0){
        a=75;}
    if (strncmp(strupr(b),"JSR",10)==0){
        a=76;}
    if (strncmp(strupr(b),"LDAA",10)==0){
        a=77;}
    if (strncmp(strupr(b),"LDAB",10)==0){
        a=78;}
    if (strncmp(strupr(b),"LDD",10)==0){
        a=79;}
    if (strncmp(strupr(b),"LDS",10)==0){
        a=80;}
    if (strncmp(strupr(b),"LDX",10)==0){
        a=81;}
    if (strncmp(strupr(b),"LDY",10)==0){
        a=82;}
    if (strncmp(strupr(b),"LSL",10)==0){
        a=83;}
    if (strncmp(strupr(b),"LSLA\n",10)==0 || strncmp(strupr(b),"LSLA",10)==0){
        a=84;}
    if (strncmp(strupr(b),"LSLB\n",10)==0 || strncmp(strupr(b),"LSLB",10)==0){
        a=85;}
    if (strncmp(strupr(b),"LSID\n",10)==0 || strncmp(strupr(b),"LSID",10)==0){
        a=86;}
    if (strncmp(strupr(b),"LSR",10)==0){
        a=87;}
    if (strncmp(strupr(b),"LSRA\n",10)==0 || strncmp(strupr(b),"LSRA",10)==0){
        a=88;}
    if (strncmp(strupr(b),"LSRB\n",10)==0 || strncmp(strupr(b),"LSRB",10)==0){
        a=89;}
    if (strncmp(strupr(b),"LSRD\n",10)==0 || strncmp(strupr(b),"LSRD",10)==0){
        a=90;}
    if (strncmp(strupr(b),"MUL\n",10)==0 || strncmp(strupr(b),"MUL",10)==0){
        a=91;}
    if (strncmp(strupr(b),"NEG",10)==0){
        a=92;}
    if (strncmp(strupr(b),"NEGA\n",10)==0 || strncmp(strupr(b),"NEGA",10)==0){
        a=93;}
    if (strncmp(strupr(b),"NEGB\n",10)==0 || strncmp(strupr(b),"NEGB",10)==0){
        a=94;}
    if (strncmp(strupr(b),"NOP\n",10)==0 || strncmp(strupr(b),"NOP",10)==0){
        a=95;}
    if (strncmp(strupr(b),"ORAA",10)==0){
        a=96;}
    if (strncmp(strupr(b),"ORAB",10)==0){
        a=97;}
    if (strncmp(strupr(b),"PSHA\n",10)==0 || strncmp(strupr(b),"PSHA",10)==0){
        a=98;}
    if (strncmp(strupr(b),"PSHB\n",10)==0 || strncmp(strupr(b),"PSHB",10)==0){
        a=99;}
    if (strncmp(strupr(b),"PSHX\n",10)==0 || strncmp(strupr(b),"PSHX",10)==0){
        a=100;}
    if (strncmp(strupr(b),"PSHY\n",10)==0 || strncmp(strupr(b),"PSHY",10)==0){
        a=101;}
    if (strncmp(strupr(b),"PULA\n",10)==0 || strncmp(strupr(b),"PULA",10)==0){
        a=102;}
    if (strncmp(strupr(b),"PULB\n",10)==0 || strncmp(strupr(b),"PULB",10)==0){
        a=103;}
    if (strncmp(strupr(b),"PULX\n",10)==0 || strncmp(strupr(b),"PULX",10)==0){
        a=104;}
    if (strncmp(strupr(b),"PULY\n",10)==0 || strncmp(strupr(b),"PULY",10)==0){
        a=105;}
    if (strncmp(strupr(b),"ROL",10)==0){
        a=106;}
    if (strncmp(strupr(b),"ROLA\n",10)==0 || strncmp(strupr(b),"ROLA",10)==0){
        a=107;}
    if (strncmp(strupr(b),"ROLB\n",10)==0 || strncmp(strupr(b),"ROLB",10)==0){
        a=108;}
    if (strncmp(strupr(b),"ROR",10)==0){
        a=109;}
    if (strncmp(strupr(b),"RORA\n",10)==0 || strncmp(strupr(b),"RORA",10)==0){
        a=110;}
    if (strncmp(strupr(b),"RORB\n",10)==0 || strncmp(strupr(b),"RORB",10)==0){
        a=111;}
    if (strncmp(strupr(b),"RTI\n",10)==0 || strncmp(strupr(b),"RTI",10)==0){
        a=112;}
    if (strncmp(strupr(b),"RTS\n",10)==0 || strncmp(strupr(b),"RTS",10)==0){
        a=113;}
    if (strncmp(strupr(b),"SBA\n",10)==0 || strncmp(strupr(b),"SBA",10)==0){
        a=114;}
    if (strncmp(strupr(b),"SBCA",10)==0){
        a=115;}
    if (strncmp(strupr(b),"SBCB",10)==0){
        a=116;}
    if (strncmp(strupr(b),"SEC\n",10)==0 || strncmp(strupr(b),"SEC",10)==0){
        a=117;}
    if (strncmp(strupr(b),"SEI\n",10)==0 || strncmp(strupr(b),"SEI",10)==0){
        a=118;}
    if (strncmp(strupr(b),"SEV\n",10)==0 || strncmp(strupr(b),"SEV",10)==0){
        a=119;}
    if (strncmp(strupr(b),"STAA",10)==0){
        a=120;}
    if (strncmp(strupr(b),"STAB",10)==0){
        a=121;}
    if (strncmp(strupr(b),"STD",10)==0){
        a=122;}
    if (strncmp(strupr(b),"STOP\n",10)==0 || strncmp(strupr(b),"STOP",10)==0){
        a=123;}
    if (strncmp(strupr(b),"STS",10)==0){
        a=124;}
    if (strncmp(strupr(b),"STX",10)==0){
        a=125;}
    if (strncmp(strupr(b),"STY",10)==0){
        a=126;}
    if (strncmp(strupr(b),"SUBA",10)==0){
        a=127;}
    if (strncmp(strupr(b),"SUBB",10)==0){
        a=128;}
    if (strncmp(strupr(b),"SUBD",10)==0){
        a=129;}
    if (strncmp(strupr(b),"SWI\n",10)==0 || strncmp(strupr(b),"SWI",10)==0){
        a=130;}
    if (strncmp(strupr(b),"TAB\n",10)==0 || strncmp(strupr(b),"TAB",10)==0){
        a=131;}
    if (strncmp(strupr(b),"TAP\n",10)==0 || strncmp(strupr(b),"TAP",10)==0){
        a=132;}
    if (strncmp(strupr(b),"TBA\n",10)==0 || strncmp(strupr(b),"TBA",10)==0){
        a=133;}
    if (strncmp(strupr(b),"TETS\n",10)==0 || strncmp(strupr(b),"TETS",10)==0){
        a=134;}
    if (strncmp(strupr(b),"TPA\n",10)==0 || strncmp(strupr(b),"TPA",10)==0){
        a=135;}
    if (strncmp(strupr(b),"TST",10)==0){
        a=136;}
    if (strncmp(strupr(b),"TSTA\n",10)==0 || strncmp(strupr(b),"TSTA",10)==0){
        a=137;}
    if (strncmp(strupr(b),"TSTB\n",10)==0 || strncmp(strupr(b),"TSTB",10)==0){
        a=138;}
    if (strncmp(strupr(b),"TSX\n",10)==0 || strncmp(strupr(b),"TSX",10)==0){
        a=139;}
    if (strncmp(strupr(b),"TSY\n",10)==0 || strncmp(strupr(b),"TSY",10)==0){
        a=140;}
    if (strncmp(strupr(b),"TXS\n",10)==0 || strncmp(strupr(b),"TXS",10)==0){
        a=141;}
    if (strncmp(strupr(b),"TYS\n",10)==0 || strncmp(strupr(b),"TYS",10)==0){
        a=142;}
    if (strncmp(strupr(b),"WAI\n",10)==0 || strncmp(strupr(b),"WAI",10)==0){
        a=143;}
    if (strncmp(strupr(b),"XGDX\n",10)==0 ||strncmp(strupr(b),"XGDX",10)==0){
        a=144;}
    if (strncmp(strupr(b),"XGDY\n",10)==0 || strncmp(strupr(b),"XGDY",10)==0){
        a=145;}
    
    if (strncmp(strupr(b),"EQU",10)==0){
        a=151;}
    if (strncmp(strupr(b),"ORG",10)==0){
        a=152;}
    if (strncmp(strupr(b),"FCB",10)==0){
        a=153;}
    if (strncmp(strupr(b),"END\n",10)==0 || strncmp(strupr(b),"END",10)==0){
        a=154;}
    
    return(a);
}


int accion_inmediato(int a,char *b){
    
    if(valida_inmhex(b)==0 || valida_inmoct(b)==0){
        string token3s = b;
        operas = token3s.substr (2,5);
        strcpy(opera, operas.c_str());
        //printf("\n%s",opera);
        if (IsAllHex(opera)==0 || validal(opera)==1){
            printf("\n%X %X %s\n",mem,a,opera);
            fprintf(fp2,"\n%X %X %s\n",mem,a,opera);
        }
        else{
            printf("\nError: Operando invalido\n");
            fprintf(fp2,"\nError: Operando invalido\n");
        }
    }
    else{
        string token3s = b;
        operas = token3s.substr (1,5);
        strcpy(opera, operas.c_str());
        printf("\n%X %X %X\n",mem,a,atoi(opera));
        fprintf(fp2,"\n%X %X %X\n",mem,a,atoi(opera));
    }
}

int accion_indexado(int a,char *b){
    
    char *tok;
    char temp[80];
    
    if(valida_hexa(b)==0 || valida_octa(b)==0){
        tok = strtok(b,",");
        strcpy(temp,tok);
        string token3s = temp;
        operas = token3s.substr (1,5);
        strcpy(opera, operas.c_str());
        if (IsAllHex(opera)==0 || validal(opera)==1){
            printf("\n%X %X %s\n",mem,a,opera);
            fprintf(fp2,"\n%X %X %s\n",mem,a,opera);
        }
        else{
            printf("\nError: Operando invalido\n");
            fprintf(fp2,"\nError: Operando invalido\n");
        }
    }
    else{
        tok = strtok(b,",");
        strcpy(temp,tok);
        string token3s = temp;
        operas = token3s.substr (0,5);
        strcpy(opera, operas.c_str());
        printf("\n%X %X %X\n",mem,a,atoi(opera));
        fprintf(fp2,"\n%X %X %X\n",mem,a,atoi(opera));
    }
}


int valida_dirext(char *b){
    
    int a=2;
    
    if(valida_hexa(b)==0 || valida_octa(b)==0){
        if(strcspn(b,"\0")<5){
            a=0;
        }
        else{
            a=1;
        }
    }
    else{
        if (validal(b)==1){
            if(atoi(opera)<128){
                a=0;
            }
            else{
                a=1;
            }
            
        }
        else{
        }
    }
    return(a);
    
}


int accion_dirext(int a, int d, char *b){
    
    if(valida_hexa(b)==0 || valida_octa(b)==0){
        if(strcspn(b,"\0")<5){
            string token3s = b;
            
            operas = token3s.substr (1,2);
            strcpy(opera, operas.c_str());
            if (IsAllHex(opera)==0 || validal(opera)==1){
                printf("\n%X %X %s\n",mem,a,opera);
                fprintf(fp2,"\n%X %X %s\n",mem,a,opera);
            }
            else{
                printf("Error:operando invalido\n");
                fprintf(fp2,"Error:operando invalido\n");
            }
        }
        else{
            string token3s = b;
            operas = token3s.substr (1,4);
            strcpy(opera, operas.c_str());
            if (IsAllHex(opera)==0 || validal(opera)==1){
                printf("\n%X %X %s\n",mem,d,opera);
                fprintf(fp2,"\n%X %X %s\n",mem,d,opera);
            }
            else{
                printf("Error:operando invalido\n");
                fprintf(fp2,"Error:operando invalido\n");
            }
            
        }
    }
    else{
        if (validal(b)==1){
            strcpy(opera, b);
            if(atoi(opera)<128){
                printf("\n%X %X %X\n",mem,a,atoi(opera));
                fprintf(fp2,"\n%X %X %X\n",mem,a,atoi(opera));
            }
            else{
                printf("\n%X %X %X\n",mem,d,atoi(opera));
                fprintf(fp2,"\n%X %X %X\n",mem,d,atoi(opera));
            }
            
        }
        else{
            printf("Error:operando invalido\n");
            fprintf(fp2,"Error:operando invalido\n");
        }
        
        
    }
}


int enc_etiq(char *b ){
    
    int i=0;
    
    while((strcmp (b,etiquetas[i])!= 0) && i<101){
        //printf("\nValor etiqueta:%s",etiquetas[i]);
        //printf("\nValor del token:%s",b);
        //_getche();
        i++;
    }
    
    return (i);
    
}

int enc_etiq2(char *b ){
    
    int i=0;
    
    while((strcmp(etiquetasequ[i],b)!= 0) && i<101){
        //printf("\nValor etiqueta:%s",etiquetasequ[i]);
        //printf("\nValor del token:%s",b);
        //_getche();
        i++;
    }
    
    return (i);
    
}




int accion_mnemonico(int c,char *ntoken){
    
    switch(c){
            
        case 1:
            inh=0x1B;
            rutina_inh(inh,ntoken);
            break;
            
        case 2:
            
            inh=0x3A;
            rutina_inh(inh,ntoken);
            break;
            
        case 3:
            inh=0x183A;
            rutina_inh(inh,ntoken);
            
            break;
            
        case 4:
            
            inm=0x89;
            dir=0x99;
            indx=0xA9;
            indy=0x18A9;
            ext=0xB9;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
            
        case 5:
            
            inm=0xc9;
            dir=0xd9;
            indx=0xe9;
            indy=0x18e9;
            ext=0xf9;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 6:
            
            inm=0x8B;
            dir=0x9B;
            indx=0xAB;
            indy=0x18AB;
            ext=0xBB;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 7:
            
            inm=0xcB;
            dir=0xDB;
            indx=0xeB;
            indy=0x18eB;
            ext=0xfB;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 8:
            
            inm=0xc3;
            dir=0xd3;
            indx=0xe3;
            indy=0x18e3;
            ext=0xf3;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 9:
            
            inm=0x84;
            dir=0x94;
            indx=0xB4;
            indy=0x18A4;
            ext=0xB4;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 10:
            
            inm=0xc4;
            dir=0xd4;
            indx=0xe4;
            indy=0x18e4;
            ext=0xf4;
            rutina_i_d_xy_ext(ntoken);
            break;
            
            
        case 11:
            
            indx=0x68;
            indy=0x1868;
            ext=0x78;
            rutina_xy_ext(ntoken);
            break;
            
        case 12:
            
            inh=0x48;
            rutina_inh(inh,ntoken);
            break;
            
        case 13:
            
            inh=0x58;
            rutina_inh(inh,ntoken);
            break;
            
        case 14:
            
            inh=0x5;
            rutina_inh(inh,ntoken);
            break;
            
        case 15:
            
            indx=0x67;
            indy=0x1867;
            ext=0x77;
            rutina_xy_ext(ntoken);
            break;
            
        case 16:
            
            inh=0x47;
            rutina_inh(inh,ntoken);
            break;
            
        case 17:
            
            inh=0x57;
            rutina_inh(inh,ntoken);
            break;
            
        case 18:
            
            rel=0x24;
            rutina_rel(ntoken);
            
            break;
            
        case 19:
            
            dir=0x15;
            indx=0x1d;
            indy=0x181d;
            rutina_d_xy(ntoken);
            
            break;
            
        case 20:
            
            rel=0x25;
            rutina_rel(ntoken);
            
            break;
            
            
        case 21:
            
            rel=0x27;
            rutina_rel(ntoken);
            
            
            break;
            
        case 22:
            
            rel=0x2c;
            rutina_rel(ntoken);
            
            break;
            
        case 23:
            
            rel=0x2e;
            rutina_rel(ntoken);
            
            break;
            
            
        case 24:
            
            rel=0x22;
            rutina_rel(ntoken);
            
            break;
            
        case 25:
            
            rel=0x24;
            rutina_rel(ntoken);
            
            break;
            
        case 26:
            
            inm=0x85;
            dir=0x95;
            indx=0xA5;
            indy=0x18A5;
            ext=0xB5;
            rutina_i_d_xy_ext(ntoken);
            break;
            
            
        case 27:
            
            inm=0xc5;
            dir=0xd5;
            indx=0xe5;
            indy=0x18e5;
            ext=0xf5;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 28:
            
            rel=0x2f;
            rutina_rel(ntoken);
            
            break;
            
            
        case 29:
            
            rel=0x25;
            rutina_rel(ntoken);
            
            break;
            
        case 30:
            
            rel=0x23;
            rutina_rel(ntoken);
            
            break;
            
            
        case 31:
            
            rel=0x2d;
            rutina_rel(ntoken);
            
            break;
            
        case 32:
            
            rel=0x2b;
            rutina_rel(ntoken);
            
            break;
            
        case 33:
            
            rel=0x26;
            rutina_rel(ntoken);
            
            break;
            
        case 34:
            
            rel=0x2a;
            rutina_rel(ntoken);
            
            break;
            
        case 35:
            
            rel=0x20;
            rutina_rel(ntoken);
            
            break;
            
        case 36:
            
            dir=0x13;
            indx=0x1f;
            indy=0x181f;
            rutina_d_xy(ntoken);
            break;
            
        case 37:
            
            rel=0x21;
            rutina_rel(ntoken);
            break;
            
        case 38:
            
            dir=0x12;
            indx=0x1e;
            indy=0x181e;
            rutina_d_xy(ntoken);
            break;
            
        case 39:
            
            dir=0x14;
            indx=0x1c;
            indy=0x181c;
            rutina_d_xy(ntoken);
            break;
            
        case 40:
            
            rel=0x8d;
            rutina_rel(ntoken);
            break;
            
        case 41:
            
            rel=0x28;
            rutina_rel(ntoken);
            break;
            
        case 42:
            
            rel=0x29;
            rutina_rel(ntoken);
            break;
            
        case 43:
            inh=0x11;
            rutina_inh(inh,ntoken);
            break;
            
        case 44:
            inh=0x0c;
            rutina_inh(inh,ntoken);
            break;
            
        case 45:
            inh=0x0e;
            rutina_inh(inh,ntoken);
            break;
            
        case 46:
            
            indx=0x6f;
            indy=0x186f;
            ext=0x7f;
            rutina_xy_ext(ntoken);
            break;
            
        case 47:
            inh=0x4f;
            rutina_inh(inh,ntoken);
            break;
            
        case 48:
            inh=0x5f;
            rutina_inh(inh,ntoken);
            break;
            
        case 49:
            inh=0x0a;
            rutina_inh(inh,ntoken);
            break;
            
        case 50:
            
            inm=0x81;
            dir=0x91;
            indx=0xA1;
            indy=0x18A1;
            ext=0xB1;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 51:
            
            inm=0xc1;
            dir=0xd1;
            indx=0xe1;
            indy=0x18e1;
            ext=0xf1;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 52:
            
            indx=0x63;
            indy=0x1863;
            ext=0x73;
            rutina_xy_ext(ntoken);
            break;
            
        case 53:
            inh=0x43;
            rutina_inh(inh,ntoken);
            break;
            
        case 54:
            inh=0x53;
            rutina_inh(inh,ntoken);
            break;
            
        case 55:
            
            inm=0x1a83;
            dir=0x1a93;
            indx=0x1aa3;
            indy=0xcda3;
            ext=0x1ab3;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 56:
            
            inm=0x8c;
            dir=0x9c;
            indx=0xac;
            indy=0xcdac;
            ext=0xbc;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 57:
            
            inm=0x188c;
            dir=0x189c;
            indx=0x1aac;
            indy=0x18ac;
            ext=0x18bc;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 58:
            inh=0x19;
            rutina_inh(inh,ntoken);
            break;
            
        case 59:
            
            indx=0x6a;
            indy=0x186a;
            ext=0x7a;
            rutina_xy_ext(ntoken);
            break;
            
        case 60:
            inh=0x4a;
            rutina_inh(inh,ntoken);
            break;
            
        case 61:
            inh=0x5a;
            rutina_inh(inh,ntoken);
            break;
            
        case 62:
            inh=0x34;
            rutina_inh(inh,ntoken);
            break;
            
        case 63:
            inh=0x09;
            rutina_inh(inh,ntoken);
            break;
            
        case 64:
            inh=0x1809;
            rutina_inh(inh,ntoken);
            break;
            
        case 65:
            
            inm=0x88;
            dir=0x98;
            indx=0xa8;
            indy=0x18a8;
            ext=0xb8;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 66:
            
            inm=0xc8;
            dir=0xd8;
            indx=0xe8;
            indy=0x18e8;
            ext=0xf8;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 67:
            inh=0x03;
            rutina_inh(inh,ntoken);
            break;
            
        case 68:
            inh=0x02;
            rutina_inh(inh,ntoken);
            break;
            
        case 69:
            
            indx=0x6c;
            indy=0x186c;
            ext=0x7c;
            rutina_xy_ext(ntoken);
            break;
            
        case 70:
            inh=0x4c;
            rutina_inh(inh,ntoken);
            break;
            
        case 71:
            inh=0x5c;
            rutina_inh(inh,ntoken);
            break;
            
        case 72:
            inh=0x31;
            rutina_inh(inh,ntoken);
            break;
            
        case 73:
            inh=0x08;
            rutina_inh(inh,ntoken);
            break;
            
        case 74:
            inh=0x1808;
            rutina_inh(inh,ntoken);
            break;
            
        case 75:
            
            indx=0x6e;
            indy=0x186e;
            ext=0x7e;
            rutina_xy_ext(ntoken);
            break;
            
        case 76:
            
            dir=0x9d;
            indx=0xad;
            indy=0x18ad;
            ext=0xbd;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 77:
            
            inm=0x86;
            dir=0x96;
            indx=0xa6;
            indy=0x18a6;
            ext=0xb6;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 78:
            
            inm=0xc6;
            dir=0xd6;
            indx=0xe6;
            indy=0x18e6;
            ext=0xf6;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 79:
            
            inm=0xcc;
            dir=0xdc;
            indx=0xec;
            indy=0x18ec;
            ext=0xfc;
            rutina_i_d_xy_ext(ntoken);
            
            break;
            
        case 80:
            
            inm=0x8e;
            dir=0x9e;
            indx=0xae;
            indy=0x18ae;
            ext=0xbe;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 81:
            
            inm=0xce;
            dir=0xde;
            indx=0xee;
            indy=0xcdee;
            ext=0xfe;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 82:
            
            inm=0x18ce;
            dir=0x18de;
            indx=0x1aee;
            indy=0x18ee;
            ext=0x18fe;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 83:
            
            indx=0x68;
            indy=0x1868;
            ext=0x78;
            rutina_xy_ext(ntoken);
            break;
            
        case 84:
            
            inh=0x48;
            rutina_inh(inh,ntoken);
            break;
            
        case 85:
            
            inh=0x58;
            rutina_inh(inh,ntoken);
            break;
            
        case 86:
            
            inh=0x05;
            rutina_inh(inh,ntoken);
            break;
            
        case 87:
            
            indx=0x64;
            indy=0x1864;
            ext=0x74;
            rutina_xy_ext(ntoken);
            break;
            
        case 88:
            
            inh=0x44;
            rutina_inh(inh,ntoken);
            break;
            
        case 89:
            
            inh=0x54;
            rutina_inh(inh,ntoken);
            break;
            
        case 90:
            
            inh=0x04;
            rutina_inh(inh,ntoken);
            break;
            
        case 91:
            
            inh=0x3d;
            rutina_inh(inh,ntoken);
            break;
            
        case 92:
            
            indx=0x60;
            indy=0x1860;
            ext=0x70;
            rutina_xy_ext(ntoken);
            break;
            
        case 93:
            
            inh=0x40;
            rutina_inh(inh,ntoken);
            break;
            
        case 94:
            
            inh=0x50;
            rutina_inh(inh,ntoken);
            break;
            
        case 95:
            
            inh=0x01;
            rutina_inh(inh,ntoken);
            break;
            
        case 96:
            
            inm=0x8a;
            dir=0x9a;
            indx=0xaa;
            indy=0x18aa;
            ext=0x18ba;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 97:
            
            inm=0xCA;
            dir=0xDA;
            indx=0xEA;
            indy=0x18EA;
            ext=0x18FA;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 98:
            
            inh=0x36;
            rutina_inh(inh,ntoken);
            break;
            
        case 99:
            
            inh=0x37;
            rutina_inh(inh,ntoken);
            break;
            
        case 100:
            
            inh=0x3C;
            rutina_inh(inh,ntoken);
            break;
            
        case 101:
            
            inh=0x183C;
            rutina_inh(inh,ntoken);
            break;
            
        case 102:
            
            inh=0x32;
            rutina_inh(inh,ntoken);
            break;
            
        case 103:
            
            inh=0x33;
            rutina_inh(inh,ntoken);
            break;
            
        case 104:
            
            inh=0x38;
            rutina_inh(inh,ntoken);
            break;
            
        case 105:
            
            inh=0x1838;
            rutina_inh(inh,ntoken);
            break;
            
        case 106:
            
            indx=0x69;
            indy=0x1869;
            ext=0x79;
            rutina_xy_ext(ntoken);
            break;
            
        case 107:
            
            inh=0x49;
            rutina_inh(inh,ntoken);
            break;
            
        case 108:
            
            inh=0x59;
            rutina_inh(inh,ntoken);
            break;
            
        case 109:
            
            indx=0x66;
            indy=0x1866;
            ext=0x76;
            rutina_xy_ext(ntoken);
            break;
            
        case 110:
            
            inh=0x46;
            rutina_inh(inh,ntoken);
            break;
            
        case 111:
            
            inh=0x56;
            rutina_inh(inh,ntoken);
            break;
            
        case 112:
            
            inh=0x3B;
            rutina_inh(inh,ntoken);
            break;
            
        case 113:
            
            inh=0x39;
            rutina_inh(inh,ntoken);
            break;
            
        case 114:
            
            inh=0x10;
            rutina_inh(inh,ntoken);
            break;
            
        case 115:
            
            inm=0x82;
            dir=0x92;
            indx=0xA2;
            indy=0x18A2;
            ext=0xB2;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 116:
            
            inm=0xC2;
            dir=0xD2;
            indx=0xE2;
            indy=0x18E2;
            ext=0xF2;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 117:
            
            inh=0x0D;
            rutina_inh(inh,ntoken);
            break;
            
        case 118:
            
            inh=0x0F;
            rutina_inh(inh,ntoken);
            break;
            
        case 119:
            
            inh=0x0B;
            rutina_inh(inh,ntoken);
            break;
            
        case 120:
            
            dir=0x97;
            indx=0xA7;
            indy=0x18A7;
            ext=0xB7;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 121:
            
            dir=0xD7;
            indx=0xE7;
            indy=0x18E7;
            ext=0xF7;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 122:
            
            dir=0xDD;
            indx=0xED;
            indy=0x18ED;
            ext=0xFD;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 123:
            
            inh=0xCF;
            rutina_inh(inh,ntoken);
            break;
            
        case 124:
            
            dir=0x9F;
            indx=0xAF;
            indy=0x18AF;
            ext=0xBF;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 125:
            
            dir=0xDF;
            indx=0xEF;
            indy=0xCDEF;
            ext=0xFF;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 126:
            
            dir=0x18DF;
            indx=0x1AEF;
            indy=0x18EF;
            ext=0xFF;
            rutina_d_xy_ext(ntoken);
            break;
            
        case 127:
            
            inm=0x80;
            dir=0x90;
            indx=0xA0;
            indy=0x18A0;
            ext=0xB0;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 128:
            
            inm=0xC0;
            dir=0xD0;
            indx=0xE0;
            indy=0x18E0;
            ext=0xF0;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 129:
            
            inm=0x83;
            dir=0x93;
            indx=0xA3;
            indy=0x18A3;
            ext=0xB3;
            rutina_i_d_xy_ext(ntoken);
            break;
            
        case 130:
            
            inh=0x3F;
            rutina_inh(inh,ntoken);
            break;
            
        case 131:
            
            inh=0x16;
            rutina_inh(inh,ntoken);
            break;
            
        case 132:
            
            inh=0x06;
            rutina_inh(inh,ntoken);
            break;
            
        case 133:
            
            inh=0x17;
            rutina_inh(inh,ntoken);
            break;
            
        case 134:
            
            inh=0x00;
            rutina_inh(inh,ntoken);
            break;
            
        case 135:
            
            inh=0x07;
            rutina_inh(inh,ntoken);
            break;
            
        case 136:
            
            indx=0x6D;
            indy=0x186D;
            ext=0x7D;
            rutina_xy_ext(ntoken);
            break;
            
        case 137:
            
            inh=0x4D;
            rutina_inh(inh,ntoken);
            break;
            
        case 138:
            
            inh=0x5D;
            rutina_inh(inh,ntoken);
            break;
            
        case 139:
            
            inh=0x30;
            rutina_inh(inh,ntoken);
            break;
            
        case 140:
            
            inh=0x1830;
            rutina_inh(inh,ntoken);
            break;
            
        case 141:
            
            inh=0x35;
            rutina_inh(inh,ntoken);
            break;
            
        case 142:
            
            inh=0x1835;
            rutina_inh(inh,ntoken);
            break;
            
        case 143:
            
            inh=0x3E;
            rutina_inh(inh,ntoken);
            break;
            
        case 144:
            
            inh=0x8F;
            rutina_inh(inh,ntoken);
            break;
            
        case 145:
            
            inh=0x188F;
            rutina_inh(inh,ntoken);
            break;
            
        case 151:
            rutina_equ_etiq(ntoken);
            break;
            
        case 152:
            rutina_org(ntoken);
            break;
            
        case 154:
            fprintf(fp2,"\n*Fin del codigo fuente");
            fclose(fp1);
            fclose(fp2);
            printf("Fin del codigo fuente");
            _getch();
            main_m();
            break;
            
    }
    
    
}


int rutina_rel(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");
    }
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");
        }
        else{
            if(valida_indexx(ntoken)==0){
                printf("Error:No se acepta direccionamiento indexado\n");
                fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");
            }
            else{
                if(valida_indexy(ntoken)==0){
                    printf("Error:No se acepta direccionamiento indexado\n");
                    fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");
                }
                else{
                    if(valida_dirext(ntoken)==0){
                        accion_dirext(rel,ext,ntoken);
                    }
                    else{
                        printf("Error:Modo de direccionamiento no valido\n");
                        fprintf(fp2,"Error:Modo de direccionamiento no valido\n");
                    }
                    
                }
            }
        }
    }
    
    
}

int rutina_inh(int a,char *ntoken){
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("%X %X\n",mem,a);
        fprintf(fp2,"%X %X\n",mem,a);
        
    }
    else{
        printf("Error:Direccionamiento inherente, no debe tener operador\n");
        fprintf(fp2,"Error:Direccionamiento inherente, no debe tener operador\n");
    }
    
    
}

int rutina_i_d_xy_ext(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");
    }
    else{
        
        if(valida_inm(ntoken)==0){
            accion_inmediato(inm,ntoken);
        }
        else{
            if(valida_indexx(ntoken)==0){
                accion_indexado(indx,ntoken);
            }
            else{
                if(valida_indexy(ntoken)==0){
                    accion_indexado(indy,ntoken);
                }
                else{
                    accion_dirext(dir,ext,ntoken);
                    
                }
            }
        }
    }
    
}

int rutina_xy_ext(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");
        
    }
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");
        }
        else{
            if(valida_indexx(ntoken)==0){
                accion_indexado(indx,ntoken);
            }
            else{
                if(valida_indexy(ntoken)==0){
                    accion_indexado(indy,ntoken);
                }
                else{
                    if(valida_dirext(ntoken)==1){
                        accion_dirext(dir,ext,ntoken);
                    }
                    else{
                        printf("Error:Modo de direccionamiento no valido\n");
                        fprintf(fp2,"Error:Modo de direccionamiento no valido\n");
                    }
                    
                }
            }
        }
    }
    
    
    
}

int rutina_d_xy(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");
    }
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");
        }
        else{
            if(valida_indexx(ntoken)==0){
                accion_indexado(indx,ntoken);
            }
            else{
                if(valida_indexy(ntoken)==0){
                    accion_indexado(indy,ntoken);
                }
                else{
                    if(valida_dirext(ntoken)==0){
                        accion_dirext(dir,ext,ntoken);
                    }
                    else{
                        printf("Error:Modo de direccionamiento no valido\n");
                        fprintf(fp2,"Error:Modo de direccionamiento no valido\n");
                    }
                    
                }
            }
        }
    }
    
    
    
}

int rutina_d_xy_ext(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");    
    }          
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");         
        }
        else{
            if(valida_indexx(ntoken)==0){
                accion_indexado(indx,ntoken);                     
            }
            else{
                if(valida_indexy(ntoken)==0){
                    accion_indexado(indy,ntoken);                     
                }
                else{
                    accion_dirext(dir,ext,ntoken);                                                   
                    
                }
            }
        }
    }    
    
}

int rutina_equ_etiq(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");    
    }          
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");         
        }
        else{
            if(valida_indexx(ntoken)==0){
                printf("Error:No se acepta direccionamiento indexado\n");
                fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");                                   
            }
            else{
                if(valida_indexy(ntoken)==0){
                    printf("Error:No se acepta direccionamiento indexado\n");
                    fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");                                           
                }
                else{
                    
                    if (IsAllHex(ntoken)==0 || validal(ntoken)==1 || valida_hexa(ntoken)==0 || valida_octa(ntoken)==0){
                        agrega_etiq_equ(token1,ntoken);
                    }
                    else{
                        printf("Error:operando invalido\n");
                        fprintf(fp2,"Error:operando invalido\n");                           
                    }
                    
                    
                }
            }
        }
    }    
    
    
}

int rutina_org(char *ntoken){
    
    if(enc_etiq(ntoken)<101){
        posetiq=enc_etiq(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    if(enc_etiq2(ntoken)<101){
        posetiq=enc_etiq2(ntoken);
        string token3s = valetiq[posetiq];
        strcpy(ntoken, token3s.c_str());
    }
    
    
    else{
    }
    
    if(strncmp(ntoken,"VACIO",5)==0 || validacom(ntoken)==0){
        printf("Error:Se esperaba operando\n");
        fprintf(fp2,"Error:Se esperaba operando\n");    
    }          
    else{
        
        if(valida_inm(ntoken)==0){
            printf("Error:No se acepta direccionamiento inmediato\n");
            fprintf(fp2,"Error:No se acepta direccionamiento inmediato\n");         
        }
        else{
            if(valida_indexx(ntoken)==0){
                printf("Error:No se acepta direccionamiento indexado\n");
                fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");                                   
            }
            else{
                if(valida_indexy(ntoken)==0){
                    printf("Error:No se acepta direccionamiento indexado\n");
                    fprintf(fp2,"Error:No se acepta direccionamiento indexado\n");                                           
                }
                else{
                    
                    //if (IsAllHex(ntoken)==0 || validal(ntoken)==1 || valida_hexa(ntoken)==0 || valida_octa(ntoken)==0){
                    
                    if(valida_hexa(ntoken)==0 || valida_octa(ntoken)==0){
                        if(strcspn(ntoken,"\0")<5){
                            string token3s = ntoken;
                            operas = token3s.substr (1,2);
                            strcpy(opera, operas.c_str());
                            if (IsAllHex(opera)==0 || validal(opera)==1){
                                ato=strtoul (opera,NULL,16);
                                mem=ato;
                                //printf("\nMEMORIA:%X",mem);                                   
                            }
                            else{
                                printf("Error:operando invalido\n");
                                fprintf(fp2,"Error:operando invalido\n");                                   
                            }
                        }
                        else{
                            string token3s = ntoken;
                            operas = token3s.substr (1,5);
                            strcpy(opera, operas.c_str());
                            if (IsAllHex(opera)==0 || validal(opera)==1){
                                ato=strtoul (opera,NULL,16);
                                mem=ato;
                                //printf("\nMEMORIA:%X",mem);                                    
                            }
                            else{
                                printf("Error:operando invalido\n");
                                fprintf(fp2,"Error:operando invalido\n");                                   
                            }
                            
                        }
                    }
                    else{
                        if (validal(ntoken)==1){
                            strcpy(opera, ntoken);               
                            if(atoi(opera)<128){
                                ato=strtoul (opera,NULL,16);
                                mem=ato;
                                //printf("\nMEMORIA:%X",mem);                                 
                            }                
                            else{
                                ato=strtoul (opera,NULL,16);
                                mem=ato;
                                //printf("\nMEMORIA:%X",mem);      
                            }
                            
                        } 
                        else{
                            printf("Error:operando invalido\n");
                            fprintf(fp2,"Error:operando invalido\n");                                   
                        } 
                        
                        
                    }
                    
                    
                }
            }
        }
    }    
    
    
}

int main_m(){
    
    system("cls");
    printf("\nCOMPILADOR BASICO MC68HC11\n\n");
    printf("\n\nSELECCIONA UNA OPCION DE LA SIGUIENTE LISTA\n");
    printf("\n 1: Acceso al compilador");
    printf("\n 2: Acerca de");
    printf("\n 3: Salir");    
    main_casos();  
    
}


int main_casos(){
    
    int opcion;
    
    printf("\n\nIntroduzca la opcion deseada: ");
    scanf("%d",&opcion);
    switch (opcion){
            
        case 1:
            ensamblador();             
            break;    
            
        case 2:
            
            system("cls");
            printf("\nACERCA DE: COMPILADOR BASICO MC68HC11\n");
            printf("\nFacultad de Ingenieria, UNAM\n");
            printf("\nDesarrollado por:\n");
            printf("\nGonzalez Gonzalez Ricardo\n");
            printf("\nEmail:textex@prodigy.net.mx,charactex27@gmail.com\n");
            getche();
            main_m();
            break;
            
        case 3:
            printf("\nSaliendo del programa - Gracias\n");
            getche();
            return(1);
            break;
        default:
            printf("Opcion incorrecta\n");
            getche();
            main_m();
            break;
            
    }
}
