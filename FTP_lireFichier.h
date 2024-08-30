#pragma once

#include <FTPClient_Generic.h>

#define DEBUG_FTP_lireFichier false
#define FTP_FREQUENCE 55000
#define FTP_DEFAULT_PORT 22

class FTP_lireFichier {
  private:
    LIREFTP*      dclient;
    bool          _udpSetup       = true;

    const char*   _ftpSrv = "ftp.server.org"; // Default time server
    const char*   _ftpUsr;
    const char*   _ftpPsw;
    const char*   _ftpRep = "";
    const char*   _ftpFile = "contenu.txt";
    unsigned int  _ftpPort = FTP_DEFAULT_PORT;
    long          _timeOffset     = 0;

    unsigned long _ftpFreq = FTP_FREQUENCE;  // In ms
    unsigned long _lastUpdate     = 0;      // In ms
    char*		   _contenuLU = "";

    void			contenuLU();
    int			fileSize = 0;
    char*			fileTime = "";

  public:
  	FTP_lireftp(LIREFTP& dclient, ftpSrv, ftpUsr, ftpPsw, ftpFile);
  	FTP_lireftp(LIREFTP& dclient, ftpSrv, ftpUsr, ftpPsw, ftpFile, const char* ftpRep);
  	FTP_lireftp(LIREFTP& dclient, ftpSrv, ftpUsr, ftpPsw, ftpFile, const char* ftpRep, int ftpFreq);
  	FTP_lireftp(LIREFTP& dclient, ftpSrv, ftpUsr, ftpPsw, ftpFile, const char* ftpRep, const int ftpFreq, const int ftpPort);


    /**
     * Set time server name
     *
     * @param poolServerName
     */
    void setftpSrv(const char* ftpSrv);

     /**
     * Set random local port
     */
    void ftpPort(unsigned int ftpPort);

    /**
     * Starts the underlying UDP client with the default local port
     */
    void begin();
    void begin(unsigned char* ftpRep);
    void begin(unsigned char* ftpRep, unsigned int ftpFreq;
    void begin(unsigned char* ftpRep, unsigned int ftpFreq, unsigned int ftpPort);

    /**
     * This should be called in the main loop of your application. By default an update from the NTP Server is only
     * made every 60 seconds. This can be configured in the FTP_lireFichier constructor.
     *
     * @return true on success, false on failure
     */
    bool update();
    /**
     * This will force the update from the NTP Server.
     *
     * @return true on success, false on failure
     */
    bool forceUpdate();

    /**
     * Définition des commandes accessibles à l'usager
     */
	void setFrequ(unsigned int ftpFreq);
	void setFrequency(unsigned int ftpFreq);
	void setServerName(unsigned char* ServerName);
	void setServerUser(unsigned char* ServerUser);
	void setServerPswd(unsigned char* ServerPassword);
	void setDirectory(unsigned char* ServerDir);
	void setFileName(unsigned char* FileName);
	void setPort(unsigned int ServPort);

    /**
     * Définition des valeurs retournées par l'objet
     */
    unsigned char* getText() const;
    unsigned long getTime() const;
    unsigned int getSize() const;

    //Vérifions ici si la connexion Wifi est bien active
    bool getStatus() const;

    /**
     * Demande de déconnexion Wifi
     */
    void end();
};
