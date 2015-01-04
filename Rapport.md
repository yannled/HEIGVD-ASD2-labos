ASD2 - labo 4 - Rapport
=====================

- HES-SO // HEIG-VD // ASD2 - Algorithmes et structures de données // **Prof. Olivier CUISENAIRE**
- MM. **Léonard BERNEY et Valentin MINDER**

Introduction
----------------------


Problématiques
------------------


Réponses aux questions posées.
------------------

1. Quel est le chemin le plus court entre Genève et Emmen ? Quelles sont les villes traversées ?

Le plus court chemin mesure `238 km` et traverse les villes de Nyon, Morges, Lausanne, Chiètres et Berne.

2. Mêmes questions entre Lausanne et Bâle ?

Le plus court chemin mesure `185 km` et traverse les villes de Yverdon-les-Bains, Neuchatel, Bienne et Delémont.

3. Quel est le chemin le plus rapide entre Genève et Emmen en passant par Yverdon ? Quelles sont les villes traversées ?

Le chemin chemin le plus rapide prend `72 minutes` (1 heure 12 min) et traverse les villes 
de Nyon, Morges, Lausanne, Yverdon-les-Bains, Neuchatel, Bienne et Berne.

4. Mêmes questions mais en passant par Vevey ?

Le chemin chemin le plus rapide prend `68.5 minutes` (1 heure 8 min 30 secondes) et traverse les villes 
de Nyon, Morges, Lausanne, Vevey, Fribourg et Berne.

5. Quelles routes doivent être rénovées ? Quel sera le coût de la rénovation de ces routes ?

Le réseau comptant `n = 27` villes, les `n - 1 = 26` tronçons suivants doivent être rénovés, 
dans l'ordre de cout minimal.

Morges - Lausanne (105 MCHF), Vevey - Montreux (105 MCHF), Langenthal - Olten (119 MCHF), 
Augst - Basel (150 MCHF), Burgdorf - Langenthal (175 MCHF), Bienne - Soleure (175 MCHF), 
Berne - Burgdorf (225 MCHF), Chietres - Neuchatel (232 MCHF), Montreux - Monthey (300 MCHF), 
Monthey - Martigny (300 MCHF), Soleure - Burgdorf (300 MCHF), La Chaux-De-Fonds - Bienne (315 MCHF), 
Neuchatel - La Chaux-De-Fonds (330 MCHF), Basel - Delemont (344 MCHF), Geneve - Nyon (345 MCHF), 
Delemont - Bienne (350 MCHF), Lausanne - Vevey (375 MCHF), Nyon - Morges (375 MCHF), 
Lausanne - Yverdon-Les-Bains (375 MCHF), Berne - Thun (390 MCHF), 
Yverdon-Les-Bains - Neuchatel (396 MCHF), Martigny - Sion (405 MCHF), 
Fribourg - Berne (480 MCHF), Thun - Brienz (624 MCHF), Emmen - Berne (630 MCHF) ainsi que Olten - Baden (675 MCHF).

Le cout total est de `8585 MCHF`, soit 8.585 milliards de francs suisses. La carte du réseau minimal est annexée.

![réseau a rénover](https://raw.githubusercontent.com/ValentinMinder/ASD/b0cfaa79f0a498ed50b6eddebad2faad55ab950a/Question5-reseau.png?token=AFPQ76MwsZ7eqLSnSLpvfnYyyn7W6Mcrks5UsraDwA%3D%3D)


Conclusion
------------------

