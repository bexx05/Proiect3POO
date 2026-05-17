# Review– Jocul Vieții al lui Conway (C++)

Obiectivul principal al acestui proiect a fost implementarea jocului **Conway’s Game of Life**, definit de John Conway. Am utilizat o clasă de tip template (**GenerationLog**) și 3 șabloane de proiectare (design patterns): **Observer**, **Factory**, **Singleton**. Aceste decizii de design au fost luate pentru a crește în mod considerabil extensibilitatea, modularitatea și posibilitatea de configurare a întregului sistem.

---

## Clasa Template – GenerationLog

O schimbare majoră și extrem de relevantă în ceea ce privește implementarea tehnică a proiectului este legată de introducerea clasei șablon (template class) denumită **GenerationLog<T>**. Această componentă a fost concepută să fie complet independentă de logica principală a jocului (fiind relativ izolată, a fost mai ușor să modific codul). **GenerationLog<T>** reprezintă o entitate pură și generică, capabilă să gestioneze date de orice tip care respectă constrângerile de utilizare.

Rolul principal al acestei clase este de a înregistra un istoric al valorilor de tip **T**, utilizând o structură de date internă de tip **std::vector<T>**. Această structură reprezintă atributul principal al clasei și depinde în mod direct de argumentul șablon furnizat la instanțiere. Un aspect tehnic important este utilizarea câmpului numit **maxSize_**, care este utilizat pentru a configura numărul maxim de valori ce pot fi stocate simultan în memorie. Prin această abordare, ne asigurăm că instanța clasei funcționează în mod similar unui **buffer circular (ring buffer)**, în care cea mai veche valoare este eliminată automat din vector imediat ce capacitatea maximă de stocare este atinsă. Această strategie de gestionare a memoriei garantează faptul că aplicația funcționează eficient chiar și în cazul unor simulări de lungă durată, în care datele despre fiecare generație trebuie salvate pentru analize ulterioare.

Funcțiile membre ale clasei, respectiv **record()**, **latest()**, **minValue()** și **maxValue()**, depind toate în mod explicit de argumentul șablon **T**. Funcția **record()** este proiectată să accepte un argument de tip **const T&** (referință constantă către **T**), asigurând astfel performanța prin evitarea copierii inutile a obiectelor mari. Pe de altă parte, funcțiile **minValue()** și **maxValue()** returnează o valoare de tip **T**, reprezentând extremele statistice ale setului de date colectat.

O altă caracteristică remarcabilă a acestei clase este funcția **filter()**. Aceasta este, la rândul ei, o funcție membră șablon (member function template), fiind parametrizată pe tipul predicatului numit **Pred**. Această implementare demonstrează modul în care șabloanele pot fi imbricate într-o manieră elegantă: **GenerationLog<T>** are o funcție membră care acceptă un argument șablon independent de cel al clasei. În acest context, cel care apelează funcția poate furniza orice obiect apelabil (callable object), cum ar fi o funcție lambda sau un functor, care acceptă o referință **const T&** și returnează o valoare booleană (**bool**). Rezultatul apelului este un **std::vector<T>** care conține exclusiv acele intrări pentru care predicatul furnizat a returnat valoarea **true**. Această funcție este utilizată activ în demonstrația jurnalului de evenimente din fișierul **main.cpp**, având rolul de a afișa toate șirurile de caractere înregistrate care îndeplinesc anumite criterii.

De asemenea, am implementat o funcție șablon independentă (free function template) denumită **average(const GenerationLog<T>&)**. Scopul acesteia este de a calcula media aritmetică a tuturor intrărilor înregistrate în jurnalul de date. Din punct de vedere al execuției, funcția invocă intern metoda **filter()** utilizând un predicat universal pentru a extrage toate intrările disponibile, iar ulterior folosește algoritmul standard **std::accumulate** pentru a calcula suma totală a elementelor. Este esențial de observat că aceasta a fost declarată și definită complet independent de clasa **GenerationLog**, nefiind un membru al acesteia, ceea ce respectă principiul decuplării. Funcția este apelată în **main.cpp** imediat după finalizarea execuției simulării, pentru a prezenta utilizatorului numărul mediu de celule vii care au existat pe parcursul rulării programului.

---
## Specializarea Șablonului pentru GenerationLog **std::string**

Pentru a demonstra utilitatea template-ului, am adăugat o specializare explicită completă a clasei **GenerationLog** pentru tipul **std::string**. Această specializare modifică în mod fundamental comportamentul operatorului de inserție în flux **operator<<**. În timp ce versiunea generică a clasei este optimizată pentru tipuri numerice și afișează valori statistice precum minimul și maximul, versiunea specializată pentru șiruri de caractere imprimă intrările pe rânduri separate.

Această decizie tehnică a fost luată pentru a evita comparațiile lexicografice care ar fi putut genera rezultate confuze în cazul mesajelor de tip text. Șablonul general gestionează tipurile numerice cu output statistic, în timp ce specializarea pentru **std::string** oferă un output secvențial, ușor de citit de către utilizator. Clasa este instanțiată în **main.cpp** cu două tipuri diferite: **int**, pentru a monitoriza numărul de celule vii pe generație, și **std::string**, pentru a înregistra evenimentele semnificative din ciclul de viață al simulării (**simulation started**, **simulation ended**). Cu alte cuvinte, șablonul are multiple tipuri de instanțiere.

---
## Pattern Design 1: **Observer**

În versiunea originală a codului (de la proiectul 2), clasa **Grid** (Rețeaua de celule) era supraîncărcată cu responsabilități, gestionând atât execuția simulării, cât și toate detaliile legate de afișarea datelor. Această structură rigidă însemna că orice adăugare a unui nou sistem de logare sau a unui monitor statistic ar fi necesitat modificarea directă a codului sursă din clasa **Grid**.

Prin introducerea modelului **Observer**, am creat o interfață abstractă numită **ISimulationObserver**, care conține o singură metodă pur virtuală: **onGenerationUpdate(int generation, int livingCells)**. Acum, clasa **Grid** menține intern un vector de pointeri către această interfață (**std::vector<ISimulationObserver*>**) și apelează metoda menționată la finalul fiecărui ciclu de actualizare din funcția **update()**. Un avantaj major este că adăugarea sau eliminarea observatorilor nu mai necesită nicio modificare în clasa **Grid**.

Implementarea concretă utilizată este **ConsoleStatsObserver**, care se ocupă cu afișarea statisticilor generației în terminal la un interval de timp configurabil. Această clasă colaborează, de asemenea, cu modelul **Singleton** pentru a citi tipul actual de celulă din **SimulationConfig::instance()**. Observatorul este înregistrat în **main.cpp** prin apelul **grid.addObserver(&statsObserver)** înainte de pornirea simulării, respectând tiparul standard de conectare a observatorilor. Această abordare este extrem de utilă, deoarece permite adăugarea ulterioară a unor observatori pentru salvarea datelor în fișier sau pentru generarea de grafice fără a altera logica centrală a simulării.

---
## Pattern Design 2: **Factory**

Codul original folosea funcții lambda în **main.cpp** pentru a crea instanțe ale celulelor. Deși această metodă era funcțională, ea nu respecta un tipar formal de proiectare și nu permitea o selecție polimorfică elegantă a fabricilor de obiecte. Noul design introduce interfața abstractă **ICellFactory**, care definește metoda **create(bool alive)**, returnând un pointer inteligent de tip **std::shared_ptr<Cell>**.

Am implementat trei fabrici concrete: **ConwayCellFactory**, **HighLifeCellFactory** și **DayNightCellFactory**. Fiecare dintre acestea gestionează logica specifică de creare pentru tipul său de celulă. Metoda **Grid::populate()** a fost revizuită pentru a accepta o referință către **const ICellFactory&**, clarificând astfel dependența față de fabrică și sporind siguranța tipurilor (**type-safety**). În funcția **main**, fabrica adecvată este aleasă pe baza input-ului de la utilizator și stocată într-un **std::unique_ptr<ICellFactory>**. Această configurare formală face legătura cu ierarhia existentă de clase, permițând extinderea jocului cu noi tipuri de celule prin simpla adăugare a unei noi clase de celulă și a unei fabrici corespondente, fără a modifica logica din **Grid**.

---
## Pattern Design 3: **Singleton**

Clasa **SimulationConfig** utilizează modelul **Singleton** pentru a oferi un punct de acces global la parametrii simulării, cum ar fi numărul de rânduri, coloane, tipul celulei și probabilitatea de viață inițială. Constructorul este privat, iar constructorul de copiere și operatorul de atribuire sunt șterși (**deleted**), garantând unicitatea instanței. Accesul se realizează prin metoda statică **instance()**, care returnează o referință către o variabilă statică locală.

În **main.cpp**, acest **Singleton** este configurat imediat după citirea datelor de la utilizator. Ulterior, este utilizat în constructorul clasei **Grid** și în **ConsoleStatsObserver**. Utilizarea **Singleton**-ului este justificată aici deoarece configurația simulării este unică și globală în contextul rulării curente a aplicației. Aceasta asigură că toate componentele sistemului lucrează cu același set de date de configurare, evitând erorile de sincronizare a parametrilor.

---
## 5. Bibliografie
* [SFML Documentation](https://www.sfml-dev.org/documentation/2.5.1/)
* [Conway's Game of Life Rules](https://conwaylife.com/wiki/Conway%27s_Game_of_Life)
* [Modern C++ Design Patterns (NVI)](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-Virtual_Interface)
* Tutorial yt https://www.youtube.com/watch?v=daFYGrXq0aw
* Alt tutorial yt https://www.youtube.com/watch?v=9NK5holxvOw
## Concluzie

Modificările aduse acestui proiect îndeplinesc cu succes toate criteriile tehnice stabilite. Clasa **GenerationLog<T>** demonstrează utilizarea corectă a programării generice, de la atribute dependente de tip până la specializări complexe. Funcția **average<T>** completează necesarul de funcții șablon independente. Cele trei modele de proiectare — **Observer**, **Factory Method** și **Singleton** — sunt implementate riguros și aplicate în contexte potrivite temei proiectului, transformând un cod procedural într-un sistem orientat pe obiecte, modular și extrem de ușor de întreținut pe termen lung.
