[Sito guida](https://wiki.ubuntu-it.org/Server/MySql)


### Installazione di MySQL
```bash
sudo apt update
sudoapt install mysql-server
```
### Configurazione del server
Aggiungere "bind-address = 127.0.0.1" (indicando l'IP della macchina sulla quale gira questo server) tramite:
```bash
sudo nano /etc/mysql/my.cnf
```
// FORSE NON SERVE FARLO DA LOCALE