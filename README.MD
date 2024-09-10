Step 1 : Créer un socket raw
    Créer un socket pour envoyer et recevoir des paquets UDP ou ICMP.
    Vérifier que l'exécution se fait avec les privilèges root.

Step 2 : Envoyer des paquets avec TTL croissant
    Créer une fonction qui envoie des paquets avec des valeurs de TTL de 1 à 64 (ou plus).
    Utiliser les champs nécessaires pour les paquets UDP ou ICMP.
    Utiliser setsockopt() pour définir le TTL pour chaque paquet envoyé.
    Gérer les erreurs si l'envoi échoue.

Step 3 : Réception des réponses ICMP "Time Exceeded"
    Implémenter la réception des paquets ICMP "Time Exceeded" renvoyés par les routeurs.
    Analyser la réponse pour extraire l'adresse IP du routeur.
    Gérer les cas où aucune réponse n'est reçue (afficher *).

Step 4 : Calcul et affichage du délai (RTT)
    Mesurer le temps entre l'envoi du paquet et la réception de la réponse pour chaque routeur.
    Afficher l'adresse IP et les temps de réponse de chaque saut.
    Gérer plusieurs réponses pour un même saut.

Step 5 : Gérer les paquets jusqu'à la destination
    Continuer à incrémenter le TTL jusqu'à atteindre le serveur cible.
    Identifier les paquets ICMP Echo Reply ou UDP Port Unreachable lorsque la destination est atteinte.

Step 6 : Gérer les options
    Ajouter des options comme --help pour l'affichage d'aide.
    Gérer des options avancées comme la sélection du protocole (ICMP ou UDP), ou la gestion du TTL initial.

Step 7 : Bonus
    Implémenter des options supplémentaires (-n, -I pour ICMP, ou TCP).
    Gérer des affichages plus détaillés ou des optimisations de performance.

ToDo list : 
    - Load Balencing
    - decimal rtt