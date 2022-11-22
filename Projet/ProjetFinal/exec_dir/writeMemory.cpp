// Cours:       INF1900 - Projet initial de syst�me embarqu�
// Auteurs:     THOELEN Nathan
//              OUGADI Mehdi
//              ALLAIRE Mederic
//              WACRENIER Paul
// Date:        03 novembre 2022

#include "memory.h"
#include "LED.h"
#include "usart.h"
#include "CapteurPoteau.h"
int main()
{
    Usart transmit;
    Memory mem;
    Led led;
    CapteurPoteau capteur2;

    uint16_t address = 0x00;
    uint8_t data;

    //Premier octet
    uint8_t firstData = transmit.receive();
    uint16_t fileSize = firstData;
    mem.ecriture(address, firstData);
    address++;
    _delay_ms(5);

    //Deuxieme octet
    uint8_t secondData = transmit.receive();
    mem.ecriture(address, secondData);
    _delay_ms(5);
    address++;

    //Calcul du fileSize
    fileSize = (fileSize << 8) | secondData;
    
    //Ecriture en memoire du restant des octects
    while (address < fileSize)
    {
        uint8_t value = capteur2.readValueDM();
        mem.ecriture(address, value);
        _delay_ms(5);
        address++;
    }

    //Allumer LED en vert si ecriture en memoire fonctionne
    led.colorGreen();
}