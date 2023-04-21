

#define _CRT_SECURE_NO_WARNINGS
#define MAX_IPS 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <windows.h>

#define BUFFER_SIZE 1024




void ping_ips();
void mostrar_configuracion_red();
void comparar_servidores_dns();

int main() {
    int opcion;
    SetConsoleCP(1252); // Cambiar STDIN - Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows
    // Menú principal
    do {
        system("cls");  // Limpiar la pantalla
        printf("MENU\n");
        printf("1. Comprobar ips con ping\n");
        printf("2. Mostrar configuracion de red\n");
        printf("3. Comparar servidores DNS\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            ping_ips();
            break;
        case 2:
            mostrar_configuracion_red();
            break;
        case 3:
            comparar_servidores_dns();
            break;
        case 0:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

        system("pause");  // Pausar la ejecución para que el usuario pueda leer el resultado
    } while (opcion != 0);

    return 0;
}
 

// Función que lee un archivo de texto con una lista de direcciones IP y lanza un ping para cada una de ellas ya fucniona!
void ping_ips() {
    char nombre_archivo[100];
   //la ruta que me funciona???:     C:/Users/Andrew/Desktop/DAM/PcomandosP/DNSips2.txt
    FILE* archivo;
    printf("Introduzca el nombre y la ubicación del archivo: ");
    scanf("%s", nombre_archivo);
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    char linea[100];
    char* ip_list[MAX_IPS];
    int i = 0;

    while (fscanf(archivo, "%s", linea) != EOF && i < MAX_IPS) {
        ip_list[i] = _strdup(linea);
        i++;
    }

    char comando[100];
    int status;

    for (int j = 0; j < i; j++) {
        sprintf(comando, "ping %s", ip_list[j]);
        status = system(comando);

        if (status != 0) {
            printf("No se pudo hacer ping a %s\n", ip_list[j]);
        }
    }

    fclose(archivo);
}
//SEGUNDA FUCNCION BUSCAR SIMPLIFICARLO LO MAS POSIBLE TIO XD SIN COSAS NI LIBRERIAS RARAS
void mostrar_configuracion_red() {
   
    //--->>>   Broadcom BCM43142 802.11 bgn Wi-Fi M.2 Adapter  <--Este es mi adaptador wifi

char command[BUFFER_SIZE];
char buffer[BUFFER_SIZE];
char* mac_address;
char mac[18];
char* subnet_mask_address;
char subnet_mask[17];
char* gateway_address;
char gateway[16];
char* dns_address;
char dns1[16], dns2[16];
char* ip_address;
char ip[16];

printf("Introduzca el nombre del adaptador de red: ");
char adaptador[100];
scanf("%s", adaptador);

sprintf(command, "ipconfig /all");

FILE* fp = _popen(command, "r");
if (fp == NULL) {
    printf("Failed to execute command\n");
    return 1;
}
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {

        mac_address = strstr(buffer, "Dirección física");
    
        if (mac_address != NULL) {
        mac_address += 43;  // saltar "Dirección física . . . . . . . . . . . . : "
        strncpy(mac, mac_address, 17);
        mac[17] = '\0';  // agregar null terminator
        printf("MAC address: %s\n", mac);
        }

        subnet_mask_address = strstr(buffer, "Máscara de subred");
    
        if (subnet_mask_address != NULL) { 
        subnet_mask_address += 39;  // saltar "Máscara de subred . . . . . . . . . . . . : "
        strncpy(subnet_mask, subnet_mask_address, 16);
        subnet_mask[16] = '\0';  // agregar null terminator
        printf("Subnet mask: %s\n", subnet_mask);
        }

        gateway_address = strstr(buffer, "Puerta de enlace predeterminada");
        if (gateway_address != NULL) {
        gateway_address += 41;  // saltar "Puerta de enlace predeterminada . . . . . : "
        strncpy(gateway, gateway_address, 15);
        gateway[15] = '\0';  // agregar null terminator
        printf("Default gateway: %s\n", gateway);
        }

        dns_address = strstr(buffer, "Servidores DNS");
        if (dns_address != NULL) {
        dns_address += 38;  // saltar "Servidores DNS. . . . . . . . . . . . . . : "
        strncpy(dns1, dns_address, 15);
        dns1[15] = '\0';  // agregar null terminator
        dns_address = strstr(dns_address, ":") + 2; // mover al siguiente servidor DNS
        strncpy(dns2, dns_address, 15);
        dns2[15] = '\0';  // agregar null terminator
        printf("DNS servers: %s, %s\n", dns1, dns2);
        }

        ip_address = strstr(buffer, "Dirección IPv4");
    
        if (ip_address != NULL) {
        ip_address += 41;  // saltar "Dirección IPv4. . . . . . . . . . . . . . : "
        strncpy(ip, ip_address, 15);
        ip[15] = '\0';  // agregar null terminator
        printf("IPv4 Direccion: %s\n", ip);
        }
    }
   
    _pclose(fp);

}

void comparar_servidores_dns() {
   printf("Funcion de comparar dns...\n");

}

