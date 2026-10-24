# Captures de la séance 3 — exports bruts WaveForms

Binôme 11 (SALOMON & VOISSIER), séance du 14/10/2026, Analog Discovery 2 (SN 210321B211F2).
Ce sont les trois fichiers nommés dans la colonne « Fichier » de la fiche de relevés.

| Fichier | Mode | Heure de capture | I moyen sur la fenêtre | I moyen sur un nombre entier de cycles |
|---|---|---|---|---|
| `normal_mode.csv` | clignotement 550 ms / 2000 ms | 11:22:10 | 38,68 mA | 38,67 mA (4 périodes) |
| `light_sleep.csv` | même clignotement, light sleep | 11:32:57 | 20,51 mA | 19,90 mA (5 périodes) |
| `deep_sleep.csv` | réveil toutes les 3,75 s | 11:38:41 | 16,22 mA | 16,71 mA (1 cycle) |

Réglages communs : 800 éch./s, 8000 points (fenêtre de 10 s), voie Math `C1 / 1.4` où 1,4 Ω est la
valeur réelle de la résistance de mesure relevée au multimètre, alimentation V+ à 5 V configurés
pour 4,97 V mesurés.

`normal_mode.csv` comporte trois colonnes (temps, voie 1 en volts, Math en ampères) ; les deux autres
n'en ont que deux (temps, Math en ampères). La dernière colonne est toujours le courant, en ampères.

La fenêtre de 10 s ne contient un nombre entier de périodes pour aucun des trois modes, ce qui biaise
la moyenne — nettement en deep sleep, dont la période réelle entre deux réveils vaut 4,369 s et non
les 3,75 s programmés. C'est la raison de l'écart entre les deux dernières colonnes du tableau.
