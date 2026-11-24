# 00 — Preparare l'ambiente di lavoro

Scopo della configurazione è che tu possa eseguire, dal terminale, il comando:

```
g++ --version
```

e vedere comparire il numero di versione del compilatore.

---

## 1. Dove lavorare: una cartella "semplice"

I compilatori più vecchi su Windows si confondono con cartelle che contengono **spazi, accenti o caratteri strani** (per esempio `Documenti e impostazioni` o `Attività`).
Crea una cartella di lavoro con un percorso semplice, per esempio:

```
Z:\cpp
```

Copiaci dentro la cartella `Kit_studenti` che ti ha dato l'insegnante: contiene `template.cpp`, `template_gara.cpp`, `check.bat` e la cartella nascosta `.vscode`.


---

## 2. Trovare il compilatore (MinGW)

Sui computer della scuola Code::Blocks è installato insieme a MinGW, il pacchetto che contiene `g++`. Cerca il file `g++.exe` in una di queste cartelle:

```
C:\Program Files\CodeBlocks\MinGW\bin
C:\Program Files (x86)\CodeBlocks\MinGW\bin
```

La cartella `bin` che contiene `g++.exe` è quella che ci serve. Annotala.

Perché non funziona ancora `g++` dal terminale? Perché Windows cerca i programmi solo nelle cartelle elencate nella variabile **PATH**, e questa cartella non c'è. Dobbiamo aggiungerla.

---

## 3. Aggiungere MinGW al PATH (senza essere amministratore)

Ogni utente può modificare il **proprio** PATH, senza diritti di amministratore.

### Metodo A — Interfaccia grafica

1. Premi il tasto Windows e scrivi: **Modifica le variabili d'ambiente relative all'account**.
2. Nella lista **Variabili utente** seleziona `Path` e premi **Modifica**.
3. Premi **Nuovo** e incolla il percorso della cartella `bin` trovata prima, per esempio
   `C:\Program Files\CodeBlocks\MinGW\bin`.
4. Conferma con **OK** in tutte le finestre.

### Metodo B — Una riga di PowerShell

Apri PowerShell (non serve "come amministratore") ed esegui, **adattando il percorso**:

```powershell
$p = [Environment]::GetEnvironmentVariable('Path','User')
[Environment]::SetEnvironmentVariable('Path', "$p;C:\Program Files\CodeBlocks\MinGW\bin", 'User')
```

### Verifica

**Chiudi e riapri** il terminale (e VS Code: le modifiche al PATH vengono lette solo all'avvio dei programmi). Poi scrivi:

```
g++ --version
```

Dovresti vedere una riga con il numero di versione (per esempio `... 8.1.0`). Se compare *"g++ non è riconosciuto come comando"*, controlla di aver copiato la cartella `bin` giusta e di aver riaperto il terminale.

> **Piano B senza PATH.** Se proprio non riesci a modificare il PATH, apri `Kit_studenti\.vscode\tasks.json` e nella voce `"command": "g++"` scrivi il percorso completo, per esempio `"C:\\Program Files\\CodeBlocks\\MinGW\\bin\\g++.exe"` (le barre rovesciate vanno raddoppiate).

---

## 4. Il processo: dal codice al programma in esecuzione

Un file `.cpp` è solo testo. Per diventare un programma passa per più fasi:

```
 prog.cpp ──► preprocessore ──► compilatore ──► assemblatore ──► linker ──► prog.exe
 (testo)     (#include,         (C++ → assembly)  (→ codice       (collega   (eseguibile)
              #define)                            macchina)       le librerie)
```

`g++` esegue tutte le fasi insieme, ma puoi fermarlo a metà e guardare cosa succede. Scrivi un file `ciao.cpp` e prova:

| Comando | Cosa fa | Risultato |
|---|---|---|
| `g++ -E ciao.cpp -o ciao.ii` | solo preprocessore | `ciao.ii` è lunghissimo: dentro ci sono tutte le righe di `<iostream>` |
| `g++ -S ciao.cpp` | fino all'assembly | `ciao.s` contiene istruzioni leggibili |
| `g++ -c ciao.cpp` | fino al codice macchina | `ciao.o`, non ancora eseguibile |
| `g++ ciao.cpp -o ciao.exe` | tutto, con il linker | `ciao.exe` si può lanciare |

Per eseguire il programma: `ciao.exe` (o `.\ciao.exe` in PowerShell).

### I quattro tipi di errore

| Tipo | Quando compare | Esempio |
|---|---|---|
| **Errore di compilazione** | `g++` si ferma, nessun `.exe` | manca un `;`, variabile non dichiarata |
| **Errore del linker** | `g++` si ferma alla fine | funzione dichiarata ma mai scritta (`undefined reference`) |
| **Errore a runtime** | il programma parte e si blocca | divisione per zero, accesso fuori da un vettore |
| **Errore logico** | il programma finisce, ma il risultato è sbagliato | `<` al posto di `<=` |

Leggi **sempre il primo errore** (è quello vero: i successivi spesso ne sono una conseguenza) e guarda il numero di riga.

### I flag che useremo

```
g++ -std=c++17 -O2 -Wall -Wextra -g prog.cpp -o prog.exe
```

| Flag | Significato |
|---|---|
| `-std=c++17` | usa lo standard C++17 |
| `-O2` | ottimizza (programma più veloce, come nelle gare) |
| `-Wall -Wextra` | mostra i **warning**: non sono errori ma quasi sempre indicano un bug. Non ignorarli! |
| `-g` | aggiunge informazioni per il debugger |

---

## 5. VS Code

### 5.1 Estensioni

Apri VS Code → icona **Estensioni** (`Ctrl+Shift+X`) e installa:

- **C/C++** (Microsoft): colorazione, suggerimenti e debugger.

Se non puoi installare estensioni, puoi comunque compilare dal terminale integrato e usare le *task* qui sotto.

### 5.2 Aprire la cartella di lavoro

`File → Apri cartella...` e scegli `Z:\cpp\Kit_studenti` (la cartella, non un singolo file: così VS Code legge la cartella `.vscode`).
Se compare la domanda *"Consideri attendibili gli autori?"*, rispondi di sì.

### 5.3 Compilare ed eseguire

Apri un file `.cpp`, poi `Ctrl+Shift+P` → **Tasks: Run Task** e scegli:

| Task | A cosa serve |
|---|---|
| **Compila** (anche `Ctrl+Shift+B`) | crea `nome.exe` accanto al sorgente; mostra errori e warning |
| **Compila ed esegui** | compila e lancia il programma nel terminale |
| **Compila ed esegui con input.txt** | come sopra, ma legge l'input dal file `input.txt` nella stessa cartella |
| **Compila in modalità debug** | aggiunge controlli che segnalano gli accessi fuori dai `vector` |

> **Il terminale di Windows.** Nel terminale PowerShell il simbolo `<` (redirezione dell'input) **non funziona**. Le task sono già impostate per usare `cmd.exe`. Se lanci a mano, usa il terminale **Command Prompt** (menu a tendina `+` nel pannello terminale) e scrivi `prog.exe < input.txt`.

### 5.4 Debugger

`F5` compila e avvia il programma con il debugger (gdb di MinGW). Metti un **punto di interruzione** cliccando a sinistra del numero di riga; con `F10` avanzi di una riga alla volta e nel pannello a sinistra vedi i valori delle variabili.

---

## 6. Alternativa: Code::Blocks

Se VS Code dà problemi, Code::Blocks è un buon piano B.

1. **File → New → Empty file** (oppure apri un `.cpp` esistente) e salva come `nome.cpp`.
2. **Settings → Compiler → Global compiler settings → Compiler settings**: spunta
   - `Have g++ follow the C++17 ISO C++ language standard [-std=c++17]`
   - `Enable all common compiler warnings [-Wall]` e `Enable extra compiler warnings [-Wextra]`
3. **Build and run** con `F9`.
4. Per leggere un `input.txt`: se lavori con un *progetto* (`File → New → Project → Console application`), imposta in **Project → Properties → Build targets** il campo *Execution working dir* sulla cartella del progetto e metti `input.txt` lì.

---

## 7. Il tuo primo programma

Salva questo codice come `ciao.cpp` e compilalo:

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Ciao, mondo!" << endl;
    return 0;
}
```

Esegui `ciao.exe`: deve comparire `Ciao, mondo!`.

**Provare per credere:**
1. togli il `;` dopo `endl` e ricompila: leggi il messaggio d'errore;
2. cambia `cout` in `cot`: che errore ottieni?
3. aggiungi, prima di `return`, la riga `int x;` e ricompila con `-Wall`: compare un warning?

---

## 8. Se qualcosa non va

| Sintomo | Causa probabile | Rimedio |
|---|---|---|
| `g++ non è riconosciuto...` | PATH non impostato o terminale non riaperto | ripeti il punto 3 e riavvia VS Code |
| `fatal error: bits/stdc++.h: No such file` | compilatore non MinGW/GCC | usa il `g++` di MinGW, non un altro |
| `cannot open output file ...exe: Permission denied` | il programma precedente è ancora in esecuzione | chiudi la finestra del programma (o `Ctrl+C`) |
| Errori su file con accenti o spazi nel percorso | cartella di lavoro "scomoda" | sposta tutto in `Z:\cpp` |
| Il programma si apre e si chiude subito | l'`.exe` è stato lanciato con doppio clic | eseguilo dal terminale |
| `prog.exe < input.txt` dà errore in PowerShell | PowerShell non supporta `<` | usa Command Prompt, oppure `Get-Content input.txt \| .\prog.exe` |
