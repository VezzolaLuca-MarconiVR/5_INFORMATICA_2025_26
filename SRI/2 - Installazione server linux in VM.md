# Installazione e configurazione di un server Ubuntu su VM

## Installazione e setup del server

1. Installare il file .iso del server Ubuntu da [qui]("https://www.ubuntu-it.org/download");
2. Avviare una VM selezionando come disco il file .iso appena scaricato quando richiesto e procedere con l'installazione
3. durente il processo di configurazione guidata fare attenzione alla configurazione della tastiera e, se si vuole usare una versione più "leggera", scegliere la versione minimized del server Ubuntu (non serve selezionare alcuna delle altre opzioni);

### Note sulla configurazione:

- Se la tastiera non dovesse essere sull'impostazione italiana una vilta avviato il server si deve procedere nel seguente modo:
  - aprire la configurazione guidata per cambiare la lingua della tastiera:
    > sudo dpkg-reconfigure keyboard-configuration
  - dopo la configurazione guidata riavviare il server per applicare le modifiche con:
    > sudo reboot

## Download funzioni necessarie

_(per scaricare qualsiasi cosa serve un IP, quindi se si ha cambiato le impostazioni per utilizzare la "Scheda con bridge", rimettere le impostazioni base, cioè con il DNS)_

```bash
  sudo apt install nano
```

## Configurazione delle impostazioni di rete

_(specifico per VirtualBox)_

1. Spegnere la VM;
2. Nelle impostazioni (sezione base, non esperto), selezionare "Rete", selezionare "Scheda con bridge" invece di "NAT", poi premere "OK" e avviare nuovamente la VM;
3. Una volta avviata la VM, eseguire i seguenti comandi:

```bash
  cd /etc/netplan/
  ls
  sudo nano nomefile.yaml
```

- ls serve per vedere il nome del file di configurazione (.yaml)
- nano serve per modificare il contenuto del file .yaml in:
  ```yaml
  network:
    version: 2
    ethernets:
      enp0s3:
        dhcp4: no
        addresses:
          - 192.168.1.100/24
        nameservers:
          addresses:
            - 8.8.8.8
            - 8.8.4.4
        routes:
          - to: 0.0.0.0/0
            via: 192.168.1.1
  ```
  - "to: 0.0.0.0/0"" è la "default route"
  - "via:" è l'IP del tuo router

4. Dopodichè, salvare il file con CTRL+X e Y per confermare;
5. Una volta salvato il file di configurazione, applicare le modifiche fatte con:
   ```bash
   sudo netplan apply
   ```
