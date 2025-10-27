# Analisi di un pacchetto HTTP con Wireshark e ricreazione di un server che risponda lo stesso pacchetto

## Analisi pacchetto con Wireshark

1. Aprire Wireshark, selezionare la scheda Ethernet del dispositivo e impostare come filtro "http";
2. Aprire un browser qualsiasi al link "http://example.com/";
3. Ora su wireshark appariranno i pacchetti scambiati tra la macchina e il server;
4. Copiare il contenuto html del pacchetto con scritto "(text/html)" nelle info.

## Contenuto HTML del pacchetto in arrivo dal server

```html
<!doctype html>
<html lang="en">
    <head>
        <title>Example Domain</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>body{background:#eee;width:60vw;margin:15vh auto;font-family:system-ui,sans-serif}h1{font-size:1.5em}div{opacity:0.8}a:link,a:visited{color:#348}</style>
    <body>
        <div><h1>Example Domain</h1>
            <p>This domain is for use in documentation examples without needing permission. Avoid use in operations.
            <p><a href="https://iana.org/domains/example">Learn more</a>
        </div>
    </body>
</html>
```
