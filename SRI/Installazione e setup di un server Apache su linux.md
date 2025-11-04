# Installazione e setup di un server Apache su linux

## Installazione di Apache sulla VM con Ubuntu Server:

1. Aggiornare la lista di pacchetti del sistema:
   > sudo apt update
2. Installare Apache:
   > sudo apt install apache2 -y
3. Assicurarsi che il server si sia già avviato da solo:
   > sudo systemctl status apache2
4. Assicurarsi che Apache si avvii sempre all'avvio della macchina:
   > sudo systemctl enable apache2
5. Configurare il firewall per permettere il traffico HTTP:
   > sudo ufw allow 'Apache'

Se non dovesse riconoscere ufw, installarlo con:

> sudo apt install ufw

Inoltre, assicurarsi che UFW (Uncomplicated Firewall) si avvii all'avvio della macchina:

> sudo systemctl enable ufw

Per leggere la documentazione di Apache:

- installare la documentazione:
  > sudo apt install apache2-doc
- includere il manuale nel file di configurazione:
  > sudo a2enconf apache2-doc
- riavviare Apache:
  > sudo systemctl reload apache2
- se non presente nel sistema, installare most (il visualizzatore di file più recente e completo) con:
  > sudo apt install most
- aprire il file contenente la documentazione con most (oppure andare a http://indirizzoServer/manual):
  > most /usr/share/doc/apache2/README.Debian.gz

(non esistono i file di documentazione - possibile interferenza con la modalità leggera)

Per accedere tramite ssh alla VM (per copiare con comodità del testo nel terminale):

- installare ssh:
  > sudo apt install openssh-server -y
- verificare che il servizio ssh si sia attivato automaticamente:
  > sudo systemctl status ssh
- assicurarsi che il servizio ssh parta all'avvio della macchina:
  > sudo systemctl enable ssh
- se UFW è abilitato (come mostrato in precedenza), permettere le connessioni ssh con:
  > sudo ufw allow ssh

## Personalizzazione e analisi del traffico del server

### Modifica dell'index

Per modificare l'index - cioè la pagina che attualmente viene restituita quando si manda una GET all'indirizzo del server - procedere con:

> sudo nano /var/www/html/index.html

Una volta aperto il file, tenere premuto "Ctrl + K" per tagliare tutte le righe e poi rimpiazzarle con il proprio codice HTML dell'index.

### Osservare lo stato e le statistiche del server Apache:

Permettere la visualizzazione del file di stato ad una subnet:

> sudo nano /etc/apache2/mods-enabled/status.conf

Modificare il contenuto del tag "Location":

```Apache
<Location "/server-status">
    SetHandler server-status
    Require ip 192.168.1.0/24
</Location>
```

Riavviare Apache:

> sudo systemctl restart apache2

Visitare "http://[serverAddress]/server-status" nel browser.
