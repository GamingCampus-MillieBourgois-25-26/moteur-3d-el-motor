# Technical Design Document (TDD) – El Motor

## Document Header
- **Project Title:** El Motor – C++ Game Engine
- **Version:** 1.0
- **Date:** 2026-02-05
- **Author(s):** Groupe *El Motor* (6 personnes)
- **Context:** Début du développement du moteur

## Revision History
| Date       | Version | Description                              | Author        |
|------------|---------|------------------------------------------|---------------|
| 2026-02-05 | 0.0     | Création initiale du document (TDD)      | El Motor Team |
| 2026-03-05 | 1.0     | Sortie de la première version utilisable | El Motor Team |

---

## 1. Introduction

### 1.1 Purpose
Ce document décrit les choix techniques et l’architecture envisagée et finalement utilisée pour **El Motor**, un moteur de jeu 3D développé en C++. Il a pour objectif de justifier les décisions technologiques prises en début de projet, puis sur les technologies finalement utilisées et de servir de référence tout au long du développement.

### 1.2 Scope
- **Objectif :** Concevoir un moteur de jeu 3D modulaire et pédagogique.
- **Cadre :** Projet académique, développement from scratch en C++.
- **État du projet :** Première sortie, version testable fonctionnelle.

### 1.3 Définitions et acronymes
- **TDD:** Technical Design Document  
- **API:** Application Programming Interface  
- **FPS:** Frames Per Second  

---

## 2. System Overview

### 2.1 Description générale
El Motor est un moteur de jeu modulaire écrit en C++ (C++20), conçu pour séparer clairement les responsabilités entre le rendu, la physique, l’audio, les entrées et la logique de jeu. Cette approche vise à faciliter la maintenance, l’évolution et les tests des différents systèmes.

### 2.2 Composants principaux
- **Rendering System** : Gestion du rendu graphique
- **Physics System** : Simulation physique et collisions
- **Audio System** : Gestion du son
- **Input System** : Gestion des entrées utilisateur
- **Core / Game Logic** : Boucle de jeu et orchestration des systèmes
- **Entity Manager** : Gestion des objets et entitées
- **Asset Manager** : Gestion du load des assets dynamiquement.

---

## 3. Requirements

### 3.1 Functional Requirements
- Rendu 3D temps réel
- Simulation physique basique (collisions, rigid bodies)
- Lecture de sons et musiques
- Gestion des entrées clavier / souris

### 3.2 Non-Functional Requirements
- Architecture modulaire
- Performances stables (objectif 60 FPS)
- Code clair, maintenable et documenté

---

## 4. System Architecture & Design

### 4.1 Vue d’ensemble
Le moteur repose sur une architecture modulaire où chaque système est isolé derrière des interfaces claires. Cette approche permet de limiter les dépendances et de faciliter les évolutions futures.

### 4.2 Choix technologiques et justification

#### API Graphique retenue : **DirectX 11**
DirectX 11 a été choisie comme API graphique principale pour El Motor. Ce choix représente un compromis équilibré entre performances, complexité et temps de développement. L’API permet une prise en main rapide tout en restant suffisamment bas niveau pour comprendre et implémenter les concepts fondamentaux du rendu 3D (pipeline graphique, shaders, gestion des ressources).

L’intégration naturelle de DirectX 11 dans l’écosystème Microsoft facilite également le développement et le débogage sous Windows.

**APIs graphiques non retenues :**
- **DirectX 12** : API très bas niveau nécessitant une gestion explicite de la mémoire et de la synchronisation CPU/GPU, jugée trop complexe pour le périmètre et la durée du projet.
- **OpenGL** : API plus ancienne et moins représentative des pipelines graphiques modernes, avec un modèle moins adapté à une architecture moteur moderne.
- **Vulkan** : API moderne et performante, mais dont la courbe d’apprentissage et la complexité d’implémentation sont trop élevées pour un projet en phase initiale.

---

#### API Physique retenue : **Jolt Physics**
Jolt Physics a été sélectionnée pour la gestion de la physique en raison de ses excellentes performances, de son API moderne et de sa simplicité d’intégration. La bibliothèque est pensée pour être multithreadée et cache-friendly, ce qui correspond aux objectifs de performance et de clarté du moteur.

**APIs physiques non retenues :**
- **PhysX** : Solution puissante mais orientée usage industriel, avec une API lourde et une intégration plus complexe pour un moteur pédagogique.
- **Bullet** : Moteur physique éprouvé mais basé sur une API plus ancienne et moins optimisée pour les architectures modernes.

---

#### API Audio retenue : **MiniAudio**

MiniAudio a été retenue pour la gestion de l’audio du moteur en raison de sa **légèreté**, de sa **simplicité d’intégration** et du **contrôle fin** qu’elle offre sur le fonctionnement interne du système audio.  
Cette bibliothèque bas niveau permet à l’équipe de concevoir un système audio **sur mesure**, parfaitement intégré à l’architecture du moteur, tout en garantissant de bonnes performances.

**APIs audio non retenues :**
- **FMOD** : Middleware robuste et largement utilisé dans l’industrie, mais offrant un niveau d’abstraction trop élevé pour les objectifs pédagogiques du projet, limitant la maîtrise des systèmes audio internes du moteur.
- **OpenAL** : API plus ancienne avec un modèle d’utilisation moins flexible et moins adapté à une architecture moteur moderne.
- **Wwise** : Solution très complète mais trop lourde et complexe pour le périmètre et la durée du projet, nécessitant un pipeline externe conséquent.
---



## 5. État d’avancement

Le projet est actuellement en **phase de démarrage**. Les travaux portent principalement sur :
- La mise en place de l’architecture globale
- L’initialisation des systèmes principaux
- La préparation des abstractions nécessaires au rendu, à la physique et à l’audio

---

## 6 Les fonctionnalités du moteur

## 6.1 Asset Management

Afin de gérer les ressources utilisées par le moteur, un Asset Manager centralisé a été implémenté. Ce système est responsable du chargement, du stockage, de la réutilisation et de la libération des assets.

Toutes les ressources héritent d’une classe abstraite commune Asset, définissant le cycle de vie d’une ressource :

**Load() :** chargement depuis le disque

CreateBuffers() : création des ressources GPU

**Unload() :** libération des ressources

Deux types d’assets sont actuellement implémentés :

### MeshAsset
Permet le chargement de modèles 3D au format OBJ. Les données de vertex (position, normale, UV) et les indices sont extraits du fichier puis utilisés pour créer les vertex buffers et index buffers nécessaires au rendu avec DirectX 11.

### TextureAsset
Gère le chargement des textures via WICTextureLoader (DirectXTK), supportant des formats standards comme PNG et JPG. Les textures sont stockées sous forme de Shader Resource View (SRV) afin d’être utilisées dans les shaders.

Les assets sont stockés dans des conteneurs associatifs indexés par leur chemin afin d’éviter les duplications et de permettre leur réutilisation dans le moteur.

**L’Asset Manager** fournit également des fonctions de rechargement (**Reload**) et de libération globale (**UnloadAll**) des ressources.

---

## 6.2 Entity Management

Le moteur utilise une architecture **Entity-Component** pour représenter les objets présents dans une scène.
Chaque objet est représenté par un **GameObject** auquel différents **components** peuvent être attachés afin de définir son comportement.

### GameObject

La classe **GameObject** représente une entité dans la scène.
Elle possède :

* un **nom**
* une **liste de composants**
* une **hiérarchie parent / enfants**

Lors de sa création, un **Transform** est automatiquement ajouté afin de stocker les informations spatiales de l’objet (position, rotation, scale).

### Component System

Les fonctionnalités sont ajoutées aux entités via des **components** héritant de la classe abstraite **Component**.

Chaque composant possède un cycle de vie simple :

* **Start()**
* **Update(float dt)**
* **OnDestroy()**

Les composants peuvent être ajoutés et récupérés dynamiquement grâce aux fonctions :

* `AddComponent<T>()`
* `GetComponent<T>()`

### Components implémentés

Plusieurs composants sont actuellement disponibles :

* **Transform** : position, rotation et scale de l’entité
* **MeshComponent** : associe un **MeshAsset** pour le rendu
* **RigidBodyComponent** : gère une physique simple basée sur la vitesse et le temps

Ce système permet d’ajouter facilement de nouveaux comportements aux entités sans modifier la structure du moteur.


---
## 7. Le fonctionnement du moteur

## 7.1 Le lancement


## 8. Conclusion

Les choix technologiques effectués pour El Motor visent à garantir un développement réaliste, cohérent et pédagogiquement pertinent. Ils permettent à l’équipe de se concentrer sur la compréhension des systèmes fondamentaux d’un moteur de jeu tout en respectant les contraintes de temps et de complexité du projet.
