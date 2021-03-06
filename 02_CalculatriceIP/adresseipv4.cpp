#include "adresseipv4.h"


AdresseIPv4::AdresseIPv4(const quint8 _adresse[], const quint8 _suffixe){
    for (int i =0; i < 4; i++){
        adresse[i] = _adresse[i];
    }
    suffixe = _suffixe;
    CalculerMasque();
}

AdresseIPv4::AdresseIPv4(const quint8 _adresse[], const quint8 _masque[]){
    for (int i =0; i < 4; i++){
        adresse[i] = _adresse[i];
    }
    for (int i =0; i < 4; i++){
        masque[i]  = _masque[i];
    }
    CalculerSuffixe();
}

void AdresseIPv4::ObtenirMasque(quint8 _masque[]){
    for(int i = 0 ; i < 4 ; i++)
           _masque[i] = masque[i];
}

void AdresseIPv4::ObtenirAdresseReseau(quint8 _adresse[]){
    for(int i = 0 ; i < 4 ; i++)
    {
        _adresse[i] = adresse[i] & masque[i] ;
    }

}

void AdresseIPv4::ObtenirPremiereAdresse(quint8 _adresse[]){

    quint8 adresseDuReseau[4];
    ObtenirAdresseReseau(adresseDuReseau);
    adresseDuReseau[3] += 1;
    for(int i = 0 ; i < 4 ; i++)
        {
            _adresse[i] = adresseDuReseau[i]  ;
        }
}

void AdresseIPv4::ObtenirDerniereAdresse(quint8 _adresse[]){

    quint8 adresseDiffusion[4];
    ObtenirAdresseDiffusion(adresseDiffusion);
    for(int i=0; i<3; i++ ){
        _adresse[i] = adresseDiffusion[i];
    }
    _adresse[3] = adresseDiffusion[3] -1;
}

void AdresseIPv4::ObtenirAdresseDiffusion(quint8 _adresse[]){

    quint8 adresseDuReseau[4] ;
     ObtenirAdresseReseau(adresseDuReseau);
     for(int i=0 ; i<4 ; i++){
         _adresse[i] = adresseDuReseau[i] | ~masque[i];
     }
}

QString AdresseIPv4::ObtenirClasseAdresse(){
    QString classe;
    if ((adresse[0] & 0x80) == 0) classe = "(Classe A)";
    if ((adresse[0] & 0xc0) == 0x80) classe = "(Classe B)";
    if ((adresse[0] & 0xe0) == 0xc0) classe = "(Classe C)";
    if ((adresse[0] & 0xf0) == 0xe0) classe = "(Classe D)";
    if ((adresse[0] & 0xf0) == 0xf0) classe = "(Classe E)";

    return classe;
}

void AdresseIPv4::CalculerMasque(){

        quint8 valSuffixe = suffixe ;
        for(int i = 0 ; i < 4 ; i++){
                 masque[i] = 0 ;
        }
        int i = 0;
        while(valSuffixe >= 8){
            masque[i++] = 255 ;
            valSuffixe -= 8 ;
        }

        quint8 puissance = 128 ;
        while(valSuffixe-- > 0){
            masque[i] += puissance ;
            puissance /=2 ;
        }

}

void AdresseIPv4::CalculerSuffixe(){

}


