# LecteurFTP

Voici comment programmer votre lecture FTP asynchrone

```cpp
#include <LecteurFTP.h>
// Si vous n'utilisez pas l'ESP82866 ni l'ESP-01, changez la ligne ci-bas conformément au micro-contrôleur choisi
#include <ESP8266WiFi.h>

const char *ssid     = "<SSID>";			//Identification de votre Wifi domestique (pour accéder à l'internet)
const char *password = "<PASSWORD>";		//Mot de passe de votre wifi domestique

const char *ftpSrv	 = "ftp.server.com";	//Adresse du serveur FTP où est logé votre ftpFile
const char *ftpUsr	 = "usser@server.com";	//Identifiant que réclame votre serveur FTP pour la connexion
const char *ftpPsw	 = "MyFTPpassword";		//Mot de passe associé à votre usager FTP
const char *ftpFile	 = "FileName.txt";		//Nom du ftpFile à récupérer
char *contentuFTP	 = "";				//Variable à garder ici vide, elle sera utilsée plus bas.

LecteurFTP lectureFTP(ftpSrv, ftpUsr, ftpPsw, ftpFile);

// Vous pouvez aussi spécifier le sous-répertoire, la valeur par défaut est "" (vide)
// Vous pouvez aussi spécifier la fréquence de mise à jour, la valeur par défaut et 55000
// Vous pouvez aussu spécifier le port du serveur FTP, la valeur par défaut est 22
// LecteurFTP lectureFTP(ftpSrv, ftpUsr, ftpPsw, ftpFile, "myRep/");
// LecteurFTP lectureFTP(ftpSrv, ftpUsr, ftpPsw, ftpFile, "myRep/", 75000);
// LecteurFTP lectureFTP(ftpSrv, ftpUsr, ftpPsw, ftpFile, "myRep/", 75000, 473);


void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
	contentuFTP = lectureFTP.getText();
	Serial.println(contenuFTP);
	//La ligne ci-haut devrait donner le même résultat que la ligne ci-bas
	Serial.println(lectureFTP.getText());
	delay(1000);
}
```

