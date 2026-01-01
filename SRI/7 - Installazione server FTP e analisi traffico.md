# Installazione di un server FTP su VM Ubuntu server e analisi traffico dati con Wireshark

## Installazione e configurazione del server FTP

### Installazione

Per installare il server:

```shell
sudo apt install vsftpd
```

### Configurazione

Per creare i due nuovi utenti senza shell di login, con home la "jail" (che creeremo dopo) e per configurarne la password (ora è consigliato impostarla identica al nome utente per semplicità):

```shell
sudo useradd -M -d /var/ftp/sito1 -s /usr/sbin/nologin sito1
sudo passwd sito1
sudo useradd -M -d /var/ftp/sito2 -s /usr/sbin/nologin sito2
sudo passwd sito2
```

Spiegazione degli attributi di useradd:

> -M evita la creazione della home; -s /usr/sbin/nologin impedisce l'accesso alla shell

Per creare le home FTP degli utenti (Root-owned chroot + sottodirectory scrivibile):

```shell
sudo mkdir -p /var/ftp/sito1 /var/ftp/sito2
sudo chown root:root /var/ftp/sito1 /var/ftp/sito2
sudo chmod 755 /var/ftp/sito1 /var/ftp/sito2

# sottodirectory per accesso (anche in scrittura) dall'utente
sudo mkdir /var/ftp/sito1/upload
sudo chown sito1:sito1 /var/ftp/sito1/web
sudo mkdir /var/ftp/sito2/upload
sudo chown sito2:sito2 /var/ftp/sito2/web
```

Spiegazione di _chroot_ in vsftpd:

> Quando vsftpd mette un utente in chroot lo “rinchiude" in una directory che diventa la sua radice FTP: l’utente non può risalire oltre quella directory. Per motivi di sicurezza vsftpd rifiuta di usare una directory chroot che sia scrivibile dall’utente (altrimenti un utente potrebbe manipolare i file di sistema della "gabbia") e genera l’errore “500 OOPS: refusing to run with writable root inside chroot”. Per questo motivo la directory di chroot deve essere in possesso di root e non avere permessi di scrittura per l’utente.

Per configurare l'accesso al server FTP, decommentare le seguenti opzioni in /etc/vsftpd.conf (qui riportate in elenco precedute da una spiegazione ricavata da [questa pagina](https://linux.die.net/man/5/vsftpd.conf)):

```conf
# If enabled, vsftpd will run in standalone mode. This means that vsftpd must not be run from an inetd of some kind. Instead, the vsftpd executable is run once directly. vsftpd itself will then take care of listening for and handling incoming connections.
listen=YES
anonymous_enable=NO
# Controls whether local logins are permitted or not. If enabled, normal user accounts in /etc/passwd may be used to log in. This must be enable for any non-anonymous login to work, including virtual users.
local_enable=YES
# This controls whether any FTP commands which change the filesystem are allowed or not. These commands are: STOR, DELE, RNFR, RNTO, MKD, RMD, APPE and SITE
write_enable=YES
# If set to YES, local users will be (by default) placed in a chroot() jail in their home directory after login. Warning: This option has security implications, especially if the users have upload permission, or shell access. Only enable if you know what you are doing. Note that these security implications are not vsftpd specific. They apply to all FTP daemons which offer to put local users in chroot() jails.
chroot_local_user=YES
# This powerful option allows the override of any config option specified in the manual page, on a per-user basis. For example, if you set user_config_dir to be /etc/vsftpd/user_conf and then log on as the user "chris", then vsftpd will apply the settings in the file /etc/vsftpd/user_conf/chris for the duration of the session. (NOTA: la cartella citata nell'opzione e i file di configurazione li creeremo subito dopo aver modificato questo file)
user_config_dir=/etc/vsftpd_user_conf
```

Creazione della cartella contenente i file di configurazione degli utenti e i suddetti file (con già un opzione di configurazione - la root utente):

```shell
sudo mkdir -p /etc/vsftpd_user_conf
echo "local_root=/var/ftp/sito1" | sudo tee /etc/vsftpd_user_conf/sito1
echo "local_root=/var/ftp/sito2" | sudo tee /etc/vsftpd_user_conf/sito2
```

Il comando _tee_:

> In Linux "tee" (pronuncia di "T" in inglese - indicante la forma di un tubo (pipe) che partendo da un input, ha due output in due direzioni) viene utilizzato per leggere dall'input standard e scrivere i dati simultaneamente sull'output standard e su uno o più file. Viene comunemente utilizzato in combinazione con le pipe sia per visualizzare l'output sul terminale sia per salvarlo in un file.

Configurazione del firewall per la porta 21 e le porte PASV (da "pasv_min_port" a "pasv_max_port" come nel file di configurazione) con TCP:

```shell
sudo ufw allow 21/tcp
sudo ufw allow 40000:40100/tcp
sudo ufw reload
```

Successivamente riavviare per applicare il cambiamento:

```shell
sudo systemctl restart vsftpd
# Controllo dello stato (opzionale):
sudo systemctl status vsftpd
```

## Utilizzo dei comandi base per caricare e scaricare un file con FTP da CMD:

![Screenshot della connessione FTP via CMD](image.png)

Comandi di base del client ftp:

- **open** per connetterti a un server FTP remoto.
- **user** per inviare un nome utente per l'autenticazione.
- **pass** per inviare una password per l'autenticazione.
- **cd** per modificare la directory di lavoro corrente sul sistema remoto.
- **lcd** per modificare la directory di lavoro locale (quella nella quale poi scarica i file).
- **pwd** per visualizzare la directory di lavoro corrente sul sistema remoto.
- **ls** o dir per elencare il contenuto della directory remota.
- **get** per scaricare un singolo file dal sistema remoto alla macchina locale.
- **mget** per scaricare più file dal sistema remoto.
- **put** per caricare un singolo file dalla macchina locale al sistema remoto.
- **mput** per caricare più file sul sistema remoto.
- **delete** o mdelete per rimuovere uno o più file dal sistema remoto.
- **mkdir** per creare una nuova directory sul sistema remoto.
- **rmdir** per rimuovere una directory dal sistema remoto.
- **quit** o bye per terminare la sessione FTP ed uscire.
- **help** o ? per visualizzare un elenco di comandi disponibili o una guida per un comando specifico.
- **binary** per impostare la modalità di trasferimento su binario, adatta per file non di testo.
- **ascii** per impostare la modalità di trasferimento su ASCII, adatta ai file di testo.
- **prompt** per attivare/disattivare la richiesta interattiva durante più operazioni sui file.
- **hash** per visualizzare un hash mark (#) per ogni blocco di dati trasferiti, utile per monitorare i progressi.
- **verbose** per consentire (o rimuovere) l'output dettagliato delle risposte del server e delle statistiche di trasferimento.
- **trace** per abilitare il tracciamento dei pacchetti a fini di debug.
- **debug** per abilitare la modalità di debug, mostrando tutti i comandi inviati al server.
