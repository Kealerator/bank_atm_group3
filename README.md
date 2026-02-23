# Ryhmä 3 opiskelijoiden pankkiautomaatti-projekti

## Johdanto

Tämän projektin tarkoitus oli luoda virtuaalinen pankkiautomaatti. Pankkiautomaatin frontend on toteutettu Qt-sovelluksena ja backend on rakennettu Node.js/Express.js ympäristöön joka on yhteydessä MySQL-tietokantaan. Frontend ja backend kommunikoivat keskenään REST API:n kautta HTTP-yhteydellä. Pankkiautomaatilla voit tunnistautua, nostaa rahaa sekä tarkistaa saldon, tilitapahtumat ja asiakastiedot.

## Pankkiautomaatin Posteri

![](images/poster_group3.png)

## Ominaisuudet

 - **Käyttäjän tunnistautuminen:** Kirjautuminen tunnistekoodilla ja PIN-koodilla.
 - **Päävalikko:** Näkymä josta käyttäjä voi valita pankkitoiminnon.
 - **Saldon tarkistus:** Tilin saldon näyttäminen.
 - **Asiakastiedot:** Kirjautuneen käyttäjän asiakastiedot.
 - **Tilitapahtumat:** Listaus tilin viimeisimmistä tilitapahtumista.
 - **Käteisen nosto:** Rahan nosto käyttäjän tililtä.
 - **Uloskirjautuminen:** Käyttäjän turvallinen uloskirjautuminen.

## Työkalut

 - **Github:** Versionhallinta ja dokumentointi.
 - **Visual Studio Code:** Backend kehitys.
 - **Uniform Server Zero:** MySQL paikallinen palvelin.
 - **Postman:** REST API testaaminen.
 - **QT-Creator:** Frontend kehitys.
 - **MySQL Workbench:** Tietokannan rakennus.
 - **Kanban:** Projektinhallinta ja työnjako.
 - **Teams:** Palaverit ja kommunikaatio.

## Sovelluksen arkitehtuuri

### Komponentit
 - **Tietokanta (MySQL):** Vastaa tiedon hallinnasta ja tallennuksesta.
 - **Backend (Node.js/Express.js):** Toimii sovelluksen REST API rajapintana, joka välittää tiedon tietokannan ja käyttöliittymän välillä.
 - **Frontend (Qt Creator):** C++ pohjainen työpöytäsovellus, jonka verkkoliikenne on toteutettu Qt Network moduulilla.

### Tiedonkulku
- Qt-sovellus lähettää HTTP-pyynnön REST API:lle.
- Palvelin hakee pyydetyn tiedon MySQL-tietokannasta.
- Pyydetty tieto palautetaan palvelimelta JSON-vastauksena   Qt-sovellukseen.
- Qt-sovellus lukee JSON-datan ja päivittää näkymän käyttäjälle.


### ER-Kaavio

![](images/er_kaavio.png)

### Käyttöönottokaavio

![](images/kayttoonottokaavio.png)


## Asennus ja käyttöönotto

### Asennus:
- Kloonaa repo tietokoneellesi
   ```
  git clone https://github.com/25kmo-project/group_3.git
   ```
- Asenna riippuvuudet group_3/backend kansioon terminaalissa tai komentorivillä.


    ```
    npm install bcryptjs@3.0.3 cookie-parser@1.4.7 debug@2.6.9 express@4.16.4 jsonwebtoken@9.0.3 morgan@1.9.1 mysql2@3.16.0 dotenv@17.2.3
    ```

- Asenna nodemon työkalu group_3/backend kansioon.
  ```
  npm install nodemon -g
  ```

- Asenna valitsemasi MySQL palvelin ja luo tietokanta sekä käyttäjä oikeuksilla:
  ```
  CREATE DATABASE bank_automat;
  CREATE USER 'netuser'@'localhost' IDENTIFIED BY 'netpass';
  GRANT ALL PRIVILEGES ON bank_automat.* TO 'netuser'@'localhost';
  ``` 
- Luo tietokannan rakenne juuresta löytyvällä Dump tiedostolla
 
  **MySQL Workbench ohje:**

  - Avaa MySQL Workbench ja kirjaudu sisään.

    Valitse vasemmasta laidasta Server-välilehti ja sieltä Data Import.

    Valitse Import from Self-Contained File ja etsi projektin juuresta löytyvä Dump tiedosto (Dump.sql).

    Valitse Default Target Schema -valikosta aiemmin luomasi tietokanta bank_automat.

    Paina Start Import.
    
- Luo .env tiedosto group_3/backend kansioon ja lisää sinne: 
   ```
   SQL_SERVER="mysql://netuser:netpass@127.0.0.1:3306/bank_automat"
   MY_TOKEN=RAf6OUluNGmHPxUHb9fyO+KHqE3U6enB6lPszO7S/4iJA4589GxhJQtYvAwZL3DecMp9eTPDFkKkiAt8ouxByA==
   ```

 ### Käyttöönotto:

 - Siirry terminaalissa tai komentorivillä projektin backend kansioon ja käynnistä palvelin:
    ```
    nodemon
    ```
   - Tämä käynnistää Node.js palvelimen joka jää kuuntelemaan Qt-sovelluksen lähettämiä pyyntöjä.

 - Avaa Qt Creatorilla "bank_automat" projekti ja paina "Run" näppäintä.
 - Kun molemmat osat ovat käynnissä, voit testata sovellusta kirjautumalla sisään:
   
   - Syötä käyttöliittymään tietokannasta löytyvä tunnistekoodi (kortin numero).

   - Syötä siihen liittyvä PIN-koodi.
    - Onnistuneen kirjautumisen jälkeen voit käyttää kaikkia pankkitoimintoja.


## Projektin tekijät:

### Riku - #angesri
- Backend, CRUD-operaatiot, Qt-sovelluksen saldo ja asiakastiedot osio.
### Jermu - #Jermu0
- Backend, CRUD-operaatiot, Qt-sovelluksen tilitapahtumat osio.
### Matti - #Kealerator
- Backend, CRUD-operaatiot, Qt-sovelluksen login ja UI design.
### Sander - #SanderVee
- Backend, CRUD-operaatiot, Qt-sovelluksen nosto osio.


#### Jokainen projektin jäsen osallistui dokumentointiin ja projektinhallintaan




## Lisenssi

Tämä projekti on lisensoitu [MIT-lisenssillä](LICENSE).





