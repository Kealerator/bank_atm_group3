-- MySQL dump 10.13  Distrib 8.0.44, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank_automat
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `idAsiakas` int NOT NULL AUTO_INCREMENT,
  `Etunimi` varchar(45) NOT NULL,
  `Sukunimi` varchar(45) NOT NULL,
  `Osoite` varchar(45) NOT NULL,
  `Puhelinnumero` varchar(45) NOT NULL,
  PRIMARY KEY (`idAsiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `Tunnistekoodi` varchar(45) NOT NULL,
  `PIN` varchar(60) NOT NULL,
  `Exp_date` date NOT NULL,
  `idAsiakas` int NOT NULL,
  PRIMARY KEY (`Tunnistekoodi`),
  KEY `fk_Kortti_Asiakas_idx` (`idAsiakas`),
  CONSTRAINT `fk_Kortti_Asiakas` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `kortti_tili`
--

DROP TABLE IF EXISTS `kortti_tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti_tili` (
  `Tunnistekoodi` varchar(45) NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`Tunnistekoodi`,`idTili`),
  KEY `fk_Kortti_Tili_Kortti1_idx` (`Tunnistekoodi`),
  KEY `fk_Kortti_Tili_Tili1_idx` (`idTili`),
  CONSTRAINT `fk_Kortti_Tili_Kortti1` FOREIGN KEY (`Tunnistekoodi`) REFERENCES `kortti` (`Tunnistekoodi`),
  CONSTRAINT `fk_Kortti_Tili_Tili1` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `idTili` int NOT NULL AUTO_INCREMENT,
  `Tilinumero` varchar(45) NOT NULL,
  `Saldo` decimal(10,2) NOT NULL,
  `luottoraja` decimal(10,2) NOT NULL,
  `idAsiakas` int NOT NULL,
  PRIMARY KEY (`idTili`),
  KEY `fk_Tili_Asiakas1_idx` (`idAsiakas`),
  CONSTRAINT `fk_Tili_Asiakas1` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `idTilitapahtumat` int NOT NULL AUTO_INCREMENT,
  `Tapahtumat` enum('Otto','Pano') NOT NULL,
  `Summa` decimal(10,2) NOT NULL,
  `Ajankohta` timestamp(6) NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idTilitapahtumat`),
  KEY `fk_Tilitapahtumat_Tili1_idx` (`idTili`),
  CONSTRAINT `fk_Tilitapahtumat_Tili1` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=73 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-02-03 11:07:10
