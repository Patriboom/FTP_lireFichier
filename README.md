# LecteurFTP

Async connect to FTP, read data from a file, here is how:

```cpp
#include <LecteurFTP.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>

const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>";

const char *ftpSrv	 = "ftp.server.com";	//FTP server's address
const char *ftpUsr	 = "usser@server.com";	//Username for the FTP server
const char *ftpPsw	 = "MyFTPpassword";		//Password for the FTP user
const char *ftpFile	 = "FileName.txt";		//File to read (download into RAM)
char *contentFile	 = "";				//Please keep this empty, that will carry the file's content

LecteurFTP lectureFTP(ftpSrv, ftpUsr, ftpPsw, ftpFile);

// You can specify the file's directory (last char must be /  )
// You can specify the update interval (in milliseconds) default value is 55000
// You can specify the FTP port, default value is 22
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
	contentFile = lectureFTP.getText();
	Serial.println(contentFile);
	//Previous line and following line should return the same
	Serial.println(lectureFTP.getText());
	delay(1000);
}
```

