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

## 6.3 Éditeur & Hub Manager

L'éditeur est le point d'entrée principal du moteur. Il repose sur un **HubManager** qui pilote une machine à états à trois modes :

* **Hub** : écran d'accueil permettant de créer ou charger un projet existant via un dialogue de fichiers.
* **Editor** : édition de la scène (hiérarchie des GameObjects, inspecteur de composants, chargement d'assets, gestion des scripts).
* **Run** : exécution du jeu dans l'éditeur avec mise à jour des scripts et de la physique.

La boucle principale gère le polling GLFW, le rendu ImGui, le rendu 3D via D3D11 et la mise à jour des inputs à chaque frame.

---

## 6.4 GUI Layer (ImGui)

La couche graphique de l'éditeur est basée sur **Dear ImGui**, initialisée avec les backends **GLFW** et **DirectX 11**. Elle supporte le **docking** et le **multi-viewport**. La classe `GuiLayer` encapsule l'initialisation, le begin/end de frame et le clear du render target.

---

## 6.5 Project Manager & Sauvegarde

Le **ProjectManager** (singleton) gère le cycle de vie des projets :

* **Création** : génère l'arborescence du projet (dossiers `Assets/`, `Scenes/`, `Scripts/`) et un fichier `ProjectConfig.json` contenant le nom et la scène par défaut.
* **Chargement** : lit le `ProjectConfig.json` puis désérialise la scène JSON en recréant les GameObjects. Seul le **Transform** est entièrement restauré (position, rotation, scale) ; les autres composants (MeshRenderer, etc.) sont ré-ajoutés mais sans leurs données associées.
* **Sauvegarde** : sérialise le scene graph (noms, types de composants) au format JSON via **nlohmann::json**. Seules les données du Transform sont écrites ; les autres composants ne sauvegardent que leur type.
* **LastProject** : un fichier `LastProject.txt` conserve le dernier projet ouvert.

---

## 6.6 Scripting & Macro d'auto-enregistrement

Le système de scripting permet aux utilisateurs de créer des comportements personnalisés :

* **Script** : classe abstraite de base définissant `OnStart()` et `Update(float dt)`.
* **UserScript** : classe intermédiaire ajoutant un nom au script.
* **REGISTER_SCRIPT(Type)** : macro qui enregistre automatiquement un script dans le `ScriptRegistry` au démarrage du programme via un objet statique anonyme.
* **ScriptManager** : gère la création de fichiers sources (header + cpp) depuis l'éditeur, l'instanciation des scripts via le registre, leur exécution (`StartAll`, `updateScripts`) et leur suppression. Il peut aussi relancer un build CMake pour recompiler les scripts modifiés.

---

## 6.7 Input Manager

L'**InputManager** gère les entrées clavier et souris via **GLFW**. Chaque touche et bouton souris possède un état parmi quatre : `Up`, `Pressed`, `Held`, `Released`, mis à jour chaque frame. Le système expose des fonctions de requête (`isKeyPressed`, `isKeyHeld`, `isKeyReleased`) et fournit la position et le delta de la souris. Les touches sont identifiées par des **scancodes** mappés sur les constantes GLFW.

---

## 6.8 Logger

Le **LoggerManager** est un singleton offrant trois niveaux de log : **Error**, **Warning** et **Info**. Chaque message est affiché dans la console (`cout`/`cerr`) et écrit dans un fichier `UserLog.txt` en mode append.

---

## 6.9 Time Manager

Le **TimeManager** utilise `std::chrono::high_resolution_clock` pour calculer le **delta time** entre chaque frame. Un clamp à 0.1s évite les pics lors de pauses ou de chargements. Le **FPS** est calculé via une moyenne glissante exponentielle.

---

## 6.10 Camera

Le système de caméra repose sur une classe abstraite **Camera** et une implémentation **EditorCamera** :

* **Déplacement** : WASD pour se déplacer dans la scène, clic souris pour orienter la vue.
* **Rotation** : gérée par **quaternions** pour éviter le gimbal lock.
* **Matrices** : calcul des matrices **Projection** (perspective), **View** (LookAt) et **VP** (combinée) à chaque frame.

---

## 6.11 Components

Les composants suivants peuvent être attachés à un GameObject :

* **Transform** : position, rotation et scale de l'entité. Ajouté automatiquement à la création de chaque GameObject.
* **MeshComponent** : associe un **MeshAsset** (modèle 3D) au GameObject pour le rendu. Le mesh est assignable depuis l'inspecteur de l'éditeur.
* **TextureComponent** : associe une **TextureAsset** au GameObject pour appliquer une texture lors du rendu.
* **AssetComponent** : composant générique permettant de lier n'importe quel type d'asset (mesh, texture) à une entité via l'Asset Manager.
* **RigidBodyComponent** : simulation physique basique — masse, vélocité, gravité (9.81 m/s²). Les forces sont accumulées via `AddForce()`, puis intégrées par Euler à chaque frame pour mettre à jour la position.

---

## 6.12 Shaders

Le moteur utilise deux shaders HLSL compilés en `.cso` :

* **Vertex Shader** : reçoit position, normale et UV en entrée et les transmet au pixel shader (pass-through, sans transformation MVP pour l'instant).
* **Pixel Shader** : utilise un **constant buffer** (`ObjectColor`) contenant une couleur et un flag `useTexture`. Si une texture est présente, elle est échantillonnée ; sinon, la couleur unie est appliquée.
---
## 7. Le fonctionnement du moteur

## 7.1 Le lancement et l'utilisation de l'éditeur

Au lancement de l'application, l'utilisateur arrive sur le **Hub**, l'écran d'accueil du moteur.

### Créer ou charger un projet

Sur le Hub, deux options s'offrent à l'utilisateur :

1. **Créer un projet** : saisir un nom dans le champ texte en bas de l'écran, appuyer sur entrée, puis cliquer sur **"Create Project"**. Le moteur génère automatiquement l'arborescence du projet (dossiers `Assets/`, `Scenes/`, `Scripts/` et un fichier `ProjectConfig.json`), puis bascule vers l'éditeur.
2. **Charger un projet existant** : cliquer sur **"Load Project"**. Un explorateur de fichiers s'ouvre et permet de naviguer jusqu'au dossier d'un projet existant (dans `Game/Projects/`). Une fois sélectionné, la scène sauvegardée est rechargée et l'éditeur s'ouvre.

### L'éditeur

Une fois dans l'éditeur, l'interface se divise en plusieurs zones :

**Barre d'outils (haut gauche) :**
* **"Create GameObject"** : ajoute un nouvel objet vide dans la scène (avec un Transform par défaut).
* **"Delete GameObject"** : supprime le GameObject actuellement sélectionné.
* **"Load Assets"** : ouvre un dialogue de fichiers pour importer un modèle 3D (`.obj`, `.fbx`) ou une texture (`.png`, `.jpg`) dans le moteur.
* **"Save"** : sauvegarde l'état actuel de la scène dans le fichier JSON du projet.
* **"Run"** : lance le mode jeu — les scripts sont instanciés, leur `OnStart()` est appelé, puis `Update()` est exécuté à chaque frame.
* **"Reload"** : sauvegarde le projet, puis relance un build CMake pour recompiler les scripts modifiés.

**Hiérarchie (panneau haut droit) :**
* Liste tous les GameObjects de la scène. Cliquer sur un objet le sélectionne et ouvre ses détails dans l'inspecteur.

**Inspecteur (panneau bas droit droit) :**
* Affiche les composants du GameObject sélectionné.
* **Renommer** : un champ texte permet de modifier le nom du GameObject.
* **Ajouter un composant** : un menu déroulant propose les types disponibles (`MeshRenderer`, `Camera`, `RigidBody`). Cliquer sur **"Add"** l'attache au GameObject.
* **Éditer un composant** : cliquer sur un composant dans la liste affiche ses propriétés modifiables :
  * *Transform* : champs glissants pour la position, rotation et scale (X, Y, Z).
  * *MeshRenderer* : un menu déroulant liste les meshes chargés — en sélectionner un l'assigne à l'objet.

**Panneau Scripts (bas gauche) :**
* Affiche l'arborescence des fichiers scripts du projet (`.hpp` / `.cpp`).
* **"Add"** : saisir un nom puis valider crée automatiquement un nouveau script (header + source) avec le squelette de base (`OnStart`, `Update`) et la macro `REGISTER_SCRIPT`.
* **"Delete Script"** : supprime le script sélectionné du disque et de la mémoire.

### Mode Run

En cliquant sur **"Run"**, l'éditeur passe en mode exécution :
* Tous les scripts enregistrés sont instanciés et démarrés.
* La boucle de jeu met à jour les scripts et la physique (RigidBody) à chaque frame.
* La caméra reste contrôlable (WASD + souris).
* Le rendu 3D continue de fonctionner normalement.

Pour quitter l'application à tout moment, appuyer sur **Échap** ferme la fenêtre.

---

## 8. Conclusion

Les choix technologiques effectués pour El Motor visent à garantir un développement réaliste, cohérent et pédagogiquement pertinent. Ils permettent à l’équipe de se concentrer sur la compréhension des systèmes fondamentaux d’un moteur de jeu tout en respectant les contraintes de temps et de complexité du projet.
