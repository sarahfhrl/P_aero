# -*- coding: utf-8 -*-
"""
Created on Thu Mar  6 15:12:08 2025

@author: Dell
"""
import pandas as pd
import matplotlib.pyplot as plt

# Chemin du fichier Excel
file_path = 'DATA1.xlsx'  # Mets à jour le nom du fichier si besoin

# Charger la première feuille du fichier Excel dans un DataFrame
df = pd.read_excel(file_path, sheet_name=0)

# Afficher les premières lignes du DataFrame pour vérifier le chargement
print(df.head())

# Afficher les statistiques de base
print(df.describe())

# Tracer un graphique des pressions P125 et P500 en fonction du temps
plt.figure(figsize=(10,5))
plt.plot(df["Timestamp (ms)"], df["P125 (Pa)"], label="P125 (Pa)")
plt.plot(df["Timestamp (ms)"], df["P500 (Pa)"], label="P500 (Pa)")
plt.xlabel("Temps (ms)")
plt.ylabel("Pression (Pa)")
plt.title("Évolution des pressions P125 et P500 au cours du temps")
plt.legend()
plt


