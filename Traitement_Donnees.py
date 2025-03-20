# -*- coding: utf-8 -*-
"""
Projet Tutoré Paéro 2024           Programme de traitement de données
ARNOULT Victor
FUHREL Sarah
GAUTIER Kassandra

@author: Dell
"""

import pandas as pd
import matplotlib.pyplot as plt

# Charger le fichier CSV
file_path = "DATA.csv"  # Assurez-vous du bon chemin d'accès
df = pd.read_csv(file_path, sep=";", skiprows=1, engine="python")

# Calcul des valeurs corrigées
df["P125corr"] = 1.3386 * df["P125 (Pa)"] + 4.5028
df["P500corr"] = 0.2816 * df["P500 (Pa)"] - 0.5152

"""
# Calcul du temps entre chaque mesure
df["Delta_Time (ms)"] = df["Timestamp (ms)"].diff()


# Affichage de la première ligne des données
print("Première ligne des données :")
print(df.iloc[0])
"""

# Création des graphiques
plt.figure(figsize=(12, 8))

# Graphique P125corr en fonction du temps
plt.subplot(3, 2, 1)
plt.plot(df["Timestamp (ms)"], df["P125corr"], label="P125corr", color='b')
plt.xlabel("Timestamp (ms)")
plt.ylabel("P125corr (Pa)")
plt.title("P125corr en fonction du temps")
plt.legend()

# Graphique P500corr en fonction du temps
plt.subplot(3, 2, 2)
plt.plot(df["Timestamp (ms)"], df["P500corr"], label="P500corr", color='r')
plt.xlabel("Timestamp (ms)")
plt.ylabel("P500corr (Pa)")
plt.title("P500corr en fonction du temps")
plt.legend()

# Graphique (Mx, My, Mz) en fonction du temps
plt.subplot(3, 2, 3)
plt.plot(df["Timestamp (ms)"], df["Mx (µT)"], label="Mx", color='g')
plt.plot(df["Timestamp (ms)"], df["My (µT)"], label="My", color='m')
plt.plot(df["Timestamp (ms)"], df["Mz (µT)"], label="Mz", color='y')
plt.xlabel("Timestamp (ms)")
plt.ylabel("Champ Magnétique (µT)")
plt.title("Mx, My, Mz en fonction du temps")
plt.legend()

# Graphique (Ax, Ay, Az) en fonction du temps
plt.subplot(3, 2, 4)
plt.plot(df["Timestamp (ms)"], df["Ax (m/s²)"], label="Ax", color='g')
plt.plot(df["Timestamp (ms)"], df["Ay (m/s²)"], label="Ay", color='m')
plt.plot(df["Timestamp (ms)"], df["Az (m/s²)"], label="Az", color='y')
plt.xlabel("Timestamp (ms)")
plt.ylabel("Accélération (m/s²)")
plt.title("Ax, Ay, Az en fonction du temps")
plt.legend()

# Graphique (Gx, Gy, Gz) en fonction du temps
plt.subplot(3, 2, 5)
plt.plot(df["Timestamp (ms)"], df["Gx (°/s)"], label="Gx", color='g')
plt.plot(df["Timestamp (ms)"], df["Gy (°/s)"], label="Gy", color='m')
plt.plot(df["Timestamp (ms)"], df["Gz (°/s)"], label="Gz", color='y')
plt.xlabel("Timestamp (ms)")
plt.ylabel("Vitesse angulaire (°/s)")
plt.title("Gx, Gy, Gz en fonction du temps")
plt.legend()

plt.tight_layout()
plt.show()


# Affichage de la première ligne du fichier
with open("DATA.csv", "r", encoding="utf-8") as f:
    first_line = f.readline().strip()  # Lire la première ligne

print("Première ligne du fichier :", first_line)
"""
On pourrait mieux la mettre en forme pour une meilleure lisibilité
"""

