-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost
-- Généré le :  ven. 10 nov. 2017 à 23:44
-- Version du serveur :  5.5.51-MariaDB
-- Version de PHP :  5.5.38

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `snirBanque`
--

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `assurance_vie`
-- (Voir ci-dessous la vue réelle)
--
CREATE TABLE `assurance_vie` (
`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`ville` varchar(128)
,`type` varchar(128)
,`solde` decimal(10,2)
);

-- --------------------------------------------------------

--
-- Structure de la table `client`
--

CREATE TABLE `client` (
  `idclient` int(5) NOT NULL,
  `nom` varchar(128) NOT NULL,
  `prenom` varchar(128) NOT NULL,
  `ville` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `client`
--

INSERT INTO `client` (`idclient`, `nom`, `prenom`, `ville`) VALUES
(1, 'Simier', 'Philippe', 'Le Mans'),
(2, 'Moulin', 'Sylvie', 'Paris'),
(3, 'Legrand', 'Anne', 'Le Mans'),
(4, 'Dubois', 'Emile', 'Neuilly'),
(5, 'Leroy', 'Marie', 'la Suze sur Sarthe');

-- --------------------------------------------------------

--
-- Structure de la table `compte`
--

CREATE TABLE `compte` (
  `idcompte` int(5) NOT NULL,
  `idproprietaire` int(5) NOT NULL,
  `type` varchar(128) NOT NULL,
  `solde` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `compte`
--

INSERT INTO `compte` (`idcompte`, `idproprietaire`, `type`, `solde`) VALUES
(1, 1, 'Compte Courant', '1652.55'),
(2, 1, 'Livret A', '150.00'),
(3, 1, 'Assurance Vie', '10537.00'),
(4, 2, 'Compte Courant', '3000.00'),
(5, 3, 'Compte Courant', '10508.50'),
(6, 3, 'Assurance Vie', '0.00'),
(7, 4, 'Compte Courant', '500.00'),
(8, 4, 'Plan Epargne Actions', '0.00'),
(9, 4, 'Livret A', '0.00'),
(10, 5, 'Compte Courant', '3500.00');

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `compte_courant`
-- (Voir ci-dessous la vue réelle)
--
CREATE TABLE `compte_courant` (
`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`ville` varchar(128)
,`type` varchar(128)
,`solde` decimal(10,2)
);

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Livret_A`
-- (Voir ci-dessous la vue réelle)
--
CREATE TABLE `Livret_A` (
`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`ville` varchar(128)
,`type` varchar(128)
,`solde` decimal(10,2)
);

-- --------------------------------------------------------

--
-- Structure de la table `operation`
--

CREATE TABLE `operation` (
  `idop` int(5) NOT NULL,
  `idcompte` int(5) NOT NULL,
  `montant` decimal(10,2) NOT NULL,
  `informations` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `operation`
--

INSERT INTO `operation` (`idop`, `idcompte`, `montant`, `informations`) VALUES
(1, 1, '2000.00', 'Salaire'),
(2, 1, '-121.53', 'Courses'),
(3, 1, '-75.92', 'Essence'),
(4, 1, '-150.00', 'VIR Livret A'),
(5, 2, '150.00', 'VIR du Compte Courant'),
(6, 4, '3000.00', 'Salaire'),
(7, 3, '10000.00', 'VIR initial'),
(8, 3, '537.00', 'Interets'),
(9, 5, '10508.50', 'VIR initial'),
(10, 7, '500.00', 'VIR initial'),
(11, 10, '3500.00', 'VIR Initial');

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Plan_Epargne_Actions`
-- (Voir ci-dessous la vue réelle)
--
CREATE TABLE `Plan_Epargne_Actions` (
`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`ville` varchar(128)
,`type` varchar(128)
,`solde` decimal(10,2)
);

-- --------------------------------------------------------

--
-- Structure de la vue `assurance_vie`
--
DROP TABLE IF EXISTS `assurance_vie`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `assurance_vie`  AS  select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Assurance Vie')) ;

-- --------------------------------------------------------

--
-- Structure de la vue `compte_courant`
--
DROP TABLE IF EXISTS `compte_courant`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `compte_courant`  AS  select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Compte Courant')) ;

-- --------------------------------------------------------

--
-- Structure de la vue `Livret_A`
--
DROP TABLE IF EXISTS `Livret_A`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `Livret_A`  AS  select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Livret A')) ;

-- --------------------------------------------------------

--
-- Structure de la vue `Plan_Epargne_Actions`
--
DROP TABLE IF EXISTS `Plan_Epargne_Actions`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `Plan_Epargne_Actions`  AS  select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Plan Epargne Actions')) ;

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `client`
--
ALTER TABLE `client`
  ADD PRIMARY KEY (`idclient`);

--
-- Index pour la table `compte`
--
ALTER TABLE `compte`
  ADD PRIMARY KEY (`idcompte`),
  ADD KEY `idproprietaire` (`idproprietaire`);

--
-- Index pour la table `operation`
--
ALTER TABLE `operation`
  ADD PRIMARY KEY (`idop`),
  ADD KEY `idcompte` (`idcompte`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `client`
--
ALTER TABLE `client`
  MODIFY `idclient` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `compte`
--
ALTER TABLE `compte`
  ADD CONSTRAINT `compte_ibfk_1` FOREIGN KEY (`idproprietaire`) REFERENCES `client` (`idclient`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `operation`
--
ALTER TABLE `operation`
  ADD CONSTRAINT `operation_ibfk_1` FOREIGN KEY (`idcompte`) REFERENCES `compte` (`idcompte`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
