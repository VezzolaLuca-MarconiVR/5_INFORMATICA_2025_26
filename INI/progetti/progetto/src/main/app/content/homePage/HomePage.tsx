import logo from "@images/EKHOIKOS!.svg";
import mountainImage from "@images/mountains-landscape.jpg";
import containersImage from "@images/containers.jpg";

function HomePage() {
  return (
    <>
      <section id="logo">
        <img
          width="80%"
          src={logo}
          style={{ margin: "5vh", maxWidth: "1700px" }}
        />
      </section>

      <section className="covering-section center-both primary-muted-bg">
        <div className="section-wrapper padding-sides light-bg rounded-corners">
          <h1>
            Cos'è <b>Ekhoikos</b>?
          </h1>
          <p>
            Ekhoikos è una piattaforma di e-commerce che promuove i piccoli
            imprenditori che producono prodotti artigianali. Qui ognuno è libero
            di creare qualsiasi cosa, che sia un prodotto fisico o digitale,
            sfruttando le proprie capacità, e utilizzando materiali
            ecosostenibili e ricialati, portando prodotti di qualità e non
            inquinanti nel proprio mercato locale. Per queste caratteristiche
            abbiamo deciso di dare un... soprannome a chi farà di Ekhoikos il
            suo negozio personale: noi li chiamiamo gli "eco-artigiani"!
          </p>

          <h2>I nostri obbiettivi:</h2>
          <p>
            Tenendo molto all'ecosostenibilità e alla preservazione
            dell'ambiente, abbiamo deciso di basare questo progetto su dei
            pilastri fondamentali:
          </p>
          <ol className="vertical-small-margin-children">
            <li>
              <h3>
                <b>"CHILOMETRO ZERO"</b>
              </h3>
              <p>
                I prodotti visualizzati nel negozio saranno ordinati in base
                alla distanza dal venditore;
              </p>
            </li>
            <li>
              <h3>
                <b>PRODOTTI SOSTENIBILI</b>
              </h3>
              <p>
                I materiali utilizzati nella produzione (nel caso di prodotti
                fisici) hanno un impatto fondamentale nella valutazione da parte
                degli utenti, favorendo materiali non inquinanti, poco
                raffinati, e anche materiali riciclati;
              </p>
            </li>
            <li>
              <h3>
                <b>SOSTEGNO VERSO LE FONDAZIONI</b>
              </h3>
              <p>
                All'acquisto di un prodotto, il 5% del ricavato viene donato a
                una o più fondazioni o associazioni a stampo ecologista scelte
                dall'utente.
              </p>
            </li>
          </ol>
        </div>
      </section>

      <section className="covering-section center-both">
        <div className="section-wrapper">
          <div style={{ width: "100%", margin: "auto" }}>
            <h1>
              La <i>nostra</i> missione
            </h1>
          </div>
          <div
            style={{
              width: "100%",
              display: "flex",
              justifyContent: "space-evenly",
            }}
          >
            <div className="card">
              <h2>Perchè tutto questo?</h2>
              <p>
                La nascita di Ekhoikos è dovuta ad una necessità che spesso è
                stata colmata male o totalmente ignorata: la necessità di uno
                spazio che permetta all'attività artigianale di fiorire, andando
                controcorrente rispetto tutto il resto del mondo, che fin dalla
                prima rivoluzione industriale ha portato all'erosione le
                fondamenta dell'hand-made, affossando i venditori locali e anche
                chi fa tutto ciò solo per hobbi. Questo è un tentativo che si è
                realizzato al suo pieno potenziale, e ciò è dovuto soprattutto a
                voi.
              </p>
            </div>
            <div className="card">
              <h2>E la qualità dei prodotti?</h2>
              <p>
                Ogni singolo prodotto, digitale o fisico che sia, può essere
                valutato dagli utenti che lo acquistano in due misure:
              </p>
              <ul>
                <li>
                  Quanto li ha soddisfati la qualità di quel prodotto (stelle)
                </li>
                <li>
                  Quanto, secondo loro, i materiali utilizzati sono
                  ecosostenibili (eco-punti)
                </li>
              </ul>
              <p>
                Sono entrambe valutazioni fatte su una scala da 1 a 5, con
                incrementi di mezzo punto alla volta (come le "stelline" di cui
                siamo abituati). Gli eco-punti, come le stelle, aiutano gli
                utenti a navigare per trovare i migliori e più sostenibili
                prodotti nella loro zona.
              </p>
            </div>
            <div className="card">
              <h2>"Dietro le quinte"</h2>
              <p>
                Dietro questa piattaforma ci sono decine di persone che
                monitorano, assistono e migliorano l'esperienza di tutti gli
                utenti, che siano clienti o "eco-artigiani", senza i quali
                Ekhoikos non potrebbe esistere. Ruolo fondamentale è stato
                quello dei fondatori: hanno deciso di prendere una svolta
                rivoluzionaria anche nella progettazione del sito web: ogni
                elemento visivo è stato ideato, creato e posizionato a mano,
                senza l'ausilio di alcuna Intelligenza Artificiale. Questa
                scelta ha permesso la nascita e lo sviluppo di un sito
                meraviglioso e dallo stile unico (e anche con pochissime
                emissioni di CO2!!!).
              </p>
            </div>
          </div>
        </div>
      </section>

      <section
        id="hero-container"
        className="covering-section hero center-both"
        style={{
          backgroundImage: `linear-gradient(rgba(0, 0, 0, 0.5), rgba(0, 0, 0, 0.5)), url(${containersImage})`,
        }}
      >
        <div className="section-wrapper center-x center-y">
          <h3 className="dark-bg-transparent padding rounded-corners">
            Detto ciò, volevamo sfruttare questa pagina anche per sensibilizzare
            sul tema dell'impatto ambientale del trasporto merci in Italia,
            quindi abbiamo preparato una sezione che possa informare tramite
            dati aggiornati provenienti da fonti affidabili, per permettere a
            chiunque di comprendere a fondo i motivi che ci hanno spinto a
            prendere le decisioni che hanno reso Ekhoios quello che è oggi. Se
            avete qualche minuto, e volete capirne qualcosa in più
            sull'argomento, continuate a scollare in basso, fino a raggiungere
            la fine della pagina.
          </h3>
          <p className="padding rounded-corners">
            Grazie - dal team di Ekhoikos.
          </p>
        </div>
      </section>

      <section className="center-both padding-top-bottom">
        <div className="section-wrapper center-x center-y margin-top">
          <h1>
            Introduzione - Un <i>Ekho</i> dal nostro <i>Oikos</i>
          </h1>
          <span>
            Negli ultimi anni, l’impatto ambientale del trasporto delle merci è
            diventato uno dei temi centrali nell’ambito della sostenibilità e
            della transizione ecologica. Le emissioni prodotte dai veicoli
            impiegati per la logistica rappresentano una quota significativa
            dell’inquinamento atmosferico globale e locale, influenzando il
            clima, la qualità dell’aria e la salute pubblica. In questo
            contesto, promuovere il chilometro zero e i prodotti locali non è
            solo una scelta etica, ma si trasforma in una strategia efficace per
            ridurre le emissioni, conservare le risorse e tutelare il
            territorio.
          </span>

          <hr />

          <h1>Emissioni di CO2 nel Trasporto Merci: Stati Attuali e Trend</h1>
          <span>
            Il comparto trasporti incide per circa il
            <b>26% delle emissioni di gas serra totali</b> in Italia, di cui la
            quota relativa al trasporto merci è in progressivo aumento a causa
            sia dell’espansione del commercio che delle crescenti aspettative di
            consegna rapida tipiche dell’e-commerce. Le emissioni di CO2 sono
            fortemente variabili in base al mezzo utilizzato e alla distanza
            coperta. In particolare: -<b>Trasporto su strada (camion):</b>{" "}
            Contribuisce da solo a circa il 24% delle emissioni di CO2 del
            settore trasporti in Italia, risultando la modalità più impattante
            sotto il profilo carbonico. -<b>Trasporto marittimo:</b> È
            efficiente per quantità, ma risulta responsabile di quasi il 3%
            delle emissioni globali di gas serra, con una significativa
            incidenza locale in prossimità dei porti. -
            <b>Trasporto ferroviario:</b> Meno del 2% delle emissioni del
            comparto trasporti pur movimentando oltre il 10% di tutte le merci
            (in tonnellate\*km) in Italia, grazie a un’efficienza energetica
            migliore e al progressivo utilizzo di energia elettrica da fonti
            rinnovabili. -<b>Trasporto aereo:</b> Pur rappresentando meno
            dell’1% del volume trasportato, incide dal 2% al 5% sulle emissioni
            del settore, per via dell’efficienza energetica molto bassa per
            chilogrammo trasportato. I dati evidenziano come
            <b>
              la distanza percorsa e la modalità di trasporto siano i due
              fattori chiave
            </b>
            nel determinare l’impatto ambientale del trasporto merci. Ridurre i
            chilometri percorsi attraverso il supporto a filiere corte e
            prodotti locali diventa quindi una leva fondamentale di
            sostenibilità.
          </span>

          <hr />

          <h1>Emissioni di NOx, PM e Altri Inquinanti Atmosferici</h1>

          <span>
            Le emissioni di CO2 non rappresentano l’unica criticità. Il
            trasporto merci produce anche ossidi di azoto (NOx), particolato
            atmosferico (PM10, PM2.5), ossidi di zolfo (SOx), idrocarburi
            incombusti (HC) ed altre sostanze tossiche che contribuiscono
            all’inquinamento locale nelle zone urbane e rurali. In particolare:
            -<b>NOx (ossidi di azoto):</b> I NOx sono emessi in grandi quantità
            dai motori diesel dei veicoli pesanti e causano fenomeni di smog
            fotochimico e piogge acide, con un impatto negativo su salute e
            ambiente. Nel 2022, circa il 40% dei NOx emessi in Italia era
            attribuibile al trasporto su strada, principalmente autocarri e
            furgoni. - <b>Particolato (PM10 e PM2.5):</b> Il particolato è
            prodotto sia dalla combustione, sia dall’abrasione di pneumatici e
            freni, con gravi conseguenze respiratorie. Camion e mezzi pesanti su
            strada sono responsabili del 25-30% delle emissioni totali di PM
            legate al trasporto. - <b>SOx (ossidi di zolfo):</b> Principalmente
            derivanti dal trasporto marittimo, che utilizza combustibili pesanti
            ad alto tenore di zolfo, aggravando l’inquinamento nelle aree
            portuali. Il ricorso a combustibili fossili e a motori endotermici
            ormai obsoleti alimenta un circolo vizioso di inquinamento
            atmosferico e pressioni sulla salute umana, rendendo urgente
            l’adozione di tecnologie pulite, carburanti meno impattanti e
            strategie di riduzione delle distanze di trasporto.
          </span>

          <hr />
          <h1>
            Conseguenze Ambientali: Clima, Biodiversità, Salute e Territorio
          </h1>
          <h2>Impatti sul Clima</h2>
          <span>
            L’aumento delle emissioni di gas serra legate ai trasporti
            contribuisce in maniera determinante al riscaldamento globale.
            <b>Secondo l’ISPRA</b>, il trasporto merci, soprattutto su gomma,
            costituisce una delle principali fonti di emissioni climalteranti in
            Italia. Questa pressione si manifesta sia a livello globale, con
            l’incremento delle temperature e la modifica del ciclo idrico, sia a
            livello locale, con microclimi urbani alterati e un aumento di
            eventi meteorologici estremi. L’intensificazione della logistica su
            lunga distanza, favorita da modelli globalizzati, amplifica questi
            effetti.
          </span>
          <h2>Impatti sulla Biodiversità e Sull’Ambiente</h2>
          <span>
            Oltre al clima, la logistica delle merci impatta fortemente la
            biodiversità e la qualità degli ambienti naturali e antropici. Le
            infrastrutture di trasporto, come autostrade, ferrovie, porti e
            aeroporti, frammentano gli habitat e creano barriere fisiche per
            molte specie, riducendo la connettività ecologica del territorio.
            Inoltre, le emissioni di NOx e PM contribuiscono all’acidificazione
            dei suoli e delle acque, alterando la composizione degli ecosistemi
            e la qualità delle colture agricole. I rilasci accidentali di
            carburanti, lubrificanti e altre sostanze tossiche incidono
            episodicamente ma in maniera devastante su fiumi, laghi e zone
            costiere.
          </span>
          <h2>Impatti sulla Salute Umana</h2>
          <span>
            Le emissioni prodotte dal trasporto merci sono strettamente connesse
            a una crescita della mortalità prematura da malattie cardiovascolari
            e polmonari, prevalentemente nelle aree urbane prossime a grandi
            arterie di traffico e centri logistici. la{" "}
            <b>European Environment Agency</b>
            stima che migliaia di decessi ogni anno in Italia siano attribuibili
            in modo diretto o indiretto all’esposizione prolungata agli
            inquinanti generati dal traffico merci.
          </span>
          <h2>Impatti Territoriali e Paesaggistici</h2>
          <span>
            La realizzazione e l’espansione di infrastrutture logistiche
            comporta un consumo di suolo costante, con perdita di territorio
            agricolo, alterazione dei paesaggi e incremento della vulnerabilità
            a fenomeni come alluvioni e dissesto idrogeologico. La costruzione
            di nuove strade e centri intermodali contribuisce alla
            cementificazione, alla perdita della biodiversità e a un degrado
            estetico del territorio, spesso irreversibile. Ridurre il raggio di
            distribuzione delle merci tramite filiere locali e sostenere il
            chilometro zero rappresenta quindi una scelta non solo ambientale,
            ma anche di tutela del capitale paesaggistico e naturale nazionale.
          </span>

          <hr />

          <h1>
            Distribuzione Percentuale del Trasporto Merci per Tipologia di
            Veicolo (Italia, 2024-2025)
          </h1>
          <span>
            Analizzare come si suddivide il trasporto delle merci rispetto alle
            diverse modalità è fondamentale per comprendere i margini di
            intervento e scegliere dove concentrare gli sforzi di
            decarbonizzazione. In Italia, secondo ISTAT, Ministero delle
            Infrastrutture e Trasporti (MIT) e recenti aggiornamenti del settore
            logistico, la situazione è la seguente:
          </span>

          <table>
            <thead>
              <tr>
                <th>Mezzo di Trasporto</th>
                <th>% Merci Trasportate (Ton/km)</th>
                <th>% Emissioni CO2</th>
                <th>% Emissioni NOx</th>
                <th>% Emissioni PM10</th>
                <th>Note Principali</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>Camion (Strada)</td>
                <td>54–57%</td>
                <td>85%</td>
                <td>70–80%</td>
                <td>60–70%</td>
                <td>Maggior impatto ambientale</td>
              </tr>
              <tr>
                <td>Treni (Ferrovia)</td>
                <td>12–13%</td>
                <td>2%</td>
                <td>2.5%</td>
                <td>&lt;1%</td>
                <td>Più efficiente e meno inquinante</td>
              </tr>
              <tr>
                <td>Navi (Marittimo)</td>
                <td>29–32%</td>
                <td>11%</td>
                <td>16%</td>
                <td>25–35%</td>
                <td>Alta efficienza per volumi, emissioni locali in porti</td>
              </tr>
              <tr>
                <td>Aerei (Trasporto)</td>
                <td>0.1–0.2%</td>
                <td>2–5%</td>
                <td>1.5%</td>
                <td>2–3%</td>
                <td>Basso volume, altissime emissioni per kg</td>
              </tr>
            </tbody>
          </table>

          <span>
            I valori si riferiscono a stime tra il 2023 e il primo trimestre
            2025, con lievi variazioni dovute all’andamento dei traffici
            internazionali e alla ripresa post-pandemica.
          </span>
          <hr />
          <span>
            Questa tabella mette in evidenza la disparità tra quantità di merci
            trasportate e responsabilità sugli inquinanti atmosferici: I
            <b>camion</b>, pur trasportando poco più della metà delle
            tonnellate*chilometro complessive, generano l’85% delle emissioni di
            CO2 dovute alle merci e la larga parte degli altri inquinanti,
            soprattutto vicino ai centri urbani e lungo i principali assi viari.
            Il <b>trasporto ferroviario</b> risulta estremamente virtuoso: muove
            oltre un decimo delle merci con solo il 2% delle emissioni
            climalteranti, grazie alla trazione prevalentemente elettrica e a
            reti sempre più alimentate da fonti rinnovabili. Il <b>marittimo</b>{" "}
            è fondamentale per i grandi volumi e il trasporto intercontinentale,
            ma va sottolineato che le sue emissioni locali incidono gravemente
            sulle aree portuali, mentre a livello globale la sua efficienza è
            superiore al trasporto stradale per ogni tonnellata*km. L’
            <b>aereo</b> è residuale nei volumi ma estremamente impattante in
            termini specifici di emissioni per chilogrammo trasportato.
          </span>
        </div>
      </section>

      <section
        id="hero-mountains"
        className="covering-section hero center-both"
        style={{
          backgroundImage: `linear-gradient(rgba(0,0,0,0.5), rgba(0,0,0,0.5)), url(${mountainImage})`,
        }}
      >
        <div className="section-wrapper dark-bg-transparent rounded-corners center-x center-y padding">
          <h1>Conclusioni</h1>
          <span>
            Le evidenze e le statistiche raccolte mostrano con chiarezza quanto
            il trasporto delle merci, soprattutto su gomma e sulle lunghe
            distanze, rappresenti una delle principali criticità ambientali per
            l’Italia e per l’Europa.
            <b>
              Promuovere la riduzione delle distanze nei trasporti, favorendo il
              chilometro zero e rilocalizzando le filiere produttive
            </b>
            , consente di abbattere drasticamente le emissioni di CO2, NOx,
            particolato e altri inquinanti, con risvolti positivi anche su
            paesaggio, salute e qualità della vita.
          </span>
          <hr />
          <span>
            Investire in innovazione, intermodalità e tecnologie pulite, oltre a
            sensibilizzare attivamente gli utenti sull’impatto concreto delle
            loro scelte di acquisto, rappresenta la strategia più efficace per
            centrare gli obiettivi di sostenibilità e offrire una reale
            alternativa alla logistica tradizionale ad alto impatto.
          </span>
          <hr />
          <span>
            L’evidenza è chiara:
            <b>
              meno chilometri percorsi dalle merci equivalgono a più salute, più
              ambiente e più valore per le economie locali
            </b>
            . Ora, il futuro della logistica sostenibile dipende anche dalle
            scelte quotidiane di ognuno di noi.
          </span>
        </div>
      </section>
    </>
  );
}

export default HomePage;
