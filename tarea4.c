// ------------------------------------------------------------------------------
// DATOS Y ENCABEZADO
//-------------------------------------------------------------------------------
    
// Archivo:                 tarea4.c
// Dispositivo:             PIC16F877A
// Autor:                   GUSTABO CÓRDOVA 
// Programa:                Contador
// Creado:                  10 MAY, 2023 
// Última modificación:     10 MAY, 2023

// ------------------------------------------------------------------------------
// CONFIGURACIÓN DEL PIC
//-------------------------------------------------------------------------------

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// ------------------------------------------------------------------------------
// CONSTANTES
//-------------------------------------------------------------------------------
#define _XTAL_FREQ 4000000

// ------------------------------------------------------------------------------
// LIBRERÍAS
//-------------------------------------------------------------------------------
#include <xc.h>

// ------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------
int ar=0;                                                                   // Se declara e inicializa la variable "ar" como entero y se le asigna el valor de cero.
int ce=0,de=0,un=0, A=0;                                                    // Se declaran e inicializan las variables "ce", "de", "un" y "A" como enteros 
                                                                            // y se les asigna el valor de cero.
int Display[10]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X98};        // Se declara e inicializa el arreglo "Display" como un arreglo de enteros con 10 elementos, 
                                                                            // cada uno de ellos con un valor hexadecimal específico.


// ------------------------------------------------------------------------------
// PROTOTIPO DE FUNCIONES
//-------------------------------------------------------------------------------
void visualizacion(void);
void incremento(void);

// ------------------------------------------------------------------------------
// CICLO PRINCIPAL
//-------------------------------------------------------------------------------
void main(void) {
    TRISC = 0X00;               // Se configura el puerto C como salida.
    TRISB = 0X00;               // Se configura el puerto B como salida.
    TRISD = 1;                  // Se configura el puerto D0 como entrada.

    while(1){
        if(PORTDbits.RD0==1){   // Si se detecta un flanco de subida en el puerto D0, se activa la variable "ar".
            ar=1;
        }
        if(PORTDbits.RD0==0 && ar==1){   // Si se detecta un flanco de bajada en el puerto D0, y la variable "ar" está activada, se incrementa el valor de las unidades.
            un=un+1;
            ar=0;               // Se desactiva la variable "ar".
        }
        visualizacion();        // Se llama a la función "visualizacion()" para mostrar en el display los valores almacenados.
        incremento();           // Se llama a la función "incremento()" para incrementar los valores de las variables "un", "de" y "ce".
    }
}

// ------------------------------------------------------------------------------
// FUNCIONES
//-------------------------------------------------------------------------------
void visualizacion(void){
    PORTC = 0X01;           // Se asigna el valor 0x01 al puerto C, para seleccionar el primer dígito en el display.
    PORTB = Display[un];    // Se asigna al puerto B el valor correspondiente al dígito de las unidades.
    __delay_us (500);       // Se realiza una pausa de 500 microsegundos para la visualización del dígito.

    PORTC = 0X02;           // Se asigna el valor 0x02 al puerto C, para seleccionar el segundo dígito en el display.
    PORTB = Display[de];    // Se asigna al puerto B el valor correspondiente al dígito de las decenas.
    __delay_us (500);       // Se realiza una pausa de 500 microsegundos para la visualización del dígito.

    PORTC = 0X04;           // Se asigna el valor 0x04 al puerto C, para seleccionar el tercer dígito en el display.
    PORTB = Display[ce];    // Se asigna al puerto B el valor correspondiente al dígito de las centenas.
    __delay_us (500);       // Se realiza una pausa de 500 microsegundos para la visualización del dígito.
}


void incremento(void){
    if(un>=10){             // Si el valor de las unidades es mayor o igual a 10, se reinicia a 0 y se incrementa el valor de las decenas.
        un=0;
        de=de+1;
    }
    if(de>=10){             // Si el valor de las decenas es mayor o igual a 10, se reinicia a 0 y se incrementa el valor de las centenas.
        de=0;
        ce=ce+1;
    }
    if(ce>=10){             // Si el valor de las centenas es mayor o igual a 10, se reinicia a 0.
        ce=0;
    }
}
