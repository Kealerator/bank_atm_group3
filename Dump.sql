-- MySQL dump 10.13  Distrib 8.0.44, for Win64 (x86_64)
--
-- Host: localhost    Database: bank_automat
-- ------------------------------------------------------
-- Server version	8.4.6

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
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (4,'Aku','Ankka','Puutarhakatu 13','04013131313'),(5,'Hannu','Hanhi','Onnela 7','0407777777'),(6,'Sakari','Sakkinen','Sammakkokuja 4','0401234567');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

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
  `PINAttempts` int DEFAULT NULL,
  `LastAttempt` timestamp(6) NULL DEFAULT NULL,
  PRIMARY KEY (`Tunnistekoodi`),
  KEY `fk_Kortti_Asiakas_idx` (`idAsiakas`),
  CONSTRAINT `fk_Kortti_Asiakas` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES ('111111','$2b$10$I1qrDIYddinFHEx7q/cTNeLSCHFqnhbGQ.ymtWyPByC9l6Z3VuxjC','2027-11-11',6,3,'2026-02-23 02:04:01.472000'),('131313','$2b$10$k9JDfqKRO4Eh.b5GJ2QtbOqdpK/MwNiC.oep5JuDnQgPtKYluxIBu','2027-02-02',4,0,'2026-02-23 03:28:12.165000');
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

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
-- Dumping data for table `kortti_tili`
--

LOCK TABLES `kortti_tili` WRITE;
/*!40000 ALTER TABLE `kortti_tili` DISABLE KEYS */;
INSERT INTO `kortti_tili` VALUES ('111111',5),('131313',6);
/*!40000 ALTER TABLE `kortti_tili` ENABLE KEYS */;
UNLOCK TABLES;

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
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (5,'FI1111',111.10,200.00,6),(6,'FI131313',670.00,200.00,4);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

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
) ENGINE=InnoDB AUTO_INCREMENT=89 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (73,'Otto',-20.00,'2026-02-13 12:00:55.000000',6),(74,'Otto',-40.00,'2026-02-16 16:16:25.000000',6),(75,'Pano',800.00,'2026-02-22 16:20:42.000000',6),(76,'Otto',-20.00,'2026-02-22 16:21:08.000000',6),(77,'Otto',-20.00,'2026-02-22 16:21:09.000000',6),(78,'Otto',-20.00,'2026-02-22 16:21:10.000000',6),(79,'Otto',-20.00,'2026-02-22 16:21:10.000000',6),(80,'Otto',-20.00,'2026-02-22 16:21:11.000000',6),(81,'Otto',-40.00,'2026-02-22 16:21:11.000000',6),(82,'Otto',-20.00,'2026-02-22 16:21:12.000000',6),(83,'Otto',-20.00,'2026-02-22 16:21:12.000000',6),(84,'Otto',-20.00,'2026-02-22 16:21:13.000000',6),(85,'Otto',-20.00,'2026-02-22 16:21:13.000000',6),(86,'Otto',-10.00,'2026-02-22 16:21:21.000000',6),(87,'Otto',-20.00,'2026-02-22 17:07:40.000000',6),(88,'Otto',-20.00,'2026-02-22 17:07:49.000000',6);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-02-23  5:30:45
