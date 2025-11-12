# Server web multisito

## Setup host

Per poter risolvere dei nomi di server in indirizzi ip senza l'utilizzo di un server DNS serve modificare il file "hosts" della macchina (è preferibile usare una VM windows per non modificare il reindirizzamento della macchina fisica):

La posizione del file cambia da un sistema operativo all'altro, ma le tipiche posizioni sono le seguenti:

- Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
- Linux – “/etc/hosts”
- Mac OS X – “/private/etc/hosts”

Esempio di file "hosts" modificato per risolvere due diversi siti dallo stesso IP:
![File "hosts" modificato su VM](fileHosts.png)

## Setup server:

Ogni sito ha la sua intera struttura all'interno della propria cartella sul server in "/var/www", quindi serve creare una cartella root per ogni sito che si vuole aggiungere (in aggiunta a http, il dominio di base):

```bash
sudo mkdir sito1.me
sudo mkdir sito2.me
...
```
