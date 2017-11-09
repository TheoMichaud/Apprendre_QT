-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Jeu 09 Novembre 2017 à 22:40
-- Version du serveur :  5.5.54-0+deb8u1
-- Version de PHP :  5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `snirBanque`
--

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `assurance_vie`
--
CREATE TABLE IF NOT EXISTS `assurance_vie` (
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

CREATE TABLE IF NOT EXISTS `client` (
  `idclient` int(5) NOT NULL,
  `nom` varchar(128) NOT NULL,
  `prenom` varchar(128) NOT NULL,
  `ville` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `client`
--

INSERT INTO `client` (`idclient`, `nom`, `prenom`, `ville`) VALUES
(1, 'Moulin', 'Sylvie', 'Paris'),
(2, 'Legrand', 'Anne', 'Le Mans'),
(3, 'Dubois', 'Emile', 'Neuilly'),
(4, 'Leroy', 'Marie', 'la Suze sur Sarthe');

-- --------------------------------------------------------

--
-- Structure de la table `compte`
--

CREATE TABLE IF NOT EXISTS `compte` (
  `idcompte` int(5) NOT NULL,
  `idproprietaire` int(5) NOT NULL,
  `type` varchar(128) NOT NULL,
  `solde` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `compte`
--

INSERT INTO `compte` (`idcompte`, `idproprietaire`, `type`, `solde`) VALUES
(1, 1, 'Compte Courant', 1652.55),
(2, 1, 'Livret A', 150.00),
(3, 1, 'Assurance Vie', 10537.00),
(4, 2, 'Compte Courant', 3000.00),
(5, 3, 'Compte Courant', 500.00),
(6, 3, 'Assurance Vie', 0.00),
(7, 4, 'Compte Courant', 500.00),
(8, 4, 'Plan Epargne Actions', 0.00),
(9, 4, 'Livret A', 0.00);

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `compte_courant`
--
CREATE TABLE IF NOT EXISTS `compte_courant` (
`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`ville` varchar(128)
,`type` varchar(128)
,`solde` decimal(10,2)
);
-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Livret A`
--
CREATE TABLE IF NOT EXISTS `Livret A` (
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

CREATE TABLE IF NOT EXISTS `operation` (
  `idop` int(5) NOT NULL,
  `idcompte` int(5) NOT NULL,
  `montant` decimal(10,2) NOT NULL,
  `informations` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `operation`
--

INSERT INTO `operation` (`idop`, `idcompte`, `montant`, `informations`) VALUES
(1, 1, 2000.00, 'Salaire'),
(2, 1, -121.53, 'Courses'),
(3, 1, -75.92, 'Essence'),
(4, 1, -150.00, 'VIR Livret A'),
(5, 2, 150.00, 'VIR du Compte Courant'),
(6, 4, 3000.00, 'Salaire'),
(7, 3, 10000.00, 'VIR initial'),
(8, 3, 537.00, 'Interets'),
(9, 5, 500.00, 'VIR initial'),
(10, 7, 500.00, 'VIR initial');

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Plan Epargne Actions`
--
CREATE TABLE IF NOT EXISTS `Plan Epargne Actions` (
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

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `assurance_vie` AS select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Assurance Vie'));

-- --------------------------------------------------------

--
-- Structure de la vue `compte_courant`
--
DROP TABLE IF EXISTS `compte_courant`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `compte_courant` AS select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Compte Courant'));

-- --------------------------------------------------------

--
-- Structure de la vue `Livret A`
--
DROP TABLE IF EXISTS `Livret A`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `Livret A` AS select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Livret A'));

-- --------------------------------------------------------

--
-- Structure de la vue `Plan Epargne Actions`
--
DROP TABLE IF EXISTS `Plan Epargne Actions`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `Plan Epargne Actions` AS select `compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`client`.`ville` AS `ville`,`compte`.`type` AS `type`,`compte`.`solde` AS `solde` from (`compte` join `client`) where ((`compte`.`idproprietaire` = `client`.`idclient`) and (`compte`.`type` = 'Plan Epargne Actions'));

--
-- Index pour les tables exportées
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
 ADD PRIMARY KEY (`idcompte`), ADD KEY `idproprietaire` (`idproprietaire`);

--
-- Index pour la table `operation`
--
ALTER TABLE `operation`
 ADD PRIMARY KEY (`idop`), ADD KEY `idcompte` (`idcompte`);

--
-- Contraintes pour les tables exportées
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

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
