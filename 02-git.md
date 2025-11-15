# GIT

## Git Commands Zusammenfassung

**Repository Setup:**
- `git clone https://github.com/davemod/25_juce1.git`

**Täglicher Workflow:**
- `git fetch` – Lädt neue Änderungen vom Remote-Repository, ohne sie in den aktuellen Branch zu integrieren.
- `git pull` – Holt neue Änderungen vom Remote-Repository und integriert sie direkt in den aktuellen Branch.
- `git status` – Zeigt den aktuellen Stand der Arbeitskopie, inklusive Änderungen und Staging-Bereich.
- `git add` – Verschiebt ausgewählte Änderungen in den Staging-Bereich, um sie für den nächsten Commit vorzubereiten.
- `git restore --staged` – Entfernt Änderungen aus dem Staging-Bereich, ohne sie aus den Dateien zu löschen.
- `git restore` – Setzt Änderungen in den Arbeitsdateien zurück, die noch nicht zum Staging-Bereich hinzugefügt wurden.
- `git commit -m message` – Erstellt einen Commit mit allen Änderungen, die sich im Staging-Bereich befinden, und versieht ihn mit einer Nachricht.
- `git commit -a -m message` – Fügt alle geänderten und bereits getrackten Dateien automatisch zum Staging-Bereich hinzu und erstellt einen Commit mit Nachricht.

- `git branch` - zeigt den aktuellen Branch an
- `git branch branch_name` - erstellt einen neuen lokalen Branch auf dem Commit, auf den der HEAD zeigt
- `git checkout` - Wechselt den aktuellen Arbeitsstand auf einen anderen Branch, Commit oder Tag.  
    - **Branch:** `git checkout branch_name` – Wechselt zu einem anderen Branch.
    - **Commit:** `git checkout commit_hash` – Setzt den Arbeitsstand auf einen bestimmten Commit (führt zu einem "detached HEAD").
    - **Tag:** `git checkout tag_name` – Wechselt zu einem bestimmten Tag.

- `git push` – Überträgt die lokalen Commits des aktuellen Branches auf das Remote-Repository.
- `git push origin --set-upstream branch_name` – Überträgt den angegebenen lokalen Branch auf das Remote-Repository und richtet ihn als Upstream-Branch ein, sodass zukünftige Pushes und Pulls ohne weitere Angaben möglich sind. Das ist bspw. nötig nach der Erstellung eines neuen lokalen Branchesn mit `git branch branch_name`

**Information & Historie:**
- `git log --graph --oneline` – Zeigt die Commit-Historie als kompakten Graphen mit einer Zeile pro Commit.
- `git log --graph --oneline --all` – Zeigt die Commit-Historie als kompakten Graphen für alle Branches.

**Zurücksetzen:**
- `git reset --soft` – Setzt den HEAD auf einen früheren Commit zurück, behält aber alle Änderungen im Staging-Bereich.
- `git reset --hard` – Setzt den HEAD auf einen früheren Commit zurück und verwirft alle Änderungen im Arbeitsverzeichnis und Staging-Bereich.

**Zusammenführen**
- `git merge branch_name` – Führt den angegebenen Branch in den aktuellen Branch zusammen.
- `git merge --no-ff branch_name` – Erstellt immer einen Merge-Commit, auch wenn ein Fast-Forward möglich wäre.
- `git rebase branch_name` – Überträgt die Commits des aktuellen Branches auf den neuesten Stand des angegebenen Branches.
- `git cherry-pick commit_hash` – Übernimmt einen bestimmten Commit aus einem anderen Branch in den aktuellen Branch.
- `git mergetool` – Startet ein Tool zur Unterstützung bei der Lösung von Merge-Konflikten.
- `git diff` – Zeigt Unterschiede zwischen Dateien, Commits oder Branches, hilfreich bei Konfliktlösung.

**head**
Der HEAD ist ein zentraler Begriff in Git. Er bezeichnet den aktuellen Zeiger auf den Commit, auf dem du gerade arbeitest.

HEAD zeigt normalerweise auf den letzten Commit im aktuellen Branch.
Wenn du einen neuen Commit erstellst, verschiebt sich der HEAD auf diesen neuen Commit.
Bei einem Branch-Wechsel (git checkout branchname) zeigt HEAD auf den neuesten Commit dieses Branches.
Merke:
HEAD ist wie ein Lesezeichen, das Git sagt, wo du dich gerade in der Historie befindest.

Beispiel:
Wenn du git log ausführst, ist der oberste Commit der, auf den HEAD zeigt.

Detached HEAD:
Wenn du einen bestimmten Commit auscheckst (z.B. git checkout <commit-hash>), zeigt HEAD direkt auf diesen Commit und nicht mehr auf einen Branch. Das nennt man einen "detached HEAD".

Zusammengefasst:
HEAD = aktueller Standpunkt im Git-Verlauf.