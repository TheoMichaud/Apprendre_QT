-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Dim 12 Novembre 2017 à 18:22
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
-- Structure de la table `client`
--

CREATE TABLE IF NOT EXISTS `client` (
`idclient` int(5) NOT NULL,
  `nom` varchar(128) NOT NULL,
  `prenom` varchar(128) NOT NULL,
  `ville` varchar(128) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;

--
-- Contenu de la table `client`
--

INSERT INTO `client` (`idclient`, `nom`, `prenom`, `ville`) VALUES
(1, 'Simon', 'Yves', 'Le Mans'),
(2, 'Moulin', 'Sylvie', 'Paris'),
(3, 'Legrand', 'Anne', 'Le Mans'),
(4, 'Dubois', 'Emile', 'Neuilly'),
(5, 'Leroy', 'Marie', 'la Suze sur Sarthe');

-- --------------------------------------------------------

--
-- Structure de la table `compte`
--

CREATE TABLE IF NOT EXISTS `compte` (
`idcompte` int(5) NOT NULL,
  `idproprietaire` int(5) NOT NULL,
  `type` enum('Compte Courant','Livret A','PEA','Assurance vie','PEL') NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;

--
-- Contenu de la table `compte`
--

INSERT INTO `compte` (`idcompte`, `idproprietaire`, `type`) VALUES
(1, 1, 'Compte Courant'),
(2, 1, 'Livret A'),
(3, 1, 'Assurance vie'),
(4, 2, 'Compte Courant'),
(5, 3, 'Compte Courant'),
(6, 3, 'Assurance vie'),
(7, 4, 'Compte Courant'),
(8, 4, 'PEL'),
(9, 4, 'Livret A'),
(10, 5, 'Compte Courant'),
(12, 5, 'Assurance vie'),
(15, 4, 'PEA');

-- --------------------------------------------------------

--
-- Structure de la table `operation`
--

CREATE TABLE IF NOT EXISTS `operation` (
`idop` int(5) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `idcompte` int(5) NOT NULL,
  `montant` decimal(10,2) NOT NULL,
  `informations` text NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;

--
-- Contenu de la table `operation`
--

INSERT INTO `operation` (`idop`, `date`, `idcompte`, `montant`, `informations`) VALUES
(1, '2017-10-01 09:37:23', 1, 2000.00, 'Salaire'),
(2, '2017-05-16 08:44:00', 1, -121.53, 'Courses'),
(3, '2017-11-10 18:51:00', 1, -75.92, 'Essence'),
(4, '2017-03-12 18:55:42', 1, -150.00, 'VIR Livret A'),
(5, '2017-11-09 16:55:42', 2, 150.00, 'VIR du Compte Courant'),
(6, '2017-08-01 10:51:42', 4, 3000.00, 'Salaire'),
(7, '2017-09-11 11:53:42', 3, 10000.00, 'VIR initial'),
(8, '2017-12-31 22:59:42', 3, 537.00, 'Interets'),
(9, '2017-11-12 16:51:42', 5, 10508.50, 'VIR initial'),
(10, '2017-08-12 12:55:42', 7, 500.00, 'VIR initial'),
(11, '2017-08-10 11:58:42', 10, 3500.00, 'VIR Initial'),
(13, '2017-08-09 13:37:42', 12, 2000.00, 'VIR initial'),
(17, '2017-12-09 15:49:42', 8, 4200.00, 'virement Ouverture '),
(18, '2017-03-02 16:53:42', 15, 14000.00, 'Vir Ouverture');

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Vue_compte`
--
CREATE TABLE IF NOT EXISTS `Vue_compte` (
`id` int(5)
,`idcompte` int(5)
,`nom` varchar(128)
,`prenom` varchar(128)
,`type` enum('Compte Courant','Livret A','PEA','Assurance vie','PEL')
,`solde` decimal(32,2)
);
-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `V_solde_compte`
--
CREATE TABLE IF NOT EXISTS `V_solde_compte` (
`idcompte` int(5)
,`solde` decimal(32,2)
);
-- --------------------------------------------------------

--
-- Structure de la vue `Vue_compte`
--
DROP TABLE IF EXISTS `Vue_compte`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `Vue_compte` AS select `client`.`idclient` AS `id`,`compte`.`idcompte` AS `idcompte`,`client`.`nom` AS `nom`,`client`.`prenom` AS `prenom`,`compte`.`type` AS `type`,`V_solde_compte`.`solde` AS `solde` from ((`client` join `compte`) join `V_solde_compte`) where ((`client`.`idclient` = `compte`.`idproprietaire`) and (`compte`.`idcompte` = `V_solde_compte`.`idcompte`));

-- --------------------------------------------------------

--
-- Structure de la vue `V_solde_compte`
--
DROP TABLE IF EXISTS `V_solde_compte`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `V_solde_compte` AS select `operation`.`idcompte` AS `idcompte`,sum(`operation`.`montant`) AS `solde` from `operation` group by `operation`.`idcompte`;

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
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `client`
--
ALTER TABLE `client`
MODIFY `idclient` int(5) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=19;
--
-- AUTO_INCREMENT pour la table `compte`
--
ALTER TABLE `compte`
MODIFY `idcompte` int(5) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT pour la table `operation`
--
ALTER TABLE `operation`
MODIFY `idop` int(5) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=19;
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
