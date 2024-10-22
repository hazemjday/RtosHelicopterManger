/*
 * Projet : Contrôleur de vol multi-tâches pour hélicoptère
 * Auteur : Hazem
 * 
 * Description : 
 * Ce programme implémente un contrôleur de vol pour hélicoptère en utilisant un ordonnanceur cyclique. 
 * L'ordonnanceur est basé sur un timer matériel (`itimerval`) qui génère des interruptions à des intervalles réguliers.
 * Les tâches sont planifiées avec des périodes spécifiques, et exécutées en fonction d'un compteur (`cpt`).
 * 
 * Les tâches suivantes sont implémentées :
 * - Validation des données des capteurs (dataValidation) : Période de 1/180s
 * - Suivi des données clavier (keyboardDataTracking) : Période de 1/30s
 * - Contrôle des boucles extérieures (controlOuterLoops) : Période de 1/30s
 * - Contrôle des boucles intérieures (controlInnerLoops) : Période de 1/90s
 * - Calcul des commandes de contrôle (computeNComd) : Période de 1/180s
 * 
 * Ordonnanceur : 
 * Ce programme utilise un *ordonnanceur cyclique non-prioritaire*. À chaque interruption, les tâches sont exécutées 
 * dans un ordre déterminé en fonction du compteur `cpt`. L'algorithme vérifie le compteur et exécute les tâches 
 * périodiquement.
 * 
 * Commandes de compilation et d'exécution :
 * Compilation :
 * gcc main.c helicopter.c -o helicopterController
 * 
 * Exécution :
 * ./helicopterController
 */

#include <stdio.h>
#include "helicopter.h"
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

int cpt = 0; // Compteur pour gérer l'ordonnancement des tâches
#define PERIOD (1000000 / 180) // Période des interruptions (1/180s = 5555 microsecondes)

/* Gestionnaire d'interruption appelé à chaque période */
void interpt(int signo) {
    cpt++; // Incrémentation du compteur
    
    if (cpt == 6) {
        // Chaque 6 périodes (1/30s) : exécuter toutes les tâches
        dataValidation();
        keyboardDataTracking();
        controlOuterLoops();
        controlInnerLoops();
        computeNComd();
        cpt = 0; // Réinitialisation du compteur
    } 
    else if (cpt % 2 == 1) {
        // À chaque période impaire (1/180s) : valider les données et calculer les commandes
        dataValidation();
        computeNComd();
    } 
    else {
        // À chaque période paire (1/90s) : valider les données, contrôler les boucles internes, calculer les commandes
        dataValidation();
        controlInnerLoops();
        computeNComd();
    }
}

int main (int argc, char *argv[]) {
    struct itimerval timer;
    
    // Associer le signal SIGALRM à la fonction d'interruption interpt
    signal(SIGALRM, interpt);

    // Initialiser le timer : première interruption après une période
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = PERIOD; // 1/180s
    
    // Configurer les intervalles des interruptions
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = PERIOD; // 1/180s
    
    // Démarrer le timer
    setitimer(ITIMER_REAL, &timer, NULL);
    
    // Boucle principale du programme
    while (1) {
        pause(); // Attente d'une interruption
    }

    return 0;
}

