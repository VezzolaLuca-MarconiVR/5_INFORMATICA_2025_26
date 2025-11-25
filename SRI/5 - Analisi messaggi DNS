# Analisi di una query e della relativa response DNS

Tramite wireshark, utilizzando il filtro "dns" è possibile visualizzare tutti i messaggi inviati e ricevuti inerenti al DNS.

Per inescare una query DNS aprire un browser qualsiasi e digitare un nome di dominio - per esempio "www.google.com".

## Analisi query

Dopo aver trovato in Wireshark un messaggio con "Standard query [...] www.google.com" come info, possiamo analizzarne il contenuto:

![analisi messaggio di query](img/analisiDNSQuery.png)

## Analisi response

Inoltre, poco dopo il messaggio di query troveremo anche la response corrispondente, con "Standard query response [...] www.google.com [...]" seguita dagli indirizzi IPv4 e IPv6 risolti (identificabili anche nel campo "Additional Records" del messaggio stesso):

![analisi messaggio di response](img/analisiDNSResponse.png)
