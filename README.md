Choix des technologies
API Graphique retenue : DirectX 11

DirectX 11 a été choisi comme API graphique principale pour le développement du moteur.
Ce choix repose sur un bon compromis entre complexité, performances et temps de développement.
L’API permet une prise en main rapide tout en restant suffisamment bas niveau pour comprendre et implémenter les concepts fondamentaux d’un moteur 3D (pipeline graphique, gestion des ressources, shaders, etc.).

De plus, DirectX 11 s’intègre naturellement dans l’écosystème Microsoft, facilitant l’utilisation des outils de développement et de débogage sous Windows.

APIs graphiques non retenues :

DirectX 12 : API très bas niveau nécessitant une gestion explicite de la mémoire et de la synchronisation CPU/GPU, augmentant fortement la complexité et le risque de dépassement du périmètre du projet.

OpenGL : API plus ancienne et moins représentative des pipelines graphiques modernes, avec une abstraction plus élevée et un modèle de fonctionnement moins adapté à une architecture moteur moderne.

Vulkan : API moderne et performante, mais dont la courbe d’apprentissage et la complexité d’implémentation sont trop élevées au regard du temps imparti pour le projet.

API Physique retenue : Jolt Physics

Jolt Physics a été choisie pour la gestion de la physique du moteur en raison de son excellente performance, de son API moderne et de sa simplicité d’intégration dans un moteur C++.
La bibliothèque est conçue pour être multithreadée, cache-friendly et orientée performance, ce qui correspond aux objectifs du projet.

Elle offre également une bonne flexibilité dans la configuration des collisions et des comportements physiques, tout en restant plus légère et accessible que certaines solutions industrielles.

APIs physiques non retenues :

PhysX : bibliothèque puissante mais orientée usage industriel, avec une API lourde et moins flexible pour un moteur pédagogique, ainsi qu’une intégration plus complexe.

Bullet : moteur physique éprouvé mais basé sur une API plus ancienne, moins optimisée pour les architectures modernes et nécessitant davantage de travail pour obtenir une intégration propre et performante.

API Audio retenue : FMOD

FMOD a été retenue pour la gestion du son en raison de sa robustesse, de sa facilité d’intégration et de son utilisation courante dans l’industrie du jeu vidéo.
Elle permet une gestion avancée de l’audio (spatialisation, événements, paramètres, bus audio) tout en restant accessible pour un projet de moteur étudiant.

APIs audio non retenues :

MiniAudio et OpenAL : solutions plus bas niveau nécessitant la mise en place manuelle de nombreux systèmes audio (mixage, gestion des événements, spatialisation).

Wwise : middleware complet mais trop lourd et complexe pour le périmètre du projet, avec un pipeline externe peu adapté à un moteur pédagogique.





