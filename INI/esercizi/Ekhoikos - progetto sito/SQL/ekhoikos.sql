-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: Apr 09, 2026 alle 21:19
-- Versione del server: 10.4.32-MariaDB
-- Versione PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ekhoikos`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `file`
--

CREATE TABLE `file` (
  `idFIle` int(11) NOT NULL,
  `idSpazio` int(11) NOT NULL,
  `nome` varchar(255) DEFAULT NULL,
  `filePath` varchar(260) DEFAULT NULL,
  `dimensioneByte` int(11) NOT NULL,
  `unicoYN` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `file`
--

INSERT INTO `file` (`idFIle`, `idSpazio`, `nome`, `filePath`, `dimensioneByte`, `unicoYN`) VALUES
(1, 2, 'schema_macrame_base.pdf', '/storage/tier2/sofia_luna/schema_macrame_base.pdf', 2457600, 0),
(2, 2, 'schema_macrame_avanzato.pdf', '/storage/tier2/sofia_luna/schema_macrame_avanzato.pdf', 3145728, 0),
(3, 2, 'ricamo_mandala_schema.pdf', '/storage/tier2/sofia_luna/ricamo_mandala_schema.pdf', 1572864, 0),
(4, 3, 'stampa_botanica_felce.png', '/storage/tier3/elena_foglia/stampa_botanica_felce.png', 8388608, 1),
(5, 3, 'stampa_botanica_iris.png', '/storage/tier3/elena_foglia/stampa_botanica_iris.png', 7340032, 1),
(6, 3, 'pattern_tessuto_natura.svg', '/storage/tier3/elena_foglia/pattern_tessuto_natura.svg', 524288, 0);

-- --------------------------------------------------------

--
-- Struttura della tabella `fileinprodottidigitali`
--

CREATE TABLE `fileinprodottidigitali` (
  `idFile` int(11) NOT NULL,
  `idSpazio` int(11) NOT NULL,
  `idProd` int(11) NOT NULL,
  `nomeVenditore` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `fileinprodottidigitali`
--

INSERT INTO `fileinprodottidigitali` (`idFile`, `idSpazio`, `idProd`, `nomeVenditore`) VALUES
(1, 2, 7, 'sofia_luna'),
(2, 2, 7, 'sofia_luna'),
(3, 2, 7, 'sofia_luna'),
(6, 3, 11, 'elena_foglia');

-- --------------------------------------------------------

--
-- Struttura della tabella `licenze`
--

CREATE TABLE `licenze` (
  `nome` varchar(32) NOT NULL,
  `descrizione` varchar(1024) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `licenze`
--

INSERT INTO `licenze` (`nome`, `descrizione`) VALUES
('CC BY 4.0', 'Creative Commons Attribuzione 4.0 Internazionale. Consente uso, condivisione, adattamento e distribuzione, anche commerciale, a condizione di citare adeguatamente l autore originale.'),
('CC BY-NC 4.0', 'Creative Commons Attribuzione-Non Commerciale 4.0. Permette uso e condivisione libera solo per scopi non commerciali, con obbligo di attribuzione all autore.'),
('CC BY-ND 4.0', 'Creative Commons Attribuzione-Non opere derivate 4.0. Consente redistribuzione, anche commerciale, solo nella forma originale e senza modifiche, con attribuzione.'),
('Uso Personale', 'Licenza esclusiva per uso strettamente personale e privato. Non e consentita la redistribuzione, la pubblicazione o l utilizzo commerciale del file acquistato.');

-- --------------------------------------------------------

--
-- Struttura della tabella `prodotti`
--

CREATE TABLE `prodotti` (
  `idProd` int(11) NOT NULL,
  `nomeVenditore` varchar(32) NOT NULL,
  `statoProd` enum('Disponibile','Esaurito','Su ordinazione') DEFAULT NULL,
  `descrizione` varchar(1024) DEFAULT NULL,
  `nome` varchar(32) NOT NULL,
  `prezzo` decimal(10,2) NOT NULL,
  `quantita` int(11) DEFAULT NULL,
  `acconto` decimal(10,2) DEFAULT NULL,
  `urlImmagine` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `prodotti`
--

INSERT INTO `prodotti` (`idProd`, `nomeVenditore`, `statoProd`, `descrizione`, `nome`, `prezzo`, `quantita`, `acconto`, `urlImmagine`) VALUES
(1, 'giulia_verde', 'Disponibile', 'Tazza in ceramica lavorata a mano con argilla naturale estratta localmente e smaltatura ecologica priva di piombo e cadmio. Ogni pezzo e unico, decorato con motivi botanici incisi a mano prima della cottura.', 'Tazza Botanica in Ceramica', 28.00, 12, NULL, 'tazzaLavorataAMano.webp'),
(2, 'giulia_verde', 'Disponibile', 'Set di 4 piattini in ceramica artigianale realizzati con argilla di recupero da scarti di lavorazione. Decorati con pigmenti naturali e ossidi minerali. Adatti per dolci, formaggi stagionati o come sottobicchieri.', 'Set Piattini in Ceramica Natural', 45.00, 6, NULL, NULL),
(3, 'giulia_verde', 'Su ordinazione', 'Vaso in ceramica completamente personalizzabile: il cliente sceglie forma, dimensione e motivo decorativo. Realizzato con argilla locale e tecniche di cottura a bassa emissione di CO2. Tempi di consegna: 3-4 settimane.', 'Vaso Ceramica Personalizzato', 65.00, NULL, 20.00, NULL),
(4, 'marco_bosco', 'Disponibile', 'Tagliere ricavato da un tronco di noce recuperato da potature locali. Trattato esclusivamente con olio di lino biologico, senza vernici o prodotti chimici. Le venature sono uniche su ogni pezzo.', 'Tagliere in Legno di Noce Recupe', 38.00, 8, NULL, NULL),
(5, 'marco_bosco', 'Disponibile', 'Cornice per foto realizzata con rami e legni di recupero raccolti nel bosco vicino al laboratorio. Formato 15x20 cm. Finitura a cera d api biologica per esaltare il colore naturale del legno.', 'Cornice Rustica in Legno di Recu', 22.00, 15, NULL, NULL),
(6, 'sofia_luna', 'Disponibile', 'Appendiabiti da parete intrecciato a mano in macrame con cordino di cotone biologico non sbiancato. Completamente privo di coloranti sintetici. Dimensioni: circa 40x60 cm. Gancio in legno di pino recuperato.', 'Appendiabiti Macrame Cotone Bio', 35.00, 10, NULL, NULL),
(7, 'sofia_luna', 'Disponibile', 'Schema PDF scaricabile per realizzare un appendiabiti in macrame e un ricamo mandala. Istruzioni passo passo, lista materiali eco-compatibili, varianti cromatiche con tinture naturali. Adatto a principianti e intermedi.', 'Schema Macrame & Ricamo Mandala', 12.00, NULL, NULL, NULL),
(8, 'pietro_sole', 'Disponibile', 'Sapone artigianale al carbone vegetale attivo e argilla verde. Ingredienti 100% naturali e biodegradabili, senza SLS, parabeni o profumi sintetici. Peso circa 100g. Confezionato in carta kraft riciclata.', 'Sapone Artigianale Carbone & Arg', 8.50, 30, NULL, 'saponeAlCarboneVegetale.webp'),
(9, 'pietro_sole', 'Disponibile', 'Kit da 3 saponi artigianali profumati con oli essenziali biologici certificati: lavanda, tea tree e arancia dolce. Ingredienti naturali e cruelty-free, testati su pelli sensibili. Ottimo come idea regalo sostenibile.', 'Kit Saponi Artigianali Oli Essen', 22.00, 18, NULL, NULL),
(10, 'elena_foglia', 'Disponibile', 'Stampa artistica botanica su carta cotone 300g riciclata al 50%, formato A4. Raffigura felci e iris selvatiche scansionate ad alta risoluzione. Ogni stampa e numerata e firmata a mano. Spedita in tubo riciclato.', 'Stampa Artistica Botanica - Seri', 40.00, 5, NULL, NULL),
(11, 'elena_foglia', 'Disponibile', 'Pack di pattern digitali in formato SVG ad alta risoluzione ispirati alla natura: foglie, ramoscelli e fiori selvatici. Pronti per uso su tessuti, carta da parati, packaging eco e progetti grafici sostenibili.', 'Pattern Digitali Botanici SVG', 18.00, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Struttura della tabella `prodottidigitali`
--

CREATE TABLE `prodottidigitali` (
  `idProd` int(11) NOT NULL,
  `nomeVenditore` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `prodottidigitali`
--

INSERT INTO `prodottidigitali` (`idProd`, `nomeVenditore`) VALUES
(7, 'sofia_luna'),
(11, 'elena_foglia');

-- --------------------------------------------------------

--
-- Struttura della tabella `prodottifisici`
--

CREATE TABLE `prodottifisici` (
  `idProd` int(11) NOT NULL,
  `nomeVenditore` varchar(32) NOT NULL,
  `pesoKg` decimal(3,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `prodottifisici`
--

INSERT INTO `prodottifisici` (`idProd`, `nomeVenditore`, `pesoKg`) VALUES
(1, 'giulia_verde', 0.35),
(2, 'giulia_verde', 0.60),
(3, 'giulia_verde', 0.80),
(4, 'marco_bosco', 0.75),
(5, 'marco_bosco', 0.30),
(6, 'sofia_luna', 0.20),
(8, 'pietro_sole', 0.10),
(9, 'pietro_sole', 0.30),
(10, 'elena_foglia', 0.05);

-- --------------------------------------------------------

--
-- Struttura della tabella `prodottivenduti`
--

CREATE TABLE `prodottivenduti` (
  `idProd` int(11) DEFAULT NULL,
  `nomeVenditore` varchar(32) DEFAULT NULL,
  `nomeCliente` varchar(32) DEFAULT NULL,
  `stelle` int(11) DEFAULT NULL CHECK (`stelle` between 1 and 5),
  `puntiEco` int(11) DEFAULT NULL CHECK (`puntiEco` between 1 and 5),
  `recensione` varchar(512) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `prodottivenduti`
--

INSERT INTO `prodottivenduti` (`idProd`, `nomeVenditore`, `nomeCliente`, `stelle`, `puntiEco`, `recensione`) VALUES
(1, 'giulia_verde', 'luca_fiume', NULL, NULL, NULL),
(1, 'giulia_verde', 'anna_terra', NULL, NULL, NULL),
(4, 'marco_bosco', 'chiara_vento', NULL, NULL, NULL),
(5, 'marco_bosco', 'riccardo_mare', NULL, NULL, NULL),
(6, 'sofia_luna', 'fabio_pietra', NULL, NULL, NULL),
(7, 'sofia_luna', 'anna_terra', NULL, NULL, NULL),
(7, 'sofia_luna', 'riccardo_mare', NULL, NULL, NULL),
(8, 'pietro_sole', 'luca_fiume', NULL, NULL, NULL),
(9, 'pietro_sole', 'chiara_vento', NULL, NULL, NULL),
(10, 'elena_foglia', 'riccardo_mare', NULL, NULL, NULL),
(11, 'elena_foglia', 'fabio_pietra', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Struttura della tabella `richieste`
--

CREATE TABLE `richieste` (
  `idRichiesta` int(11) NOT NULL,
  `nomeCliente` varchar(32) NOT NULL,
  `idProd` int(11) NOT NULL,
  `nomeVenditore` varchar(32) NOT NULL,
  `statoRichiesta` enum('In attesa','Accettata','Completata','Rifiutata') DEFAULT NULL,
  `specificazioni` varchar(512) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `richieste`
--

INSERT INTO `richieste` (`idRichiesta`, `nomeCliente`, `idProd`, `nomeVenditore`, `statoRichiesta`, `specificazioni`) VALUES
(1, 'luca_fiume', 3, 'giulia_verde', 'Accettata', 'Vaso di medie dimensioni (circa 25 cm di altezza) con motivi a foglie di ulivo incisi. Colori: terracotta naturale con sfumature verdi. Vorrei anche un foro di drenaggio sul fondo.'),
(2, 'anna_terra', 3, 'giulia_verde', 'In attesa', 'Vaso piccolo per piante grasse, con foro di drenaggio. Decorazione geometrica minimal stile nordico. Preferisco toni neutri: beige sabbia e grigio ardesia.'),
(3, 'riccardo_mare', 3, 'giulia_verde', 'Completata', 'Grande vaso da esterno resistente alle intemperie per pianta di limone (diam. 35 cm). Motivo con onde marine stilizzate. Colori: blu ceruleo e bianco calce.'),
(4, 'chiara_vento', 6, 'sofia_luna', 'In attesa', 'Schema per un appendiabiti macrame in versione XL (circa 60x90 cm) con frange lunghe e almeno 8 ganci.'),
(5, 'fabio_pietra', 9, 'pietro_sole', 'Rifiutata', 'Possibile sostituire i profumi standard con eucalipto, menta piperita e rosa mosqueta biologica? Confezionamento in scatola regalo in cartone riciclato con nastro in cotone invece del cellofan.');

-- --------------------------------------------------------

--
-- Struttura della tabella `spazidimemoria`
--

CREATE TABLE `spazidimemoria` (
  `idSpazio` int(11) NOT NULL,
  `tier` int(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `spazidimemoria`
--

INSERT INTO `spazidimemoria` (`idSpazio`, `tier`) VALUES
(1, 1),
(2, 2),
(3, 3);

-- --------------------------------------------------------

--
-- Struttura della tabella `utenti`
--

CREATE TABLE `utenti` (
  `nomeUtente` varchar(32) NOT NULL,
  `psw` varchar(255) NOT NULL,
  `nome` varchar(64) NOT NULL,
  `cognome` varchar(64) NOT NULL,
  `dNascita` date NOT NULL,
  `email` varchar(320) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `utenti`
--

INSERT INTO `utenti` (`nomeUtente`, `psw`, `nome`, `cognome`, `dNascita`, `email`) VALUES
('anna_terra', '$2y$12$fxuq.yvGaHzVnEon4/CzLu0umkdWFfzYXzPyBOTGs8TfnJSEyMdtO', 'Anna', 'Terranova', '1992-06-25', 'anna.terranova@ekhoikos.it'),
('chiara_vento', '$2y$12$qilzkqR.kzoNNXLLMaXpOOKlAv5kcawmW6vaS3To8hifUWVxSWKVe', 'Chiara', 'Ventosi', '1997-01-03', 'chiara.ventosi@ekhoikos.it'),
('elena_foglia', '$2y$12$wFrcKIELC79V8k6Z.czFju80WI3vvHGb05LZtwwbDu57AlhHjZLBW', 'Elena', 'Fogliani', '1995-09-12', 'elena.fogliani@ekhoikos.it'),
('fabio_pietra', '$2y$12$oBxfSbwghT2aBhbg7cXDB.W3FU6XFkQOXh5eNyB6sjpfJUjsCD9ge', 'Fabio', 'Pietrani', '1983-08-18', 'fabio.pietrani@ekhoikos.it'),
('giulia_verde', '$2y$12$LsK/dTzyZjS9zvwfkn.Z4Oycu9j7j5tuo7z1dc5b30lBOAejsJMyW', 'Giulia', 'Verdi', '1990-03-15', 'giulia.verdi@ekhoikos.it'),
('lucaV', '$2y$10$jeRk2zJ0SnEwzLltgpPZXOXKn18mGbV.WhpQW0wKnonHT2dyj2Hmi', 'Luca', 'Vezzola', '2007-05-27', 'lucav@gmail.com'),
('luca_fiume', '$2y$12$Lsq7KFPnJkP77QraEJyoHerBjEVARoU9B1fWDVJPOLNM7/OZrxxKS', 'Luca', 'Fiumara', '1988-02-14', 'luca.fiumara@ekhoikos.it'),
('marco_bosco', '$2y$12$g08dJL9M7XdkvZFhBOilRuDQlTjH/tOEq0uZ4mPSwajMeiYNM9Ab6', 'Marco', 'Boschi', '1985-07-22', 'marco.boschi@ekhoikos.it'),
('pietro_sole', '$2y$12$W1M/QT6p1rpaQtfMgxgrxO8CviasFLqAhnY4O5R9amkGLWS6Mf0XS', 'Pietro', 'Soleri', '1978-05-30', 'pietro.soleri@ekhoikos.it'),
('riccardo_mare', '$2y$12$O.GOpNgvSFG2IC5iLKQPW.kr98UkDIhMCRlyB1Emb8QTgC9qlNVkC', 'Riccardo', 'Marelli', '1991-12-07', 'riccardo.marelli@ekhoikos.it'),
('sofia_luna', '$2y$12$.zWqaEjmQv7vqlev81M90uZLnkkLH2PZQb.ubyukcV.tXoicXgMsG', 'Sofia', 'Lunardi', '1993-11-08', 'sofia.lunardi@ekhoikos.it');

-- --------------------------------------------------------

--
-- Struttura della tabella `venditori`
--

CREATE TABLE `venditori` (
  `nomeUtente` varchar(32) NOT NULL,
  `digitaleOFisico` enum('Digitale','Fisico') DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `venditori`
--

INSERT INTO `venditori` (`nomeUtente`, `digitaleOFisico`) VALUES
('elena_foglia', 'Digitale'),
('giulia_verde', 'Fisico'),
('marco_bosco', 'Fisico'),
('pietro_sole', 'Fisico'),
('sofia_luna', 'Digitale');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `file`
--
ALTER TABLE `file`
  ADD PRIMARY KEY (`idFIle`,`idSpazio`),
  ADD KEY `idSpazio` (`idSpazio`);

--
-- Indici per le tabelle `fileinprodottidigitali`
--
ALTER TABLE `fileinprodottidigitali`
  ADD PRIMARY KEY (`idFile`,`idSpazio`,`idProd`,`nomeVenditore`),
  ADD KEY `idProd` (`idProd`,`nomeVenditore`);

--
-- Indici per le tabelle `licenze`
--
ALTER TABLE `licenze`
  ADD PRIMARY KEY (`nome`);

--
-- Indici per le tabelle `prodotti`
--
ALTER TABLE `prodotti`
  ADD PRIMARY KEY (`idProd`,`nomeVenditore`),
  ADD KEY `nomeVenditore` (`nomeVenditore`);

--
-- Indici per le tabelle `prodottidigitali`
--
ALTER TABLE `prodottidigitali`
  ADD PRIMARY KEY (`idProd`,`nomeVenditore`);

--
-- Indici per le tabelle `prodottifisici`
--
ALTER TABLE `prodottifisici`
  ADD PRIMARY KEY (`idProd`,`nomeVenditore`);

--
-- Indici per le tabelle `prodottivenduti`
--
ALTER TABLE `prodottivenduti`
  ADD KEY `idProd` (`idProd`,`nomeVenditore`),
  ADD KEY `nomeCliente` (`nomeCliente`);

--
-- Indici per le tabelle `richieste`
--
ALTER TABLE `richieste`
  ADD PRIMARY KEY (`idRichiesta`,`nomeCliente`,`idProd`,`nomeVenditore`),
  ADD KEY `nomeCliente` (`nomeCliente`),
  ADD KEY `idProd` (`idProd`,`nomeVenditore`);

--
-- Indici per le tabelle `spazidimemoria`
--
ALTER TABLE `spazidimemoria`
  ADD PRIMARY KEY (`idSpazio`);

--
-- Indici per le tabelle `utenti`
--
ALTER TABLE `utenti`
  ADD PRIMARY KEY (`nomeUtente`),
  ADD UNIQUE KEY `email` (`email`);

--
-- Indici per le tabelle `venditori`
--
ALTER TABLE `venditori`
  ADD PRIMARY KEY (`nomeUtente`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `file`
--
ALTER TABLE `file`
  MODIFY `idFIle` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT per la tabella `prodotti`
--
ALTER TABLE `prodotti`
  MODIFY `idProd` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT per la tabella `richieste`
--
ALTER TABLE `richieste`
  MODIFY `idRichiesta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT per la tabella `spazidimemoria`
--
ALTER TABLE `spazidimemoria`
  MODIFY `idSpazio` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `file`
--
ALTER TABLE `file`
  ADD CONSTRAINT `file_ibfk_1` FOREIGN KEY (`idSpazio`) REFERENCES `spazidimemoria` (`idSpazio`);

--
-- Limiti per la tabella `fileinprodottidigitali`
--
ALTER TABLE `fileinprodottidigitali`
  ADD CONSTRAINT `fileinprodottidigitali_ibfk_1` FOREIGN KEY (`idFile`,`idSpazio`) REFERENCES `file` (`idFIle`, `idSpazio`),
  ADD CONSTRAINT `fileinprodottidigitali_ibfk_2` FOREIGN KEY (`idProd`,`nomeVenditore`) REFERENCES `prodottidigitali` (`idProd`, `nomeVenditore`);

--
-- Limiti per la tabella `prodotti`
--
ALTER TABLE `prodotti`
  ADD CONSTRAINT `prodotti_ibfk_1` FOREIGN KEY (`nomeVenditore`) REFERENCES `venditori` (`nomeUtente`);

--
-- Limiti per la tabella `prodottidigitali`
--
ALTER TABLE `prodottidigitali`
  ADD CONSTRAINT `prodottidigitali_ibfk_1` FOREIGN KEY (`idProd`,`nomeVenditore`) REFERENCES `prodotti` (`idProd`, `nomeVenditore`);

--
-- Limiti per la tabella `prodottifisici`
--
ALTER TABLE `prodottifisici`
  ADD CONSTRAINT `prodottifisici_ibfk_1` FOREIGN KEY (`idProd`,`nomeVenditore`) REFERENCES `prodotti` (`idProd`, `nomeVenditore`);

--
-- Limiti per la tabella `prodottivenduti`
--
ALTER TABLE `prodottivenduti`
  ADD CONSTRAINT `prodottivenduti_ibfk_1` FOREIGN KEY (`idProd`,`nomeVenditore`) REFERENCES `prodotti` (`idProd`, `nomeVenditore`),
  ADD CONSTRAINT `prodottivenduti_ibfk_2` FOREIGN KEY (`nomeCliente`) REFERENCES `utenti` (`nomeUtente`);

--
-- Limiti per la tabella `richieste`
--
ALTER TABLE `richieste`
  ADD CONSTRAINT `richieste_ibfk_1` FOREIGN KEY (`nomeCliente`) REFERENCES `utenti` (`nomeUtente`),
  ADD CONSTRAINT `richieste_ibfk_2` FOREIGN KEY (`idProd`,`nomeVenditore`) REFERENCES `prodotti` (`idProd`, `nomeVenditore`);

--
-- Limiti per la tabella `venditori`
--
ALTER TABLE `venditori`
  ADD CONSTRAINT `venditori_ibfk_1` FOREIGN KEY (`nomeUtente`) REFERENCES `utenti` (`nomeUtente`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
