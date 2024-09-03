/**
 * General licence
 * Copyright (c) 2015 by Patrick ALLAIRE
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "LecteurFTP.h"

bool LecteurFTP::forceUpdate() {
  #ifdef DEBUG_LecteurFTP
    Serial.println("Forcing update of your FTP`s file into the RAM");
  #endif
  if(getStatus() == false) { Serial.println("Il n`y a pas de connexion Wifi active.");  return false; }
  strcpy(_contenuLU, getText());
  _lastUpdate = millis();
  return true;
}

bool LecteurFTP::update() {
	if ((millis() - _lastUpdate >= _ftpFreq ) || _lastUpdate == 0) {      // Update after _ftpFreq  or Update if there was no update yet (if lastUpdate == 0)
		return forceUpdate();
	} else {
		return false;   // return false if update does not occur
	}
	return true;
}

char* LecteurFTP::getText() {
	if(getStatus() == false) { 
		if (Connexion() == true) {
			FTPclient.connect(_ftpSrv, _ftpPort);
			FTPclient.authenticate(_ftpUsr, _ftpPsw);
      	size_t fileSize = FTPclient.getFileSize(_ftpFile);
	      uint8_t fileBuffer[fileSize];
   	   FTPclient.downloadFile(_ftpFile, fileBuffer, fileSize);
	      FTPclient.disconnect();

			Serial.print  ("Voici la valeur lue : ");
			Serial.write(fileBuffer, fileSize);
			_contenuLU = (char *) (intptr_t) fileBuffer;
		} else {
			strcpy(_contenuLU,"");
		}
	}
	return _contenuLU;
}

bool LecteurFTP::Connexion() {
	int combien = 0;
	WiFi.begin();
	while (WiFi.status() != WL_CONNECTED && ++combien <= 40) {
		delay(500);
		Serial.print(".");
	}
	if (combien > 40) { 
		Serial.println(" échouée"); 
		return false; 
	} else { 
		Serial.println( " réussie! "); 
		FTPclient.connect(_ftpSrv, _ftpPort);
		FTPclient.authenticate(_ftpUsr, _ftpPsw);
		FTPclient.setWorkDirectory(_ftpRep);
		return true; 
	}
}

long LecteurFTP::getTime() {
  return 1232;
}

int LecteurFTP::getSize() {
	return sizeof(_contenuLU);
}


void LecteurFTP::end() {
  FTPclient.disconnect();
  status = false;
}

bool LecteurFTP::getStatus() {
	return status;
}

void LecteurFTP::setFreq(unsigned int ftpFreq) {
	_ftpFreq = ftpFreq;
}

void LecteurFTP::setServerName(char* ServerName) {
    _ftpSrv = ServerName;
}

void LecteurFTP::setServerUser(char* ServerUser) {
    _ftpUsr = ServerUser;
}

void LecteurFTP::setServerPswd(char* ServerPassword) {
    _ftpPsw = ServerPassword;
}

void LecteurFTP::setDirectory(char* ServerDir) {
    _ftpRep = ServerDir;
}

void LecteurFTP::setFileName(char* FileName) {
    _ftpFile = FileName;
}

void LecteurFTP::setFrequency(unsigned int ServFreq) {
    setFreq(ServFreq);
}

void LecteurFTP::setPort(int ServPort) {
//   FTPclient.disconnect();
    _ftpPort = ServPort;
}
