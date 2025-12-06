
# **PHILOSOPHERS**
# *Gestion de la concurrence avec threads*

Ce projet est une implémentation du problème classique des *Dining Philosophers*, utilisé pour introduire les difficultés de la **programmation concurrente** et de la **synchronisation des threads**.

L’objectif est de modéliser plusieurs philosophes qui mangent, dorment et pensent, tout en partageant des ressources limitées : les fourchettes.
Le programme doit garantir qu’aucun philosophe ne meurt de faim, qu’il n’y a pas de *deadlock*, et que le comportement reste cohérent et reproductible.

---

## **Fonctionnalités**

* Création d’un thread par philosophe.
* Gestion des états : *penser*, *manger*, *dormir*.
* Utilisation de mutex pour éviter l’accès concurrent aux mêmes ressources.
* Synchronisation fine pour empêcher :

  * les *data races*
  * les *deadlocks*
  * les comportements imprévisibles

---

## **Multithreading**

Le **multithreading** permet d’exécuter plusieurs tâches en parallèle au sein d’un même programme.
Chaque tâche s’exécute dans un **thread**, c’est-à-dire une ligne d’exécution indépendante mais qui partage la même mémoire.

### ✦ Problème : accès simultané

Lorsque plusieurs threads accèdent à la même variable ou ressource au même moment, cela peut créer des erreurs invisibles et difficiles à reproduire.

### ✦ Solution : mutex

Un **mutex** (mutual exclusion) assure qu’une seule thread à la fois peut accéder à une ressource partagée.
Dans Philosophers, chaque fourchette est protégée par un mutex.

---

## **Objectifs pédagogiques**

* Comprendre les bases du multithreading.
* Manipuler les mutex pour protéger les ressources.
* Apprendre à éviter les situations de blocage (deadlock).
* Concevoir une simulation déterministe malgré l’exécution parallèle.

---

## **Compilation & Exécution**

```bash
make
./philo 5 800 200 200
```

Arguments :

```
./philo nbr_philos time_to_die time_to_eat time_to_sleep [nbr_meals]
```
