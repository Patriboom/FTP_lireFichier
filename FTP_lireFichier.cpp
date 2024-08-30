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

#include "FTP_lireFichier.h"

FTP_lireFichier::FTP_lireFichier(LIREFTP& lireFTP, char* ftpSrv, char* ftpUsr, char* ftpPsw, char* ftpFile) {
  this->_lireFTP	= &lireFTP;
  this->_ftpSev 	= ftpSrv;
  this->_ftpUsr 	= ftpUsr;
  this->_ftpPsw 	= ftpPsw;
  this->_ftpFile 	= ftpFile;
}

FTP_lireFichier::FTP_lireFichier(LIREFTP& lireFTP, char* ftpSrv, char* ftpUsr, char* ftpPsw, char* ftpFile, char* ftpRep) {
  this->_lireFTP	= &lireFTP;
  this->_ftpSev 	= ftpSrv;
  this->_ftpUsr 	= ftpUsr;
  this->_ftpPsw 	= ftpPsw;
  this->_ftpFile 	= ftpFile;
  this->_ftpRep 	= ftpRep;
}
FTP_lireFichier::FTP_lireFichier(LIREFTP& lireFTP, char* ftpSrv, char* ftpUsr, char* ftpPsw, char* ftpFile, char* ftpRep, int ftpFreq) {
  this->_lireFTP	= &lireFTP;
  this->_ftpSev 	= ftpSrv;
  this->_ftpUsr 	= ftpUsr;
  this->_ftpPsw 	= ftpPsw;
  this->_ftpFile 	= ftpFile;
  this->_ftpRep 	= ftpRep;
  this->_ftpFreq 	= ftpFreq;
}
FTP_lireFichier::FTP_lireFichier(LIREFTP& lireFTP, char* ftpSrv, char* ftpUsr, char* ftpPsw, char* ftpFile, char* ftpRep, int ftpFreq, ftpPort) {
  this->_lireFTP	= &lireFTP;
  this->_ftpSev 	= ftpSrv;
  this->_ftpUsr 	= ftpUsr;
  this->_ftpPsw 	= ftpPsw;
  this->_ftpFile 	= ftpFile;
  this->_ftpRep 	= ftpRep;
  this->_ftpFreq 	= ftpFreq;
  this->_ftpPort 	= ftpPort;
}


void FTP_lireFichier::begin() {
  this->begin(this->_ftpSrv, this->_ftpUsr, this->_ftpPsw, this->_ftpFile);
}

void FTP_lireFichier::begin(char* ftpRep) {
	this->_ftpRep = ftpRep;
}

void FTP_lireFichier::begin(char* ftpRep, int ftpFreq) {
	this->_ftpRep = ftpRep;
	this->_ftpFreq = ftpFreq;
}

void FTP_lireFichier::begin(char* ftpRep, int ftpFreq, int ftpPort) {
	this->_ftpRep = ftpRep;
	this->_ftpFreq = ftpFreq;
	this->_ftpPort = ftpPort;
}

bool FTP_lireFichier::forceUpdate() {
  #ifdef DEBUG_FTP_lireFichier
    Serial.println("Forcing update of your FTP`s file into the RAM");
  #endif
  if(!this->Status) { return false; }
  this->getText;
  this->_lastUpdate = millis();
  return true;
}

bool FTP_lireFichier::update() {
	if ((millis() - this->_lastUpdate >= this->_updateInterval) || this->_lastUpdate == 0) {      // Update after _updateInterval or Update if there was no update yet (if lastUpdate == 0)
		return this->forceUpdate();
	} else {
		return false;   // return false if update does not occur
	}
	return true;
}

char FTP_lireFichier::getText() {
	if(!this->Status) { 
		if (FTP_lire->Connexin()) {
			this->Wifi.OpenConnection();
			this->Wifi.InitFile(COMMAND_XFER_TYPE_ASCII);
			this->Wifi.DownloadString(this->_ftpFile, this->contenuLU);
			this->Wifi.CloseConnection();
			Serial.print  ("Voici la valeur lue : ");
			Serial.println(this->contenuLU);
			this->fileSize = Wifi.Size();
		} else {
			return "";
		}
	}
	return this->_contenuLU;
}

bool Connexion() {
	int combien = 0;
	this->WiFi.begin(this->_ssid, this->_pswd);
	while (this->WiFi.status() != WL_CONNECTED && ++combien <= 40) {
		delay(500);
		Serial.print(".");
	}
	if (combien > 40) { 
		Serial.println(" échouée"); 
		return false; 
	} else { 
		Serial.println( " réussie! "); 
		if (this->_ftpRep != "") { this->wifi.ChangeWorkDir(_ftpRep); }
		return true; 
	}
}

bool FTP_lireFichier::isTimeSet() const {
  return (this->_lastUpdate != 0); // returns true if the time has been set, else false
}

unsigned long FTP_lireFichier::getTime() const {
  return this->WiFi.GetLastModifiedTime();
}

int FTP_lireFichier::getTime() {
  return this->fileTime;
}

int FTP_lireFichier::getSize() {
  return this->fileSize;
}


void FTP_lireFichier::end() {
  this->_udp->stop();
  this->_udpSetup = false;
}


void FTP_lireFichier::setFrequ(unsigned int ftpFreq) {
  this->_ftpFreq = ftpFreq;
}

void FTP_lireFichier::setServerName(const char* ServerName) {
    this->_ftpSrv = ServerName;
}

void FTP_lireFichier::setServerUser(const char* ServerUser) {
    this->_ftpUsr = ServerName;
}

void FTP_lireFichier::setServerPswd(const char* ServerPassword) {
    this->_ftpPsw = ServerPassword;
}

void FTP_lireFichier::setDirectory(const char* ServerDir) {
    this->_ftpRep = ServerDir;
}

void FTP_lireFichier::setFileName(const char* FileName) {
    this->_ftpFile = FileName;
}

void FTP_lireFichier::setFrequency(const int ServFreq) {
    this->_ftpFreq = this->setFrequ(ServFreq);
}

void FTP_lireFichier::setPort(const int ServPort) {
    this->_ftpPort = ServPort;
}

