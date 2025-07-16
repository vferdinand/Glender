# Glender
---

#  3D Renderer

Dieses Tool rendert 3D-Objekte aus `.obj`-Dateien in verschiedenen Auflösungen und Modi. Es unterstützt verschiedene Darstellungsarten wie klassische Darstellung oder rotierende "Spinner"-Animationen.

## Kompilieren

```bash
make
```

---

## Verwendung

```bash
./main <obj-datei> [auflösung] [modus] [frames]
```

* `<obj-datei>`: Pfad zur `.obj`-Datei, die gerendert werden soll.
* `[auflösung]`: (optional) Render-Auflösung. Standard: `fullhd`
* `[modus]`: (optional) Render-Modus. Standard: `classic`
* `[frames]`: (nur für Modus `frames`) Anzahl der Frames

---

## Auflösungen

| Name   | Beschreibung       | Skalierung |
| ------ | ------------------ | ---------- |
| mini   | Sehr klein         | 2          |
| test   | Klein (Testzwecke) | 4          |
| fullhd | Standard (1080p)   | 12         |
| 2k     | Kinoauflösung      | 16         |
| 4k     | Ultra HD           | 24         |
| 8k     | Sehr hoch          | 48         |
| 16k    | Extrem hoch        | 96         |

---

## Modi

| Modus                  | Beschreibung                                  |
| ---------------------- | --------------------------------------------- |
| `classic`              | Statisches Rendering                          |
| `spinner`              | Rotation eines Fahrzeugs                      |
| `frames`               | Frame-by-Frame-Export einer Spinner-Animation |
| `cottage`              | Statische Cottage-Ansicht (falls vorhanden)   |
| `cottagespinner`       | Cottage-Spinner                               |
| `cottagespinnerframes` | Cottage-Frames mit Rotation                   |

---

## Beispielnutzung

### Klassisches Rendering (Fokus-Modus)

```bash
./main Car.obj fullhd classic
```

* Lädt `Car.obj`
* Rendert in Full HD
* Verwendet den statischen `classic`-Modus (z. B. Fahrzeug- oder Architekturansicht)

### Spinner-Beispiel

```bash
./main Car.obj test spinner
```

* Lädt `car.obj`
* Nutzt die `test`-Auflösung für schnelle Vorschau
* Zeigt das Modell in einer rotierenden `spinner`-Ansicht

---

## Beispiel für Frames (nur bei `frames`-Modus)

```bash
./main Car.obj mini cottagespinnerframes 20
```

* Erstellt 20 Einzelbilder einer Cottage-Rotation in kleiner Auflösung

---

##  Fehlerbehandlung

* **Unbekannter Modus**: Es wird eine Fehlermeldung angezeigt, wenn der Modus nicht erkannt wird.
* **Fehlende Frames**: Bei Modus `cottagespinnerframes` muss ein `frames`-Wert angegeben werden.
* **Ungültige Auflösung**: Fällt zurück auf `fullhd`, wenn eine ungültige Angabe gemacht wird.

---


## Hinweis

[Abgabe Dokument](https://docs.google.com/document/d/18JriSh_IYwQzvJ9Mc-a5ljyjvrl6McUFQcZskvrGRxI/edit?usp=sharing)
Beispiel Bilder und Performance Vergleiche.

---

Wenn du möchtest, kann ich dir die README auch direkt als Datei ausgeben. Sag einfach Bescheid!
