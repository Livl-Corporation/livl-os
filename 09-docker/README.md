# I – Proposer un service d’infrastructure via conteneur

## 1. La récupération de l’image networkboot/dhcpd depuis le hub docker.
`docker pull networkboot/dhcpd`

## 2. La création du fichier de configuration pour le service
Voir le fichier de configuration [dhcpd.conf](./dhcpd.conf).

### Commandes pour ajouter une adresse IP à l'interface eth0
`ip addr add 10.16.64.1/24 dev eth0`
`ifconfig eth0:0 10.16.64.1 netmask 255.255.255.0 up`

## 3. Le démarrage du conteneur avec les paramètres appropriés.
`docker run --name my_dhcp -v /home/jvondermarck/IT/Systems/Labs/09-docker:/data -d --network host networkboot/dhcpd`

> ":/data" permet de monter le dossier courant dans le conteneur --> le fichier de configuration est accessible dans le conteneur et peut être modifié sans devoir recréer le conteneur au chemin "/data/dhcpd.conf".
> -v : permet de monter un volume dans le conteneur (permet de monter le fichier de configuration dans le conteneur)
> --network host : permet de partager le réseau de la machine hôte avec le conteneur (permet de ne pas devoir configurer le réseau du conteneur
> -d : permet de lancer le conteneur en arrière plan

## 4. La vérification de la disponibilité du service.
`docker logs my_dhcp`

## 5. L’arrêt du conteneur associé.
`docker stop my_dhcp`

# II – Proposer une stack applicative « wordpress »
- Voir le fichier [docker-compose.yml](./docker-compose.yml) pour la stack applicative.
- Run the stack: `docker-compose up -d`
> -d : permet de lancer le conteneur en arrière plan
- Stop the stack: `docker-compose down`

- `docker ps` : permet de lister les conteneurs en cours d'exécution
- Pour accéder à l'interface web de wordpress, il faut aller sur l'adresse IP de la machine hôte sur le port 8080 (http://localhost:8080/)