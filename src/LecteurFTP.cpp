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
	_contenuLU[0]='\0';
	if (Connexion() == true) {
   	size_t _ftpFileSize = FTPclient.getFileSize(_ftpFileName);
      uint8_t fileBuffer[_ftpFileSize];
	   FTPclient.downloadFile(_ftpFileName, fileBuffer, _ftpFileSize);
      FTPclient.disconnect();

		Serial.print  ("Voici la valeur lue : ");
		Serial.write(fileBuffer, _ftpFileSize);
		char* ceci = (char *) (intptr_t) fileBuffer;
		int rendu = 0;
		for (int THISx=0; THISx<_ftpFileSize; THISx++) {
			if (isAscii(ceci[THISx])) { _contenuLU[rendu++] = ceci[THISx]; }
		}
	}
	return _contenuLU;
}

bool LecteurFTP::Connexion() {
	int combien = 0;
	if (WiFi.status() != WL_CONNECTED) {
		WiFi.begin();
		while (WiFi.status() != WL_CONNECTED && ++combien <= 40) {
			delay(500);
			Serial.print(".");
		}
	}
	if (combien > 40) { 
		Serial.println(" échouée"); 
		return false; 
	} else { 
		Serial.println( " Connexion wifi rétablie avec succès! "); 
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
    strlcpy(_ftpRep, ServerDir, sizeof _ftpRep);
}

void LecteurFTP::setFileName(char* FileName) {
    strlcpy(_ftpFileName, FileName, sizeof _ftpFileName);
}

void LecteurFTP::setFrequency(unsigned int ServFreq) {
    setFreq(ServFreq);
}

void LecteurFTP::setPort(int ServPort) {
//   FTPclient.disconnect();
    _ftpPort = ServPort;
}
